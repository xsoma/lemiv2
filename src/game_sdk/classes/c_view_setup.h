#pragma once
#include <math/q_angle.h>
#include <math/v_matrix.h>

enum ClearFlags_t
{
	VIEW_CLEAR_COLOR = 0x1,
	VIEW_CLEAR_DEPTH = 0x2,
	VIEW_CLEAR_FULL_TARGET = 0x4,
	VIEW_NO_DRAW = 0x8,
	VIEW_CLEAR_OBEY_STENCIL = 0x10, // Draws a quad allowing stencil test to clear through portals
	VIEW_CLEAR_STENCIL = 0x20,
};

enum StereoEye_t
{
	STEREO_EYE_MONO = 0,
	STEREO_EYE_LEFT = 1,
	STEREO_EYE_RIGHT = 2,
	STEREO_EYE_MAX = 3,
};


//-----------------------------------------------------------------------------
// Purpose: Renderer setup data.  
//-----------------------------------------------------------------------------
class CViewSetup
{
public:
	int x, x_old;
	int y, y_old;
	int width, width_old;
	int height, height_old;
	bool m_bOrtho;
	float m_OrthoLeft;
	float m_OrthoTop;
	float m_OrthoRight;
	float m_OrthoBottom;
	bool m_bCustomViewMatrix;
	Math::matrix3x4_t m_matCustomViewMatrix;
	char pad_0x68[0x48];
	float fov;
	float fovViewmodel;
	Math::CVector origin;
	Math::QAngle angles;
	float zNear;
	float zFar;
	float zNearViewmodel;
	float zFarViewmodel;
	float m_flAspectRatio;
	float m_flNearBlurDepth;
	float m_flNearFocusDepth;
	float m_flFarFocusDepth;
	float m_flFarBlurDepth;
	float m_flNearBlurRadius;
	float m_flFarBlurRadius;
	int m_nDoFQuality;
	int m_nMotionBlurMode;
	float m_flShutterTime;
	Math::CVector m_vShutterOpenPosition;
	Math::QAngle m_shutterOpenAngles;
	Math::CVector m_vShutterClosePosition;
	Math::QAngle m_shutterCloseAngles;
	float m_flOffCenterTop;
	float m_flOffCenterBottom;
	float m_flOffCenterLeft;
	float m_flOffCenterRight;
	int m_EdgeBlur;
};