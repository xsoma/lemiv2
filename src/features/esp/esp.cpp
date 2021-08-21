#include "esp.h"

#include <math/v_matrix.h>
#include <math/game_math.h>
#include <game_sdk/entitys/local_player.h>
#include <globals.h>
#include <tools/render_tool.h>

#include <algorithm>



bool get_player_box(CBasePlayer* ent, Math::Box& box_in)
{
	Math::vec3_t origin, min, max, flb, brt, blb, frt, frb, brb, blt, flt;
	float left, top, right, bottom;

	origin = ent->get_origin_vt();
	min = ent->collideable()->mins() + origin;
	max = ent->collideable()->maxs() + origin;

	Math::vec3_t points[] = {
		Math::vec3_t(min.x, min.y, min.z),
		Math::vec3_t(min.x, max.y, min.z),
		Math::vec3_t(max.x, max.y, min.z),
		Math::vec3_t(max.x, min.y, min.z),
		Math::vec3_t(max.x, max.y, max.z),
		Math::vec3_t(min.x, max.y, max.z),
		Math::vec3_t(min.x, min.y, max.z),
		Math::vec3_t(max.x, min.y, max.z)
	};

	if (!CInterfaces::get().debug_overlay->world_to_screen(points[3], flb) || !CInterfaces::get().debug_overlay->world_to_screen(points[5], brt)
		|| !CInterfaces::get().debug_overlay->world_to_screen(points[0], blb) || !CInterfaces::get().debug_overlay->world_to_screen(points[4], frt)
		|| !CInterfaces::get().debug_overlay->world_to_screen(points[2], frb) || !CInterfaces::get().debug_overlay->world_to_screen(points[1], brb)
		|| !CInterfaces::get().debug_overlay->world_to_screen(points[6], blt) || !CInterfaces::get().debug_overlay->world_to_screen(points[7], flt))
		return false;

	Math::vec3_t arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	left = flb.x;
	top = flb.y;
	right = flb.x;
	bottom = flb.y;

	if (left < 0 || top < 0 || right < 0 || bottom < 0)
		return false;

	for (int i = 1; i < 8; i++) {
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	box_in.x = (int)left;
	box_in.y = (int)top;
	box_in.w = int(right - left);
	box_in.h = int(bottom - top);

	return true;
}

inline void draw_box(CBasePlayer* ent, Math::Box box)
{	
	Color col = ent->is_visible(CBasePlayer::get_local_player()) ? Color(G::get().player->visible_color) : Color(G::get().player->unvisible_color);
	RenderTool::get().draw_border_box(box.x, box.y, box.w, box.h, col);
}

inline void draw_name(CBasePlayer* ent, Math::Box box)
{
	player_info_t pi;

	if (!ent->get_player_info(pi))
		return;

	int w, h;
	
	CInterfaces::get().i_surface->get_text_size(G::get().fonts->dFont[12], get_wc_t(pi.m_player_name), w, h);

	//RenderTool::get().draw_filled_box((box.x + w * 0.5) + w - 2, (box.y + box.h) + h + 2, w + 2, h + 2, Color(0, 0, 0, 100));

	RenderTool::get().draw_text(box.x + box.w * 0.5, box.y + box.h, G::get().fonts->dFont[12], pi.m_player_name, true, Color::White());
}

void ESP::draw()
{
	if (!G::get().player->esp_enable)
		return;

	if (!CInterfaces::get().engine->is_in_game())
		return;

	CLocalPlayer* local_player = CLocalPlayer::get_local_player();

	if (!local_player)
		return;


	for (int i = 1; i <= CInterfaces::get().engine->get_max_clients(); ++i)
	{
		CBasePlayer* ply = (CBasePlayer*)CBasePlayer::get_by_index(i);

		if (!ply || !ply->is_alive() || ply == local_player || ply->is_dormant())
			continue;

		if (ply->get_client_class()->ClassId != class_ids::ccsplayer)
			continue;

		if (G::get().player->esp_check_team)
			if (ply->get_team_num() == local_player->get_team_num())
				continue;

		Math::Box box;

		if (!get_player_box(ply, box))
			continue;

		draw_box(ply, box);

		draw_name(ply, box);
	}
}
