#include "legit_bot.h"

#include <interfaces.h>

#include <globals.h>
#include <game_sdk/entitys/local_player.h>


void get_bone(Math::CVector& in_vector, float& in_fov, CBaseEntity* ent, const Math::CVector& viewangels)
{
	if (!G::get().aim->nerest)
	{
		in_vector = ent->get_entity_bone(ECSPlayerBones::head_0);
		return;
	}

	CLocalPlayer* local_player = CLocalPlayer::get_local_player();
	Math::QAngle aim_punch = local_player->get_aim_punch_angel() * 2.f;
	float best_fov = FLT_MAX;
	float best_bone = 6;

	for (auto bone : { 8, 4, 3, 7, 6, 5 })
	{
		auto angle = Math::CalculateRelativeAngle(local_player->get_eye_pos(), ent->get_entity_bone(bone), viewangels + aim_punch);
		auto fov = std::hypot(angle.x, angle.y);

		if (fov < best_fov)
			best_fov = fov, best_bone = bone;
	}

	in_vector = ent->get_entity_bone(best_bone);
	in_fov = best_fov;
}

CBasePlayer* LegitBot::get_closest(CUserCmd* ucmd)
{
	CLocalPlayer* local_player = CLocalPlayer::get_local_player();
	CBasePlayer* best = nullptr;

	Math::QAngle aim_punch = local_player->get_aim_punch_angel() * 2.f;

	Math::QAngle view_angel;
	CInterfaces::get().engine->get_viewangles(view_angel);

	float best_fov = FLT_MAX;

	for (size_t i = 0; i <= 64; i++)
	{
		CBasePlayer* ply = (CBasePlayer*)CBasePlayer::get_by_index(i);

		if (!ply || !ply->is_alive() || ply == local_player || ply->is_dormant())
			continue;

		if (ply->get_client_class()->ClassId != class_ids::ccsplayer)
			continue;

		if (G::get().aim->only_visible)
			if (!ply->is_visible(local_player))
				continue;

		if (G::get().aim->check_team)
			if (ply->get_team_num() == local_player->get_team_num())
				continue;

		Math::QAngle aimAng = Math::CalcAngel(local_player->get_eye_pos(), ply->get_entity_bone(ECSPlayerBones::head_0));

		float fov = local_player->get_fov_to_player(view_angel + local_player->get_aim_punch_angel() * 2.f, aimAng);

		if (G::get().aim->nerest)
		{
			float fov;
			Math::CVector bone;
			get_bone(bone, fov, ply, view_angel);
		}


		if (fov < best_fov && round(fov) <= G::get().aim->fov)
			best_fov = fov, best = ply;

	}

	return best;
}

void LegitBot::work(CUserCmd* ucmd)
{
	CLocalPlayer* local_player = CLocalPlayer::get_local_player();
	if (!local_player)
		return;

	if (!G::get().aim->enable)
		return;

	Math::QAngle view_angel;
	CInterfaces::get().engine->get_viewangles(view_angel);

	CBasePlayer* best = this->get_closest(ucmd);
	if (!best)
		return;

	Math::QAngle ang;

	if (!G::get().aim->nerest)
		ang = Math::CalcAngel(local_player->get_eye_pos(), best->get_entity_bone((ECSPlayerBones)8)) - local_player->get_aim_punch_angel() * 2;
	else
	{
		Math::CVector bone;
		float fov;

		get_bone(bone, fov, best, view_angel);

		ang = Math::CalcAngel(local_player->get_eye_pos(), bone) - local_player->get_aim_punch_angel() * 2;
	}


	smooth(view_angel, ang, (float)G::get().aim->smooth);

	if (ucmd->viewangles != ang)
		ucmd->viewangles = ang;

	CInterfaces::get().engine->set_viewangles(ang);
}

void LegitBot::smooth(Math::QAngle& view_angel, Math::QAngle& angel, float value)
{
	angel = (view_angel + (angel - view_angel).Clamped() / value).Clamped();
}
