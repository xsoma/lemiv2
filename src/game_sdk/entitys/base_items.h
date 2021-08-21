#pragma once

#include <tools/netvars.h>
#include "base_entity.h"

class CEconItemView
{
private:
	using str_32 = char[32];
public:
	NETVAR("DT_BaseAttributableItem", "m_bInitialized", is_initialized, int32_t);
	NETVAR("DT_BaseAttributableItem", "m_iItemDefinitionIndex", get_item_defintion_index, int32_t);
	NETVAR("DT_BaseAttributableItem", "m_iEntityLevel", get_entity_level, int32_t);
	NETVAR("DT_BaseAttributableItem", "m_iAccountID", get_account_id, int32_t);
	NETVAR("DT_BaseAttributableItem", "m_iItemIDLow", get_item_id_low, int32_t);
	NETVAR("DT_BaseAttributableItem", "m_iItemIDHigh", get_item_id_hight, int32_t);
	NETVAR("DT_BaseAttributableItem", "m_iEntityQuality", get_entity_quality, int32_t);
	NETVAR("DT_BaseAttributableItem", "m_szCustomName", get_custom_name, str_32);
};

class CBaseAttributableItem : public CBaseEntity
{
public:
	//NETVAR(uint64_t, m_OriginalOwnerXuid, "DT_BaseAttributableItem", "m_OriginalOwnerXuidLow");
	//NETVAR(int32_t, m_OriginalOwnerXuidLow, "DT_BaseAttributableItem", "m_OriginalOwnerXuidLow");
	//NETVAR(int32_t, m_OriginalOwnerXuidHigh, "DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh");
	//NETVAR(int32_t, m_nFallbackStatTrak, "DT_BaseAttributableItem", "m_nFallbackStatTrak");
	//NETVAR(int32_t, m_nFallbackPaintKit, "DT_BaseAttributableItem", "m_nFallbackPaintKit");
	//NETVAR(int32_t, m_nFallbackSeed, "DT_BaseAttributableItem", "m_nFallbackSeed");
	//NETVAR(float_t, m_flFallbackWear, "DT_BaseAttributableItem", "m_flFallbackWear");

	//NETVAR(C_EconItemView, m_Item2, "DT_BaseAttributableItem", "m_Item");

	//C_EconItemView& m_Item()
	//{
	//	// Cheating. It should be this + m_Item netvar but then the netvars inside C_EconItemView wont work properly.
	//	// A real fix for this requires a rewrite of the netvar manager
	//	return *(C_EconItemView*)this;
	//}
	//void SetGloveModelIndex(int modelIndex);

};


class CBaseCombatWeapon : public CBaseAttributableItem
{
public:
	NETVAR("DT_BaseCombatWeapon", "m_flNextPrimaryAttack", get_next_primary_attack, float);
	NETVAR("DT_BaseCombatWeapon", "m_flNextSecondaryAttack", get_next_secondary_attack, float);
	NETVAR("DT_BaseEntity", "m_hOwnerEntity", get_owner_entity, CBaseEntity*);
	NETVAR("DT_BaseCombatWeapon", "m_iClip1", get_clip1, int);
	NETVAR("DT_BaseCombatWeapon", "m_iClip2", get_clip2, int);

	//bool has_primary_ammo()
	//{
	//	using orig_fn = bool(__thiscall*)(void*);
	//	return (*(orig_fn**)this)[27](this);
	//}

	//bool can_fire()
	//{
	//	auto owner = get_owner_entity();

	//	if (!owner)
	//		return false;

	//	if (!has_primary_ammo())
	//		return false;

	//	return true;
	//}
};