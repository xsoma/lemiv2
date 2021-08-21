#pragma once
#include <math/vector.h>

//      "engine.dll", "VDebugOverlay004"

class VDebugOverlay
{
public:
	bool world_to_screen(const Math::CVector& in, Math::CVector& out) {
		using original_fn = int(__thiscall*)(VDebugOverlay*, const Math::CVector&, Math::CVector&);
		int return_value = (*(original_fn**)this)[13](this, in, out);
		return static_cast<bool>(return_value != 1);
	}	
	
	bool world_to_screen(const Math::vec3_t& in, Math::vec3_t& out) {
		using original_fn = int(__thiscall*)(VDebugOverlay*, const Math::vec3_t&, Math::vec3_t&);
		int return_value = (*(original_fn**)this)[13](this, in, out);
		return static_cast<bool>(return_value != 1);
	}


};