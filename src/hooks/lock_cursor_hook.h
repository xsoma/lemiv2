#pragma once

#include <game_interfaces/i_surface.h>

namespace lock_cursor_hook
{
	using fn = void(__thiscall*)(ISurface*);
	extern void __stdcall hook();
}