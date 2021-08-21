#pragma once
#include <singleton.h>

#include <game_sdk/classes/c_user_cmd.h>
#include <game_sdk/entitys/base_player.h>


class LegitBot : public Singleton<LegitBot>
{
private:
	CBasePlayer* targeted = nullptr;

	CBasePlayer* get_closest(CUserCmd* ucmd);
public:
	void work(CUserCmd* ucmd);

	void smooth(Math::QAngle& view_angel, Math::QAngle& angel, float value);
};
