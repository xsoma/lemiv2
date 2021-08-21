#include <iostream>

#include "end_scane_hook.h"
#include "hook_manager.h"

#include <tools/render_tool.h>

#include <features/esp/esp.h>
#include <features/menu/menu.h>

#include <imgui/imgui.h>
#include <imgui/impl/imgui_impl_win32.h>
#include <imgui/impl/imgui_impl_dx9.h>

#include <globals.h>
#include <features/menu/menu.h>

#include <hack_core.h>

static bool is_init = false;
static WNDPROC wnd_proc = nullptr;

LRESULT STDMETHODCALLTYPE my_wndproc(HWND window, UINT message_type, WPARAM w_param, LPARAM l_param)
{
    if (message_type == WM_KEYDOWN)
    {
        if (w_param == VK_INSERT)
            Menu::get().trigger();
        if (w_param == VK_DELETE)
            CHackCore::get().shutdown();
    }

    if (ImGui_ImplWin32_WndProcHandler(window, message_type, w_param, l_param) && Menu::get().is_open())
    {
        return true;
    }
    return CallWindowProc(wnd_proc, window, message_type, w_param, l_param);
}


void init(IDirect3DDevice9* device)
{
    ImGui::CreateContext();

    auto game_hwnd = FindWindow("Valve001", 0);
    if (game_hwnd != NULL)
    {
        ImGui_ImplWin32_Init(game_hwnd);
        ImGui_ImplDX9_Init(device);

        ImGui::GetIO().IniFilename = nullptr;
        ImGui::StyleColorsDark();

        wnd_proc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(game_hwnd, GWLP_WNDPROC, LONG_PTR(my_wndproc)));

        RenderTool::get().init(device);

        ImRender::get().init();

        is_init = true;
    }
}


long __stdcall end_scane_hook::hook(IDirect3DDevice9* device)
{
    if (!is_init)
        init(device);

    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImRender::get().render_frame();

    Menu::get().draw();

    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

    return HookManager::get().end_scane_original(device);
}