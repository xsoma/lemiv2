#pragma once
#include <game_interfaces/v_base_client.h>


namespace frame_stage_notify_hook
{
	using fn = void(__fastcall*)(void*, int, ClientFrameStage_t);
	extern void __fastcall hook(void* _this, int edx, ClientFrameStage_t stage);
}