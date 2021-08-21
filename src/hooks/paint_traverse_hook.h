#pragma once
#include <game_interfaces/i_panel.h>

namespace paint_traverse_hook
{
	using fn = void(__thiscall*)(IPanel*, unsigned int, bool, bool);
	extern void __stdcall hook(unsigned int panel, bool force_repaint, bool allow_force);
}