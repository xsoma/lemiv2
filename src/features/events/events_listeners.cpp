#include "events_listeners.h"
#include <interfaces.h>
#include <game_sdk/fnv.h>

#include <game_sdk/entitys/base_player.h>

CBasePlayer* get_player_from_event(IGameEvent* _event)
{
	return (CBasePlayer*)CBasePlayer::get_by_index(CInterfaces::get().engine->get_player_for_user_id(_event->get_int("userid")));
}

MyEventListener::MyEventListener() noexcept
{
	CInterfaces::get().game_event_manager->add_listener(this, "player_footstep", false);

}

void MyEventListener::remove() noexcept
{
	CInterfaces::get().game_event_manager->remove_listener(this);
}

void MyEventListener::fire_game_event(IGameEvent* _event)
{
	
	switch (fnv::hash(_event->get_name()))
	{
	case fnv::hash("player_footstep"):
		auto ply = get_player_from_event(_event);
		if (ply != CBasePlayer::get_local_player())
		{

		}
		break;
	}

}

void MyEventListener::add_listener(const char* name, event_callback)
{
}

void EventsListeners::init()
{
	this->main_listener = new MyEventListener();
}
