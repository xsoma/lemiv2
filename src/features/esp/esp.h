#pragma once
#include <singleton.h>


class ESP : public Singleton<ESP>
{
public:
	void draw();
};