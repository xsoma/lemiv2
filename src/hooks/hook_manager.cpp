#include <MinHook.h>


#include "hook_manager.h"
#include "interfaces.h"


inline unsigned int get_virtual(void* _class, unsigned int index) { return static_cast<unsigned int>((*static_cast<int**>(_class))[index]); }

bool HookManager::setup()
{
    const auto create_move_target = reinterpret_cast<void*>(get_virtual(CInterfaces::get().client_mode, 24));
    const auto paint_traverse_target = reinterpret_cast<void*>(get_virtual(CInterfaces::get().i_panel, 41));
    const auto end_scane_target = reinterpret_cast<void*>(get_virtual(CInterfaces::get().directx_device, 42));
    const auto reset_target = reinterpret_cast<void*>(get_virtual(CInterfaces::get().directx_device, 16));
    const auto lock_cursor_target = reinterpret_cast<void*>(get_virtual(CInterfaces::get().i_surface, 67));
    const auto frame_stage_notify_target = reinterpret_cast<void*>(get_virtual(CInterfaces::get().client, 37));
    const auto override_view_target = reinterpret_cast<void*>(get_virtual(CInterfaces::get().client_mode, 18));

    if (MH_Initialize() != MH_OK)
        return false;

    if (MH_CreateHook(create_move_target, &create_move_hook::hook, reinterpret_cast<void**>(&this->create_move_original)) != MH_OK) 
    { std::cout << "CreateMove" << " setup error\n"; return false; }

    if (MH_CreateHook(paint_traverse_target, &paint_traverse_hook::hook, reinterpret_cast<void**>(&this->paint_traverse_original)) != MH_OK)
    { std::cout << "paint_traverse" << " setup error\n"; return false; }

    if (MH_CreateHook(end_scane_target, &end_scane_hook::hook, reinterpret_cast<void**>(&this->end_scane_original)) != MH_OK)
    { std::cout << "end_scane" << " setup error\n"; return false; }

    if (MH_CreateHook(reset_target, &reset_hook::hook, reinterpret_cast<void**>(&this->reset_original)) != MH_OK)
    { std::cout << "reset" << " setup error\n"; return false; }

    if (MH_CreateHook(lock_cursor_target, &lock_cursor_hook::hook, reinterpret_cast<void**>(&this->lock_cursor_original)) != MH_OK)
    { std::cout << "lock_cursor" << " setup error\n"; return false; }

    if (MH_CreateHook(frame_stage_notify_target, &frame_stage_notify_hook::hook, reinterpret_cast<void**>(&this->frame_stage_notify_original)) != MH_OK)
    { std::cout << "frame_stage_notify" << " setup error\n"; return false; }    
    
    if (MH_CreateHook(override_view_target, &override_view_hook::hook, reinterpret_cast<void**>(&this->override_view_original)) != MH_OK)
    { std::cout << "override_view" << " setup error\n"; return false; }

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
        return false;

    return true;
}

void HookManager::remove()
{
    MH_Uninitialize();
    MH_DisableHook(MH_ALL_HOOKS);
}
