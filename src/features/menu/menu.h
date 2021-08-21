#pragma once
#include <singleton.h>


class Menu : public Singleton<Menu>
{
	bool b_open = false;

public:
	void draw();

	inline bool is_open() { return this->b_open; }
	inline void close() { this->b_open = false; }
	inline void open() { this->b_open = true; }
	inline void trigger() { this->b_open = !this->b_open; }
};
