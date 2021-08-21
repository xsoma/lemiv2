#include "game_math.h"


namespace Math
{

	static float numb(float f, float s)
	{
		if (f > s)
			return abs(f - s);
		else if (s > f)
			return abs(s - f);
		return 0;
	}

	static bool ScreenTransform(const Math::CVector& in, Math::CVector& out)
	{
		static auto& w2sMatrix = CInterfaces::get().engine->world_to_screen_matrix();


		out.x = w2sMatrix.m[0][0] * in.x + w2sMatrix.m[0][1] * in.y + w2sMatrix.m[0][2] * in.z + w2sMatrix.m[0][3];
		out.y = w2sMatrix.m[1][0] * in.x + w2sMatrix.m[1][1] * in.y + w2sMatrix.m[1][2] * in.z + w2sMatrix.m[1][3];
		out.z = 0.0f;

		float w = w2sMatrix.m[3][0] * in.x + w2sMatrix.m[3][1] * in.y + w2sMatrix.m[3][2] * in.z + w2sMatrix.m[3][3];

		if (w < 0.001f) {
			out.x *= 100000;
			out.y *= 100000;
			return false;
		}

		out.x /= w;
		out.y /= w;

		return true;
	}

	bool world_to_screen_dx(const Math::CVector& in, Math::CVector& out)
	{
		if (ScreenTransform(in, out))
		{
			int width, height; CInterfaces::get().engine->get_screen_size(width, height);

			out.x = (width / 2.0f) + (out.x * width) / 2.0f;
			out.y = (height / 2.0f) - (out.y * height) / 2.0f;

			//std::cout << out.x << "\t" << out.y << "\n\0";

			return true;
		}
		return false;
	}

	bool world_to_screen(const Math::CVector& in, Math::CVector& out)
	{
		auto& w2sm = CInterfaces::get().engine->world_to_screen_matrix();

		float w = w2sm[3][0] * in.x + w2sm[3][1] * in.y + w2sm[3][2] * in.z + w2sm[3][3];

		if (w > 0.001f)
		{
			int width, height; CInterfaces::get().engine->get_screen_size(width, height);

			float fl1DBw = 1.0f / w;
			out.x = (width / 2) + (0.5f * ((w2sm[0][0] * in.x + w2sm[0][1] * in.y + w2sm[0][2] * in.z + w2sm[0][3]) * fl1DBw) * width + 0.5f);
			out.y = (height / 2) - (0.5f * ((w2sm[1][0] * in.x + w2sm[1][1] * in.y + w2sm[1][2] * in.z + w2sm[1][3]) * fl1DBw) * height + 0.5f);


			return true;
		}
		return false;
	}



}
