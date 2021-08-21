#include "hack_core.h"
#include "interfaces.h"
#include "hooks/hook_manager.h"
#include "globals.h"
#include "features/events/events_listeners.h"


bool CHackCore::init()
{
	//#ifdef DEBUG_CONSOLE
	AllocConsole();
	freopen("CONOUT$", "wb", stdout);
	freopen("CONOUT$", "wb", stderr);
	freopen("CONIN$", "rb", stdin);
	//#endif


	//if (this->fnPreInit_ != nullptr && !this->fnPreInit_())
		//return false;


	std::cout << "[L]\tCapturing interfaces" << std::flush;
	if (CInterfaces::get().init())
		std::cout << "\tOK!" << std::endl;
	else
		return false;
	CInterfaces::get().print_interfaces();

	std::cout << "\n[L]\tHooking functions" << std::flush;
	if (HookManager::get().setup())
		std::cout << "\tOK!" << std::endl;
	else
		return false;

	EventsListeners::get().init();
	

	//if (this->fnPostInit_ != nullptr && !this->fnPostInit_())
		//return false;
	return true;
}

bool CHackCore::shutdown()
{
	FreeConsole();
	HookManager::get().remove();
	FreeLibraryAndExitThread((HMODULE)this->dll, 0);
	return false;
}