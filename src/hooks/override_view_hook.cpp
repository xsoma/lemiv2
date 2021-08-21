#include "override_view_hook.h"
#include <globals.h>
#include "hook_manager.h"


void __stdcall override_view_hook::hook(CViewSetup& vc)
{
	//if (G::get().game->override_fov == -1)
	//	G::get().game->override_fov = vc.fov;
	//if (G::get().game->override_viewmodel_fov == -1)
	//	G::get().game->override_viewmodel_fov = vc.fovViewmodel;

	//vc.fov = G::get().game->override_fov;
	//vc.fovViewmodel = G::get().game->override_viewmodel_fov;

	G::get().game->fov = vc.fov;

	HookManager::get().override_view_original(vc);
}
