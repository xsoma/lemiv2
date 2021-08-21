#pragma once
#include <game_sdk/classes/c_view_setup.h>

namespace override_view_hook
{
	using fn = void(__stdcall*)(CViewSetup&);
	extern void __stdcall hook(CViewSetup& vc);
}