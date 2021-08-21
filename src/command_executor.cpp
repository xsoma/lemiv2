#include "command_executor.h"
#include "interfaces.h"
#include <game_sdk/entitys.h>

#include <globals.h>

#include <features/menu/menu.h>

void CCommandExecutor::execute(const std::string& cmd)
{
	if (cmd == "ingame")
	{
		std::cout << CInterfaces::get().engine->is_in_game() << std::endl;
	}
	else if (cmd == "screensize")
	{
		int w, h;
		CInterfaces::get().engine->get_screen_size(w, h);
		std::cout << w << " x " << h << std::endl;
	}
	else if (cmd == "getlpi")
	{
		std::cout << CInterfaces::get().engine->get_local_player() << std::endl;
	}
	else if (cmd == "geth")
	{
		auto ent = (
			(CBasePlayer*)
			(CInterfaces::get().client_entity_list->get_entity_by_index(
			CInterfaces::get().engine->get_local_player()
			)));

		std::cout << ent->get_health() << "\t" << ent->get_flags() << "\t" << ent->get_team_num() << std::endl;
	}
	else if (cmd == "getclasses")
	{
		auto r = reinterpret_cast<DWORD>(CInterfaces::get().client->get_all_classes());
		std::cout << r << std::endl;
	}
	//else if (cmd == "setsmooth")
	//{
	//	std::string s;
	//	std::cin >> s;
	//	float r = (float)std::atof(s.c_str());
	//	std::cout << "Old: " << G::get().f_smooth << "\tNew: " << r << std::endl;
	//	G::get().f_smooth = r;
	//}
	//else if (cmd == "setfov")
	//{
	//	std::string s;
	//	std::cin >> s;
	//	float r = (int)std::atof(s.c_str());
	//	std::cout << "Old: " << G::get().fov << "\tNew: " << r << std::endl;
	//	G::get().fov = r;
	//}	
	//else if (cmd == "setct")
	//{
	//	std::string s;
	//	std::cin >> s;
	//	float r = (int)std::atof(s.c_str());
	//	G::get().check_team = (bool)r;
	//}	
	else if (cmd == "setd")
	{
		std::string s;
		std::cin >> s;
		float r = std::atof(s.c_str());
		G::get().d = r;
	}
	else if (cmd == "cm")
	{
		if (Menu::get().is_open())
			Menu::get().close();
		else
			Menu::get().open();
	}
}
