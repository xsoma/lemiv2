#pragma once
#include "vector.h"
#include "v_matrix.h"
#include <interfaces.h>
#include "vector2d.h" 

namespace Math
{
	struct Box {
		int x, y, w, h;
		Box() = default;
		Box(int x, int y, int w, int h) {
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
	};

	extern bool world_to_screen_dx(const Math::CVector& in, Math::CVector& out);
	extern bool world_to_screen(const Math::CVector& in, Math::CVector& out);
}