#pragma once
#include "singleton.h"
#include <functional>


typedef std::function<bool()> init_callback;


class CHackCore : public Singleton<CHackCore>
{

public:
	void* dll;

	bool init();
	bool shutdown();

	void set_pre_init(init_callback preInitFuncion);
	void set_post_init(init_callback prePostFuncion);

};

