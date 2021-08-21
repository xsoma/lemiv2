#include "paint_traverse_hook.h"
#include "hook_manager.h"
#include <interfaces.h>

#include <game_sdk/fnv.h>
#include <tools/render_tool.h>

#include <globals.h>

#include <features/esp/esp.h>

static bool is_init = false;
static unsigned int dpanel = NULL;

static int lscreen_w, lscreen_h;

void init()
{
	RenderTool::get().create_font(G::get().fonts->dFont);
	is_init = true;
}

void __stdcall paint_traverse_hook::hook(unsigned int panel, bool force_repaint, bool allow_force)
{
	HookManager::get().paint_traverse_original(CInterfaces::get().i_panel, panel, force_repaint, allow_force);

	if (!is_init)
		init();

	if (!dpanel)
	{
		const char* pname = CInterfaces::get().i_panel->get_panel_name(panel);
		if (!strcmp(pname, "FocusOverlayPanel")) {
			dpanel = panel;
		}
	}
	else if (dpanel == panel)
	{
		static bool skip = false;
		skip = !skip;

		if (skip)
			return;

		int screen_w, screen_h;
		CInterfaces::get().engine->get_screen_size(screen_w, screen_h);

		if (screen_h != lscreen_h || screen_w != lscreen_w)
			RenderTool::get().create_font(G::get().fonts->dFont);

		RenderTool::get().draw_text(10, 10, G::get().fonts->dFont[16], "LemiCSGO", false, Color::White());

		ESP::get().draw();

		if (CInterfaces::get().engine->is_in_game())
		{
			if (G::get().visuals->draw_fov)
			{
				auto fov = G::get().aim->fov;
				auto game_fov = G::get().game->fov;

				if (fov > 180) fov = 180;
				if (fov < 0) fov = 1;

				float diagonal = sqrt(pow(screen_w, 2) + pow(screen_h, 2));
				float R = (fov * (diagonal / 145.f)) * 0.85f;

				if (game_fov > 40)
					R = R;
				else if (game_fov > 20)
					R *= 3;
				else
					R *= 6;

				RenderTool::get().draw_cricle(screen_w / 2, screen_h / 2, R, 40, Color::Black());
			}
		}

		lscreen_w = screen_w;
		lscreen_h = screen_h;
	}
}
