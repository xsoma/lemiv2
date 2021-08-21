#include "frame_stage_notify_hook.h"
#include "hook_manager.h"


void __fastcall frame_stage_notify_hook::hook(void* _this, int edx, ClientFrameStage_t stage)
{
	//More shit
	HookManager::get().frame_stage_notify_original(_this, edx, stage);
}
