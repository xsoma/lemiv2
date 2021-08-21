#pragma once
#include <singleton.h>
#include <include_all_interfaces.h>
#include <tools/mem_tools.h>
#include <vector>
#include <d3d9.h>

#define CIINTERNAL

#ifdef CIINTERNAL
#define ADD_INTERFACE( interfaceType, engineInterfaceName ) interfaceType* engineInterfaceName = nullptr;
#define INIT_INTERFACE( interfaceType,  engineInterfaceName, module_, name_ ) this->engineInterfaceName = (interfaceType*)CMemTools::get_interface(module_, name_);

#ifdef DEBUG_CONSOLE
#define PRINT_INTERFACE( interface_, interfaceName) std::cout << "[I]\t" << interfaceName << "\t" << reinterpret_cast<DWORD>(interface_) << std::endl;

#elif DEBUG_CSGO
#define PRINT_INTERFACE( interface_ )
#endif

#endif



namespace interfaces_names
{
	static const char* iv_engine_client = "VEngineClient014";
	static const char* v_client_entity_list = "VClientEntityList003";
	static const char* v_base_client = "VClient018";
	static const char* i_panel = "VGUI_Panel009";
	static const char* i_surface = "VGUI_Surface031";
	static const char* v_debug_overlay = "VDebugOverlay004";
	static const char* i_engine_trace = "EngineTraceClient004";
	static const char* i_game_event_manager = "GAMEEVENTSMANAGER002";
}


class CInterfaces : public Singleton<CInterfaces>
{
public:
	ADD_INTERFACE(IVEngineClient, engine);
	ADD_INTERFACE(VClientEntityList, client_entity_list);
	ADD_INTERFACE(VBaseClient, client);
	ADD_INTERFACE(IClientMode, client_mode);
	ADD_INTERFACE(IPanel, i_panel);
	ADD_INTERFACE(ISurface, i_surface);
	ADD_INTERFACE(IDirect3DDevice9, directx_device);
	ADD_INTERFACE(VDebugOverlay, debug_overlay);
	ADD_INTERFACE(IEngineTrace, engine_trace);
	ADD_INTERFACE(IGameEventManager, game_event_manager);

	bool init();
	bool shutdown();
	void print_interfaces();
};

#undef CIINTERNAL