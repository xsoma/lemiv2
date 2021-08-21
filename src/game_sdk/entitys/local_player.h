#pragma once
#include "base_player.h"
#include <math/q_angle.h>

class CLocalPlayer : public CBasePlayer
{
public:
	static CLocalPlayer* get_local_player()
	{
		return (CLocalPlayer*)CBasePlayer::get_local_player();
	}

	float get_fov_to_player(Math::QAngle view_angel, Math::QAngle aimAngle)
	{
		Math::QAngle delta = aimAngle - view_angel;
		delta.Normalized();
		delta.Clamped();
		return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
		//Math::CVector qAngles = view_angel;
		//Math::CVector vecSource = this->get_eye_pos();
		//Math::CVector vecDestination = ply->get_eye_pos();
		//bool bDistanceBased = false;

		//auto MakeVector = [](Math::QAngle qAngles)
		//{
		//	auto ret = Math::CVector();
		//	auto pitch = float(qAngles[0] * M_PI / 180.f);
		//	auto yaw = float(qAngles[1] * M_PI / 180.f);
		//	auto tmp = float(cos(pitch));
		//	ret.x = float(-tmp * -cos(yaw));
		//	ret.y = float(sin(yaw) * tmp);
		//	ret.z = float(-sin(pitch));
		//	return ret;
		//};

		//Math::CVector ang, aim;
		//double fov;

		//ang = Math::CalcAngel(vecSource, vecDestination);
		//aim = MakeVector(qAngles);
		//ang = MakeVector(ang);

		//auto mag_s = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
		//auto mag_d = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
		//auto u_dot_v = aim[0] * ang[0] + aim[1] * ang[1] + aim[2] * ang[2];

		//fov = acos(u_dot_v / (mag_s * mag_d)) * (180.f / M_PI);

		//if (bDistanceBased) {
		//	fov *= 1.4;
		//	float xDist = abs(vecSource[0] - vecDestination[0]);
		//	float yDist = abs(vecSource[1] - vecDestination[1]);
		//	float Distance = sqrt((xDist * xDist) + (yDist * yDist));

		//	Distance /= 650.f;

		//	if (Distance < 0.7f)
		//		Distance = 0.7f;

		//	if (Distance > 6.5)
		//		Distance = 6.5;

		//	fov *= Distance;
		//}

		//return (float)fov;
	}
};