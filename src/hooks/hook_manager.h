#pragma once
#include <singleton.h>
#include "hooks.h"


class HookManager : public Singleton<HookManager>
{
public:
	create_move_hook::fn create_move_original = nullptr;
	paint_traverse_hook::fn paint_traverse_original = nullptr;
	end_scane_hook::fn end_scane_original = nullptr;
	reset_hook::fn reset_original = nullptr;
	lock_cursor_hook::fn lock_cursor_original = nullptr;
	frame_stage_notify_hook::fn frame_stage_notify_original = nullptr;
	override_view_hook::fn override_view_original = nullptr;

	bool setup();
	void remove();
};