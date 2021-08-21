#pragma once
#include <game_sdk/classes/c_user_cmd.h>
#include <game_interfaces/i_client_mode.h>

namespace create_move_hook
{
	using fn = bool(__thiscall*)(IClientMode*, float, CUserCmd* ucmd);
	extern bool __stdcall hook(int frame_time, CUserCmd* ucmd);
}