#pragma once
#include "singleton.h"
#include <future>
#include <iostream>

class CCommandExecutor : public Singleton<CCommandExecutor>
{
public:
	void execute(const std::string& cmd);
};