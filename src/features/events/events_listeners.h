#pragma once
#include <singleton.h>
#include <game_interfaces/i_event_manager.h>
#include <vector>

using event_callback = void(IGameEvent*);

class MyEventListener : public IGameEventListener
{
private:

public:
	MyEventListener() noexcept;
	void remove() noexcept;
	void fire_game_event(IGameEvent* _event);

	void add_listener(const char* name, event_callback);
};

class EventsListeners : public Singleton<EventsListeners>
{
private:

public:
	IGameEventListener* main_listener = nullptr;

	void init();
};