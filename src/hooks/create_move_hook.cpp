#include "create_move_hook.h"
#include <game_sdk/entitys/base_player.h>
#include "hook_manager.h"

#include <Windows.h>

#include <features/legit_bot/legit_bot.h>

#include <features/menu/menu.h>

#include <globals.h>

#define	FL_ONGROUND				(1<<0)

bool __stdcall create_move_hook::hook(int frame_time, CUserCmd* ucmd)
{
	HookManager::get().create_move_original(CInterfaces::get().client_mode, frame_time, ucmd);

	if (!ucmd)
		return false;

	if (GetAsyncKeyState(G::get().aim->aim_key.code))
	{
		LegitBot::get().work(ucmd);
	}

	CBasePlayer* local_player = CBasePlayer::get_local_player();

	if (ucmd->buttons & IN_JUMP && !(local_player->get_flags() & (int)FL_ONGROUND) && G::get().misc->bhop)
		ucmd->buttons &= ~IN_JUMP;

	if (Menu::get().is_open())
		ucmd->buttons &= ~IN_ATTACK;

	if (ucmd->buttons & IN_SCORE && G::get().misc->reveral_rank)
		CInterfaces::get().client->dispatch_user_message(50, 0, 0, nullptr);	//reveral rank

    return false;
}
