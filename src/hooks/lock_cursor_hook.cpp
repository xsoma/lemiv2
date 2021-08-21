#include "lock_cursor_hook.h"

#include <features/menu/menu.h>

#include <interfaces.h>

#include <hooks/hook_manager.h>

void __stdcall lock_cursor_hook::hook()
{
	if (Menu::get().is_open())
		CInterfaces::get().i_surface->unlock_cursor();
	else
		HookManager::get().lock_cursor_original(CInterfaces::get().i_surface);
}
