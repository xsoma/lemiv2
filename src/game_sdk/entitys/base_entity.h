#pragma once
#include "i_client_entity.h"
#include <tools/netvars.h>
#include <cstdint>
#include <interfaces.h>


enum ECSPlayerBones {
	pelvis = 0,
	spine_0,
	spine_1,
	spine_2,
	spine_3,
	neck_0,
	head_0,
	clavicle_L,
	arm_upper_L,
	arm_lower_L,
	hand_L
};

class CCollideable
{
public:
	virtual void unknown_0() = 0;
	virtual Math::vec3_t& mins() = 0;
	virtual Math::vec3_t& maxs() = 0;



	//Math::vec3_t& mins_vt()
	//{
	//	auto& v = mins();
	//	Math::vec3_t ret = Math::vec3_t(v.x, v.y, v.z);
	//	return ret;
	//}

	//Math::vec3_t& maxs_vt()
	//{
	//	auto& v = maxs();
	//	Math::vec3_t ret = Math::vec3_t(v.x, v.y, v.z);
	//	return ret;
	//}
};


class CBaseEntity : public IClientEntity
{
public:
	NETVAR("DT_DynamicProp", "m_bShouldGlow", is_should_glow, bool);
	NETVAR("DT_BaseEntity", "m_vecOrigin", get_origin, Math::CVector);
	NETVAR("DT_BaseEntity", "m_vecOrigin", get_origin_vt, Math::vec3_t);
	NETVAR("DT_BaseEntity", "m_vecAngles", get_angels, Math::CVector);
	NETVAR("DT_BaseEntity", "m_nModelIndex", get_model_index, int32_t);
	NETVAR("DT_BaseEntity", "m_iTeamNum", get_team_num, int32_t);

	NETVAR("DT_BasePlayer", "m_vecViewOffset[0]", get_view_offset, Math::CVector);
	inline Math::CVector get_eye_pos() { return this->get_origin() + this->get_view_offset(); }

	CCollideable* collideable()
	{
		using original_fn = CCollideable * (__thiscall*)(void*);
		return (*(original_fn**)this)[3](this);
	}

	bool is_player()
	{
		using original_fn = bool(__thiscall*)(void*);
		return (*(original_fn**)this)[157](this);
	}

	bool isWeapon() 
	{
		using original_fn = bool(__thiscall*)(CBaseEntity*);
		return (*(original_fn**)this)[165](this);
	}

	static inline CBaseEntity* get_by_index(int index)
	{
		return (CBaseEntity*)(CInterfaces::get().client_entity_list->get_entity_by_index(index));
	}

	const Math::CVector& get_entity_bone(int Bone)
	{
		Math::matrix3x4_t boneMatrix[128];

		if (!this->setup_bones(boneMatrix, 128, 0x00000100, CInterfaces::get().engine->get_last_time_stamp()))
			return Math::CVector();

		Math::matrix3x4_t hitbox = boneMatrix[Bone];

		return Math::CVector(hitbox[0][3], hitbox[1][3], hitbox[2][3]);
	}

	bool is_visible(CBaseEntity* from)
	{
		Ray_t ray;
		trace_t tr;
		CTraceFilter filter;
		filter.pSkip = from;

		Math::CVector eye_pos = from->get_eye_pos();
		Math::CVector end_pos = this->get_eye_pos();

		ray.Init(eye_pos, end_pos);

		CInterfaces::get().engine_trace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &filter, &tr);


		if (tr.hit_entity == this || tr.fraction >= 0.98f)
			return true;
		return false;
	}

	static inline CBaseEntity* get_local_player() { return (CBaseEntity*)(CBaseEntity::get_by_index(CInterfaces::get().engine->get_local_player())); }

};