#pragma once

#include "D2CommonDefinitions.h"
#include <DataTbls/ItemsTbls.h>

struct D2Unit;
struct D2Game;

#pragma pack(1)

enum D2C_ItemStats
{
	STAT_INVALID = -1,
	STAT_STRENGTH = 0, 					// 000
	STAT_ENERGY, 						// 001
	STAT_DEXTERITY, 					// 002
	STAT_VITALITY, 						// 003
	STAT_STATPTS, 						// 004
	STAT_SKILLPTS, 						// 005
	STAT_HITPOINTS, 					// 006
	STAT_MAXHP, 						// 007
	STAT_MANA, 							// 008
	STAT_MAXMANA, 						// 009
	STAT_STAMINA, 						// 00A
	STAT_MAXSTAMINA, 					// 00B
	STAT_LEVEL, 						// 00C
	STAT_EXPERIENCE, 					// 00D
	STAT_GOLD, 							// 00E
	STAT_GOLDBANK, 						// 00F
	STAT_ITEM_ARMOR_PERCENT, 			// 010
	STAT_ITEM_MAXDAMAGE_PERCENT, 		// 011
	STAT_ITEM_MINDAMAGE_PERCENT, 		// 012
	STAT_TOHIT,
	STAT_TOBLOCK,
	STAT_MINDAMAGE,
	STAT_MAXDAMAGE,
	STAT_SECONDARY_MINDAMAGE,
	STAT_SECONDARY_MAXDAMAGE,
	STAT_DAMAGEPERCENT,
	STAT_MANARECOVERY,
	STAT_MANARECOVERYBONUS,
	STAT_STAMINARECOVERYBONUS,
	STAT_LASTEXP,
	STAT_NEXTEXP,
	STAT_ARMORCLASS,
	STAT_ARMORCLASS_VS_MISSILE,
	STAT_ARMORCLASS_VS_HTH,
	STAT_NORMAL_DAMAGE_REDUCTION,
	STAT_MAGIC_DAMAGE_REDUCTION,
	STAT_DAMAGERESIST,
	STAT_MAGICRESIST,
	STAT_MAXMAGICRESIST,
	STAT_FIRERESIST,
	STAT_MAXFIRERESIST,
	STAT_LIGHTRESIST,
	STAT_MAXLIGHTRESIST,
	STAT_COLDRESIST,
	STAT_MAXCOLDRESIST,
	STAT_POISONRESIST,
	STAT_MAXPOISONRESIST,
	STAT_DAMAGEAURA,
	STAT_FIREMINDAM,
	STAT_FIREMAXDAM,
	STAT_LIGHTMINDAM,
	STAT_LIGHTMAXDAM,
	STAT_MAGICMINDAM,
	STAT_MAGICMAXDAM,
	STAT_COLDMINDAM,
	STAT_COLDMAXDAM,
	STAT_COLDLENGTH,
	STAT_POISONMINDAM,
	STAT_POISONMAXDAM,
	STAT_POISONLENGTH,
	STAT_LIFEDRAINMINDAM,
	STAT_LIFEDRAINMAXDAM,
	STAT_MANADRAINMINDAM,
	STAT_MANADRAINMAXDAM,
	STAT_STAMDRAINMINDAM,
	STAT_STAMDRAINMAXDAM,
	STAT_STUNLENGTH,
	STAT_VELOCITYPERCENT,
	STAT_ATTACKRATE,
	STAT_OTHER_ANIMRATE,
	STAT_QUANTITY,
	STAT_VALUE,
	STAT_DURABILITY,
	STAT_MAXDURABILITY,
	STAT_HPREGEN,
	STAT_ITEM_MAXDURABILITY_PERCENT,
	STAT_ITEM_MAXHP_PERCENT,
	STAT_ITEM_MAXMANA_PERCENT,
	STAT_ITEM_ATTACKERTAKESDAMAGE,
	STAT_ITEM_GOLDBONUS,
	STAT_ITEM_MAGICBONUS,
	STAT_ITEM_KNOCKBACK,
	STAT_ITEM_TIMEDURATION,
	STAT_ITEM_ADDCLASSSKILLS,
	STAT_UNSENTPARAM1,
	STAT_ITEM_ADDEXPERIENCE,
	STAT_ITEM_HEALAFTERKILL,
	STAT_ITEM_REDUCEDPRICES,
	STAT_ITEM_DOUBLEHERBDURATION,
	STAT_ITEM_LIGHTRADIUS,
	STAT_ITEM_LIGHTCOLOR,
	STAT_ITEM_REQ_PERCENT,
	STAT_ITEM_LEVELREQ,
	STAT_ITEM_FASTERATTACKRATE,
	STAT_ITEM_LEVELREQPCT,
	STAT_LASTBLOCKFRAME,
	STAT_ITEM_FASTERMOVEVELOCITY,
	STAT_ITEM_NONCLASSSKILL,
	STAT_STATE,
	STAT_ITEM_FASTERGETHITRATE,
	STAT_MONSTER_PLAYERCOUNT,
	STAT_SKILL_POISON_OVERRIDE_LENGTH,
	STAT_ITEM_FASTERBLOCKRATE,
	STAT_SKILL_BYPASS_UNDEAD,
	STAT_SKILL_BYPASS_DEMONS,
	STAT_ITEM_FASTERCASTRATE,
	STAT_SKILL_BYPASS_BEASTS,
	STAT_ITEM_SINGLESKILL,
	STAT_ITEM_RESTINPEACE,
	STAT_CURSE_RESISTANCE,
	STAT_ITEM_POISONLENGTHRESIST,
	STAT_ITEM_NORMALDAMAGE,
	STAT_ITEM_HOWL,
	STAT_ITEM_STUPIDITY,
	STAT_ITEM_DAMAGETOMANA,
	STAT_ITEM_IGNORETARGETAC,
	STAT_ITEM_FRACTIONALTARGETAC,
	STAT_ITEM_PREVENTHEAL,
	STAT_ITEM_HALFFREEZEDURATION,
	STAT_ITEM_TOHIT_PERCENT,
	STAT_ITEM_DAMAGETARGETAC,
	STAT_ITEM_DEMONDAMAGE_PERCENT,
	STAT_ITEM_UNDEADDAMAGE_PERCENT,
	STAT_ITEM_DEMON_TOHIT,
	STAT_ITEM_UNDEAD_TOHIT,
	STAT_ITEM_THROWABLE,
	STAT_ITEM_ELEMSKILL,
	STAT_ITEM_ALLSKILLS,
	STAT_ITEM_ATTACKERTAKESLIGHTDAMAGE,
	STAT_IRONMAIDEN_LEVEL,
	STAT_LIFETAP_LEVEL,
	STAT_THORNS_PERCENT,
	STAT_BONEARMOR,
	STAT_BONEARMORMAX,
	STAT_ITEM_FREEZE,
	STAT_ITEM_OPENWOUNDS,
	STAT_ITEM_CRUSHINGBLOW,
	STAT_ITEM_KICKDAMAGE,
	STAT_ITEM_MANAAFTERKILL,
	STAT_ITEM_HEALAFTERDEMONKILL,
	STAT_ITEM_EXTRABLOOD,
	STAT_ITEM_DEADLYSTRIKE,
	STAT_ITEM_ABSORBFIRE_PERCENT,
	STAT_ITEM_ABSORBFIRE,
	STAT_ITEM_ABSORBLIGHT_PERCENT,
	STAT_ITEM_ABSORBLIGHT,
	STAT_ITEM_ABSORBMAGIC_PERCENT,
	STAT_ITEM_ABSORBMAGIC,
	STAT_ITEM_ABSORBCOLD_PERCENT,
	STAT_ITEM_ABSORBCOLD,
	STAT_ITEM_SLOW,
	STAT_ITEM_AURA,
	STAT_ITEM_INDESCTRUCTIBLE,
	STAT_ITEM_CANNOTBEFROZEN,
	STAT_ITEM_STAMINADRAINPCT,
	STAT_ITEM_REANIMATE,
	STAT_ITEM_PIERCE,
	STAT_ITEM_MAGICARROW,
	STAT_ITEM_EXPLOSIVEARROW,
	STAT_ITEM_THROW_MINDAMAGE,
	STAT_ITEM_THROW_MAXDAMAGE,
	STAT_SKILL_HANDOFATHENA,
	STAT_SKILL_STAMINAPERCENT,
	STAT_SKILL_PASSIVE_STAMINAPERCENT,
	STAT_SKILL_CONCENTRATION,
	STAT_SKILL_ENCHANT,
	STAT_SKILL_PIERCE,
	STAT_SKILL_CONVICTION,
	STAT_SKILL_CHILLINGARMOR,
	STAT_SKILL_FRENZY,
	STAT_SKILL_DECREPIFY,
	STAT_SKILL_ARMOR_PERCENT,
	STAT_ALIGNMENT,
	STAT_TARGET0,
	STAT_TARGET1,
	STAT_GOLDLOST,
	STAT_CONVERSION_LEVEL,
	STAT_CONVERSION_MAXHP,
	STAT_UNIT_DOOVERLAY,
	STAT_ATTACK_VS_MONTYPE,
	STAT_DAMAGE_VS_MONTYPE,
	STAT_FADE,
	STAT_ARMOR_OVERRIDE_PERCENT,
	STAT_UNUSED183,
	STAT_UNUSED184,
	STAT_UNUSED185,
	STAT_UNUSED186,
	STAT_UNUSED187,
	STAT_ITEM_ADDSKILL_TAB,
	STAT_UNUSED189,
	STAT_UNUSED190,
	STAT_UNUSED191,
	STAT_UNUSED192,
	STAT_UNUSED193,
	STAT_ITEM_NUMSOCKETS,
	STAT_ITEM_SKILLONATTACK,
	STAT_ITEM_SKILLONKILL,
	STAT_ITEM_SKILLONDEATH,
	STAT_ITEM_SKILLONHIT,
	STAT_ITEM_SKILLONLEVELUP,
	STAT_UNUSED200,
	STAT_ITEM_SKILLONGETHIT,
	STAT_UNUSED202,
	STAT_UNUSED203,
	STAT_ITEM_CHARGED_SKILL,
	STAT_UNUSED204,
	STAT_UNUSED205,
	STAT_UNUSED206,
	STAT_UNUSED207,
	STAT_UNUSED208,
	STAT_UNUSED209,
	STAT_UNUSED210,
	STAT_UNUSED211,
	STAT_UNUSED212,
	STAT_ITEM_ARMOR_PERLEVEL,
	STAT_ITEM_ARMORPERCENT_PERLEVEL,
	STAT_ITEM_HP_PERLEVEL,
	STAT_ITEM_MANA_PERLEVEL,
	STAT_ITEM_MAXDAMAGE_PERLEVEL,
	STAT_ITEM_MAXDAMAGE_PERCENT_PERLEVEL,
	STAT_ITEM_STRENGTH_PERLEVEL,
	STAT_ITEM_DEXTERITY_PERLEVEL,
	STAT_ITEM_ENERGY_PERLEVEL,
	STAT_ITEM_VITALITY_PERLEVEL,
	STAT_ITEM_TOHIT_PERLEVEL,
	STAT_ITEM_TOHITPERCENT_PERLEVEL,
	STAT_ITEM_COLD_DAMAGEMAX_PERLEVEL,
	STAT_ITEM_FIRE_DAMAGEMAX_PERLEVEL,
	STAT_ITEM_LTNG_DAMAGEMAX_PERLEVEL,
	STAT_ITEM_POIS_DAMAGEMAX_PERLEVEL,
	STAT_ITEM_RESIST_COLD_PERLEVEL,
	STAT_ITEM_RESIST_FIRE_PERLEVEL,
	STAT_ITEM_RESIST_LTNG_PERLEVEL,
	STAT_ITEM_RESIST_POIS_PERLEVEL,
	STAT_ITEM_ABSORB_COLD_PERLEVEL,
	STAT_ITEM_ABSORB_FIRE_PERLEVEL,
	STAT_ITEM_ABSORB_LTNG_PERLEVEL,
	STAT_ITEM_ABSORB_POIS_PERLEVEL,
	STAT_ITEM_THORNS_PERLEVEL,
	STAT_ITEM_FIND_GOLD_PERLEVEL,
	STAT_ITEM_FIND_MAGIC_PERLEVEL,
	STAT_ITEM_REGENSTAMINA_PERLEVEL,
	STAT_ITEM_STAMINA_PERLEVEL,
	STAT_ITEM_DAMAGE_DEMON_PERLEVEL,
	STAT_ITEM_DAMAGE_UNDEAD_PERLEVEL,
	STAT_ITEM_TOHIT_DEMON_PERLEVEL,
	STAT_ITEM_TOHIT_UNDEAD_PERLEVEL,
	STAT_ITEM_CRUSHINGBLOW_PERLEVEL,
	STAT_ITEM_OPENWOUNDS_PERLEVEL,
	STAT_ITEM_KICK_DAMAGE_PERLEVEL,
	STAT_ITEM_DEADLYSTRIKE_PERLEVEL,
	STAT_ITEM_FIND_GEMS_PERLEVEL,
	STAT_ITEM_REPLENISH_DURABILITY,
	STAT_ITEM_REPLENISH_QUANTITY,
	STAT_ITEM_EXTRA_STACK,
	STAT_ITEM_FIND_ITEM,
	STAT_ITEM_SLASH_DAMAGE,
	STAT_ITEM_SLASH_DAMAGE_PERCENT,
	STAT_ITEM_CRUSH_DAMAGE,
	STAT_ITEM_CRUSH_DAMAGE_PERCENT,
	STAT_ITEM_THRUST_DAMAGE,
	STAT_ITEM_THRUST_DAMAGE_PERCENT,
	STAT_ITEM_ABSORB_SLASH,
	STAT_ITEM_ABSORB_CRUSH,
	STAT_ITEM_ABSORB_THRUST,
	STAT_ITEM_ABSORB_SLASH_PERCENT,
	STAT_ITEM_ABSORB_CRUSH_PERCENT,
	STAT_ITEM_ABSORB_THRUST_PERCENT,
	STAT_ITEM_ARMOR_BYTIME,
	STAT_ITEM_ARMORPERCENT_BYTIME,
	STAT_ITEM_HP_BYTIME,
	STAT_ITEM_MANA_BYTIME,
	STAT_ITEM_MAXDAMAGE_BYTIME,
	STAT_ITEM_MAXDAMAGE_PERCENT_BYTIME,
	STAT_ITEM_STRENGTH_BYTIME,
	STAT_ITEM_DEXTERITY_BYTIME,
	STAT_ITEM_ENERGY_BYTIME,
	STAT_ITEM_VITALITY_BYTIME,
	STAT_ITEM_TOHIT_BYTIME,
	STAT_ITEM_TOHITPERCENT_BYTIME,
	STAT_ITEM_COLD_DAMAGEMAX_BYTIME,
	STAT_ITEM_FIRE_DAMAGEMAX_BYTIME,
	STAT_ITEM_LTNG_DAMAGEMAX_BYTIME,
	STAT_ITEM_POIS_DAMAGEMAX_BYTIME,
	STAT_ITEM_RESIST_COLD_BYTIME,
	STAT_ITEM_RESIST_FIRE_BYTIME,
	STAT_ITEM_RESIST_LTNG_BYTIME,
	STAT_ITEM_RESIST_POIS_BYTIME,
	STAT_ITEM_ABSORB_COLD_BYTIME,
	STAT_ITEM_ABSORB_FIRE_BYTIME,
	STAT_ITEM_ABSORB_LTNG_BYTIME,
	STAT_ITEM_ABSORB_POIS_BYTIME,
	STAT_ITEM_FIND_GOLD_BYTIME,
	STAT_ITEM_FIND_MAGIC_BYTIME,
	STAT_ITEM_REGENSTAMINA_BYTIME,
	STAT_ITEM_STAMINA_BYTIME,
	STAT_ITEM_DAMAGE_DEMON_BYTIME,
	STAT_ITEM_DAMAGE_UNDEAD_BYTIME,
	STAT_ITEM_TOHIT_DEMON_BYTIME,
	STAT_ITEM_TOHIT_UNDEAD_BYTIME,
	STAT_ITEM_CRUSHINGBLOW_BYTIME,
	STAT_ITEM_OPENWOUNDS_BYTIME,
	STAT_ITEM_KICK_DAMAGE_BYTIME,
	STAT_ITEM_DEADLYSTRIKE_BYTIME,
	STAT_ITEM_FIND_GEMS_BYTIME,
	STAT_ITEM_PIERCE_COLD,
	STAT_ITEM_PIERCE_FIRE,
	STAT_ITEM_PIERCE_LTNG,
	STAT_ITEM_PIERCE_POIS,
	STAT_ITEM_DAMAGE_VS_MONSTER,
	STAT_ITEM_DAMAGE_PERCENT_VS_MONSTER,
	STAT_ITEM_TOHIT_VS_MONSTER,
	STAT_ITEM_TOHIT_PERCENT_VS_MONSTER,
	STAT_ITEM_AC_VS_MONSTER,
	STAT_ITEM_AC_PERCENT_VS_MONSTER,
	STAT_FIRELENGTH,
	STAT_BURNINGMIN,
	STAT_BURNINGMAX,
	STAT_PROGRESSIVE_DAMAGE,
	STAT_PROGRESSIVE_STEAL,
	STAT_PROGRESSIVE_OTHER,
	STAT_PROGRESSIVE_FIRE,
	STAT_PROGRESSIVE_COLD,
	STAT_PROGRESSIVE_LIGHTNING,
	STAT_ITEM_EXTRA_CHARGES,
	STAT_PROGRESSIVE_TOHIT,
	STAT_POISON_COUNT,
	STAT_DAMAGE_FRAMERATE,
	STAT_PIERCE_IDX,
	STAT_PASSIVE_FIRE_MASTERY,
	STAT_PASSIVE_LTNG_MASTERY,
	STAT_PASSIVE_COLD_MASTERY,
	STAT_PASSIVE_POIS_MASTERY,
	STAT_PASSIVE_FIRE_PIERCE,
	STAT_PASSIVE_LTNG_PIERCE,
	STAT_PASSIVE_COLD_PIERCE,
	STAT_PASSIVE_POIS_PIERCE,
	STAT_PASSIVE_CRITICAL_STRIKE,
	STAT_PASSIVE_DODGE,
	STAT_PASSIVE_AVOID,
	STAT_PASSIVE_EVADE,
	STAT_PASSIVE_WARMTH,
	STAT_PASSIVE_MASTERY_MELEE_TH,
	STAT_PASSIVE_MASTERY_MELEE_DMG,
	STAT_PASSIVE_MASTERY_MELEE_CRIT,
	STAT_PASSIVE_MASTERY_THROW_TH,
	STAT_PASSIVE_MASTERY_THROW_DMG,
	STAT_PASSIVE_MASTERY_THROW_CRIT,
	STAT_PASSIVE_WEAPONBLOCK,
	STAT_PASSIVE_SUMMON_RESIST,
	STAT_MODIFIERLIST_SKILL,
	STAT_MODIFIERLIST_LEVEL,
	STAT_LAST_SENT_HP_PCT,
	STAT_SOURCE_UNIT_TYPE,
	STAT_SOURCE_UNIT_ID,
	STAT_SHORTPARAM1,
	STAT_QUESTITEMDIFFICULTY,
	STAT_PASSIVE_MAG_MASTERY,
	STAT_PASSIVE_MAG_PIERCE,
};

enum D2C_PropertyModes
{
	PROPMODE_AFFIX,
	PROPMODE_GRADE,
	PROPMODE_GEM,
	PROPMODE_UNIQUE,
	PROPMODE_SET,
	PROPMODE_RUNE,
	PROPMODE_RUNEWORD,
	PROPMODE_UNUSED
};

enum D2C_PropertySets
{
	PROPSET_WEAPON,
	PROPSET_HELM,
	PROPSET_SHIELD,
};

enum D2C_StatlistFlags : uint32_t
{
	STATLIST_BASE = 0x0,
	STATLIST_BASIC = 0x1,
	STATLIST_NEWLENGTH = 0x2,
	STATLIST_TEMPONLY = 0x4,
	STATLIST_BUFF = 0x8,
	STATLIST_CURSE = 0x20,
	STATLIST_MAGIC = 0x40,
	STATLIST_OVERLAY = 0x80,
	STATLIST_UNK_0x100 = 0x100,
	STATLIST_TOGGLE = 0x200,
	STATLIST_CONVERT = 0x800,
	STATLIST_SET = 0x2000,
	STATLIST_ITEM_EX = 0x200000,
	STATLIST_PERMANENT = 0x20000000,
	STATLIST_DYNAMIC = 0x40000000,
	STATLIST_EXTENDED = 0x80000000,
};

typedef int32_t D2SLayerStatId_PackedType;

#define struct_D2SLayerStatId(optionalName) struct optionalName \
{ \
	/* We can not use a struct as function parameters here as it has a different effect when using the __cdecl calling convetion. */ \
	/* Instead we just use D2SLayerStatId_PackedType so that we may easily change it later */ \
\
	union \
	{ \
		struct \
		{ \
			uint16_t nLayer;				/* 0x00 */ \
			uint16_t nStat;					/* 0x02 */ \
		}; \
		D2SLayerStatId_PackedType nPackedValue;			/* 0x00 */ \
	}; \
}
struct_D2SLayerStatId(D2SLayerStatId);

inline struct D2SLayerStatId D2SLayerStatId_Make(uint16_t wLayer, uint16_t wStatId) {
	return (struct D2SLayerStatId){ wLayer, wStatId };
}
inline struct D2SLayerStatId D2SLayerStatId_MakeFromStatId(uint16_t wStatId) {
	return (struct D2SLayerStatId){ 0, wStatId };
}
inline struct D2SLayerStatId D2SLayerStatId_FromPackedType(D2SLayerStatId_PackedType nPackedValue) {
	struct D2SLayerStatId ls;
	ls.nPackedValue = nPackedValue;
	return ls; 
}

struct D2Stat
{
	struct_D2SLayerStatId();
	int32_t nValue;							//0x04
};

enum : int {
	D2StatsArray_nGrowthAmount = 4,
	D2StatsArray_nShrinkThreshold = 8,
};

struct D2StatsArray
{
	struct D2Stat* pStat;						//0x00 An Array[wStatCount]
	uint16_t nStatCount;					//0x04
	uint16_t nCapacity;						//0x06
};

enum : int {
	D2ModStatsArray_nGrowthAmount = 4,
	D2ModStatsArray_nShrinkThreshold = 8,
};

struct D2ModStatsArray
{
	struct D2SLayerStatId* pStat;				//0x00 An Array[wStatCount]
	uint16_t nStatCount;					//0x04
	uint16_t nCapacity;						//0x06
};

struct D2StatList;

typedef void(__cdecl* StatListRemoveCallback)(struct D2Unit* pUnit, int32_t nState, struct D2StatList* pStatList);

#define struct_D2StatList(optionalName) struct optionalName \
{ \
	void* pMemPool;							/* 0x00 */ \
	struct D2Unit* pUnit;						/* 0x04 */ \
	uint32_t dwOwnerType;					/* 0x08*/ \
	uint32_t dwOwnerId;						/* 0x0C*/ \
	uint32_t dwFlags;						/* 0x10 D2C_StatlistFlags */ \
	uint32_t dwStateNo;						/* 0x14 */ \
	int32_t dwExpireFrame;					/* 0x18 */ \
	uint32_t dwSkillNo;						/* 0x1C */ \
	uint32_t dwSLvl;						/* 0x20 */ \
	struct D2StatsArray Stats;					/* 0x24 */ \
	struct D2StatList* pPrevLink;				/* 0x2C */ \
	struct D2StatList* pNextLink;				/* 0x30 */ \
	struct D2StatList* pParent;				/* 0x34 */ \
	StatListRemoveCallback fpStatRemove;	/* 0x38 */ \
}
struct_D2StatList(D2StatList);

typedef void(__cdecl* StatListValueChangeFunc)(struct D2Game*, struct D2Unit*, struct D2Unit*, int32_t, int32_t, int32_t);

struct D2StatListEx
{
	struct_D2StatList();
	struct D2StatList* pMyLastList;			//0x3C
	struct D2StatList* pMyStats;				//0x40
	struct D2Unit* pOwner;						//0x44
	struct D2StatsArray FullStats;				//0x48
	struct D2ModStatsArray ModStats;			//0x50
	uint32_t* StatFlags;					//0x58 8bytes per states
	StatListValueChangeFunc pfOnValueChanged;		//0x5C
	struct D2Game* pGame;						//0x60
};
#pragma pack()

// Helper function
inline struct D2StatListEx* STATLIST_StatListExCast(struct D2StatList* pStatList) {
	if (pStatList->dwFlags & STATLIST_EXTENDED)
	{
		return (struct D2StatListEx*)(pStatList);
	}
	return nullptr;
}

inline bool STATLIST_IsExtended(struct D2StatList* pStatList) { return pStatList->dwFlags & STATLIST_EXTENDED; }

inline int STAT_HitPointsFixedPointToInt(int nHP) { return nHP >> 8; }

//D2Common.0x6FDB57C0 (#10563)
D2COMMON_DLL_DECL BOOL __cdecl STATLIST_AreUnitsAligned(struct D2Unit* pUnit1, struct D2Unit* pUnit2);
//D2Common.0x6FDB5830
int __cdecl sub_6FDB5830(struct D2StatListEx* pStatListEx, D2SLayerStatId_PackedType nLayer_StatId);
//D2Common.0x6FDB6300
int __cdecl STATLIST_FindStatIndex_6FDB6300(struct D2StatsArray* pStatArray, D2SLayerStatId_PackedType nLayer_StatId);
//D2Common.0x6FDB6340
int __cdecl STATLIST_GetBaseStat_6FDB6340(struct D2StatList* pStatListEx, D2SLayerStatId_PackedType nLayer_StatId, struct D2ItemStatCostTxt* pItemStatCostTxtRecord);
//D2Common.0x6FDB63E0
int __cdecl STATLIST_GetTotalStat_6FDB63E0(struct D2StatList* pStatList, D2SLayerStatId_PackedType nLayer_StatId, struct D2ItemStatCostTxt* pItemStatCostTxtRecord);
//D2Common.0x6FDB64A0
int __cdecl sub_6FDB64A0(struct D2StatListEx* pStatListEx, D2SLayerStatId_PackedType nLayer_StatId, struct D2ItemStatCostTxt* pItemStatCostTxtRecord, struct D2Unit* pUnit);
//D2Common.0x6FDB6920
struct D2Stat* __cdecl STATLIST_FindStat_6FDB6920(struct D2StatsArray* pStatArray, D2SLayerStatId_PackedType nLayer_StatId);
//D2Common.0x6FDB6970
struct D2Stat* __cdecl STATLIST_InsertStatOrFail_6FDB6970(void* pMemPool, struct D2StatsArray* pStatsArray, D2SLayerStatId_PackedType nLayer_StatId);
//D2Common.0x6FDB6A30
void __cdecl STATLIST_RemoveStat_6FDB6A30(void* pMemPool, struct D2StatsArray* pStatEx, struct D2Stat* pStat);
//D2Common.0x6FDB6AB0
void __cdecl STATLIST_UpdateUnitStat_6FDB6AB0(struct D2StatListEx* pStatList, D2SLayerStatId_PackedType nLayer_StatId, int nNewValue, struct D2ItemStatCostTxt* pItemStatCostTxtRecord, struct D2Unit* pUnit);
//D2Common.0x6FDB6C10
void __cdecl sub_6FDB6C10(struct D2StatListEx* pStatListEx, D2SLayerStatId_PackedType nLayer_StatId, int nValue, struct D2Unit* pUnit);
//D2Common.0x6FDB6E30
void __cdecl D2Common_ExpireStatList_6FDB6E30(struct D2StatList* pStatList);
//D2Common.0x6FDB7030 (#10485)
D2COMMON_DLL_DECL void __cdecl STATLIST_FreeStatList(struct D2StatList* pStatList);
//D2Common.0x6FDB7050
void __cdecl D2Common_STATLIST_FreeStatListImpl_6FDB7050(struct D2StatList* pStatList);
//D2Common.0x6FDB7110 (#10527)
D2COMMON_DLL_DECL void __cdecl STATLIST_FreeStatListEx(struct D2Unit* pUnit);
//D2Common.0x6FDB7140 (#10470)
D2COMMON_DLL_DECL struct D2StatList* __cdecl STATLIST_AllocStatList(void* pMemPool, uint32_t fFilter, uint32_t dwTimeout, int nUnitType, D2UnitGUID nUnitGUID);
//D2Common.0x6FDB7190 (#10526)
D2COMMON_DLL_DECL void __cdecl STATLIST_AllocStatListEx(struct D2Unit* pUnit, char nFlags, StatListValueChangeFunc pfOnValueChanged, struct D2Game* pGame);
//D2Common.0x6FDB7260 (#10471)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetOwnerType(struct D2StatList* pStatList);
//D2Common.0x6FD912D0 (#10472)
D2COMMON_DLL_DECL D2UnitGUID __cdecl STATLIST_GetOwnerGUID(struct D2StatList* pStatList);
//D2Common.0x6FDB7280 (#11304)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetBaseStatsCount(struct D2StatList* pStatList);
//D2Common.0x6FDB72A0 (#11305)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetFullStatsCountFromUnit(struct D2Unit* pUnit);
//D2Common.0x6FDB72C0 (#10478)
D2COMMON_DLL_DECL void __cdecl STATLIST_SetState(struct D2StatList* pStatList, int nState);
//D2Common.0x6FDB72E0 (#10479)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetState(struct D2StatList* pStatList);
//D2Common.0x6FDB7300 (#10528)
D2COMMON_DLL_DECL void __cdecl STATLIST_SetExpireFrame(struct D2StatList* pStatList, int nExpireFrame);
//D2Common.0x6FDB7320 (#10529)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetExpireFrame(struct D2StatList* pStatList);
//D2Common.0x6FDB7340 (#10475)
D2COMMON_DLL_DECL void __cdecl D2COMMON_10475_PostStatToStatList(struct D2Unit* pUnit, struct D2StatList* pStatList, BOOL bResetFlag);
//D2Common.0x6FDB7560 (#10464)
D2COMMON_DLL_DECL void __cdecl STATLIST_AddStat(struct D2StatList* pStatList, int nStatId, int nValue, uint16_t nLayer);
//D2Common.0x6FDB7690
void __cdecl STATLIST_InsertStatModOrFail_6FDB7690(struct D2StatList* pStatList, D2SLayerStatId_PackedType nLayer_StatId);
//D2Common.0x6FDB77B0 (#10463)
D2COMMON_DLL_DECL BOOL __cdecl STATLIST_SetStat(struct D2StatList* pStatList, int nStatId, int nValue, uint16_t nLayer);
//D2Common.0x6FDB7910 (#10465)
D2COMMON_DLL_DECL void __cdecl STATLIST_SetStatIfListIsValid(struct D2StatList* pStatList, int nStatId, int nValue, uint16_t nLayer);
//D2Common.0x6FDB7930 (#11294)
D2COMMON_DLL_DECL BOOL __cdecl STATLIST_SetBaseStat(struct D2StatList* pStatList, int nStatId, int nValue, uint16_t nLayer, struct D2Unit* pUnit);
//D2Common.0x6FDB7A90 (#11295)
D2COMMON_DLL_DECL //Duplicate of STATLIST_SetBaseStat#11294
void __cdecl STATLIST_SetBaseStat2(struct D2StatList* pStatList, int nStatId, int nValue, uint16_t nLayer, struct D2Unit* pUnit);
//D2Common.0x6FDB7AB0 (#10517)
D2COMMON_DLL_DECL void __cdecl STATLIST_SetUnitStat(struct D2Unit* pUnit, int nStatId, int nValue, uint16_t nLayer);
//D2Common.0x6FDB7B00 (#10518)
D2COMMON_DLL_DECL void __cdecl STATLIST_AddUnitStat(struct D2Unit* pUnit, int nStatId, int nValue, uint16_t nLayer);
//D2Common.0x6FDB7C30 (#10519)
D2COMMON_DLL_DECL int32_t __cdecl STATLIST_UnitGetStatValue(const struct D2Unit* pUnit, int nStatId, uint16_t nLayer);
//D2Common.0x6FDB7E30 (#10520)
D2COMMON_DLL_DECL int32_t __cdecl STATLIST_UnitGetItemStatOrSkillStatValue(struct D2Unit* pUnit, int nStatId, uint16_t nLayer);
//D2Common.0x6FDB7B30 (#10521)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetUnitBaseStat(struct D2Unit* pUnit, int nStatId, uint16_t nLayer);
//D2Common.0x(6FDB7D40 (#10466)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetStatValue(struct D2StatList* pStatList, int nStatId, uint16_t nLayer);
//D2Common.0x6FDB7F40 (#10522)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetUnitStatBonus(struct D2Unit* pUnit, int nStatId, uint16_t nLayer);
//D2Common.0x6FDB80C0 (#10515)
D2COMMON_DLL_DECL void __cdecl STATLIST_DeactivateTemporaryStates(struct D2Unit* pUnit);
//D2Common.0x6FDB8120 (#10467)
D2COMMON_DLL_DECL int __cdecl D2Common_10467(struct D2StatList* pStatList, int nStat);
//D2Common.0x6FDB8150 (#10468)
D2COMMON_DLL_DECL void __cdecl STATLIST_RemoveAllStats(struct D2StatList* pStatList);
//D2Common.0x6FDB8190
struct D2StatList* __cdecl D2Common_GetStateFromStatListEx_6FDB8190(struct D2StatListEx* pStatListEx, int nStateId);
//D2Common.0x6FDB81E0 (#10480)
D2COMMON_DLL_DECL struct D2StatList* __cdecl STATLIST_GetStatListFromUnitAndState(struct D2Unit* pUnit, int nState);
//D2Common.0x6FDB8200 (#10482)
D2COMMON_DLL_DECL struct D2StatList* __cdecl STATLIST_GetStatListFromFlag(struct D2StatList* pStatList, int nFlag);
//D2Common.0x6FDB8230 (#10481)
D2COMMON_DLL_DECL struct D2StatList* __cdecl STATLIST_GetStatListFromUnitAndFlag(struct D2Unit* pUnit, int nFlag);
//D2Common.0x6FDB8270 (#10483)
D2COMMON_DLL_DECL struct D2StatList* __cdecl STATLIST_GetStatListFromUnitStateOrFlag(struct D2Unit* pUnit, int nState, int nFlag);
//D2Common.0x6FDB82C0 (#10484)
D2COMMON_DLL_DECL struct D2StatList* __cdecl STATLIST_GetStatListFromUnitStateAndFlag(struct D2Unit* pUnit, int nState, int nFlag);
//D2Common.0x6FDB8310 (#10523)
D2COMMON_DLL_DECL void __cdecl STATLIST_MergeStatLists(struct D2Unit* pTarget, struct D2Unit* pUnit, BOOL bType);
//D2Common.0x6FDB83A0 (#10535)
D2COMMON_DLL_DECL struct D2Unit* __cdecl STATLIST_GetOwner(struct D2Unit* pUnit, BOOL* pStatNotDynamic);
//D2Common.0x6FDB8420 (#10512)
D2COMMON_DLL_DECL void __cdecl D2Common_10512(struct D2Unit* pUnit1, struct D2Unit* pUnit2, int nStatId, void(__cdecl* pfCallback)(struct D2Unit*, int, int, struct D2Unit*));
//D2Common.0x6FDB84E0 (#10513)
D2COMMON_DLL_DECL void __cdecl D2Common_10513(struct D2Unit* pUnit1, struct D2Unit* pUnit2, void(__cdecl* pfCallback)(struct D2Unit*, int, int, struct D2Unit*));
//D2Common.0x6FDB85D0 (#10511)
D2COMMON_DLL_DECL void __cdecl STATLIST_FreeModStats(struct D2Unit* pUnit);
//D2Common.0x6FDB8620 (#10562)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetUnitAlignment(struct D2Unit* pUnit);
//D2Common.0x6FDB8750 (#10534)
D2COMMON_DLL_DECL void __cdecl D2Common_10534(struct D2Unit* pUnit);
//D2Common.0x6FDB8770 (#10530)
D2COMMON_DLL_DECL BOOL __cdecl D2COMMON_10530_D2CheckStatlistFlagDMGRed(struct D2Unit* pUnit);
//D2Common.0x6FDB87A0 (#10532)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetTotalStatValue_Layer0(struct D2StatList* pStatListEx, int nStatId);
//D2Common.0x6FDB8890 (#10533)
D2COMMON_DLL_DECL void __cdecl STATLIST_RemoveAllStatsFromOverlay(struct D2Unit* pUnit);
//D2Common.0x6FDB8900
void __cdecl D2Common_STATES_ToggleState_6FDB8900(struct D2Unit* pUnit, int nState, BOOL bSet);
//D2Common.0x6FDB8A90
uint32_t* __cdecl D2COMMON_STATES_GetStatFlags_6FDB8A90(struct D2Unit* pUnit);
//D2Common.0x6FDB8AC0
uint32_t* __cdecl D2COMMON_STATES_GetListGfxFlags_6FDB8AC0(struct D2Unit* pUnit);
//D2Common.0x6FDB8B10 (#10516)
D2COMMON_DLL_DECL // If nFrame == 0 (client), decrements dwExpireFrame, otherwise only frees the expired lists
void __cdecl STATLIST_UpdateStatListsExpiration(struct D2Unit* pUnit, int nFrame);
//D2Common.0x6FDB8BA0 (#11268)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetFullStatsDataFromUnit(struct D2Unit* pUnit, struct D2Stat* pOutStatBuffer, int nBufferSize);
//D2Common.0x6FDB8C00 (#11243)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetBaseStatsData(struct D2StatList* pStatListEx, struct D2Stat* pOutStatBuffer, int nBufferSize);
//D2Common.0x6FDB8C50 (#10573)
D2COMMON_DLL_DECL void __cdecl STATLIST_MergeBaseStats(struct D2StatList* pTargetStatList, struct D2StatList* pSourceStatlist);
//D2Common.0x6FDB8CA0 (#10477)
D2COMMON_DLL_DECL void __cdecl STATLIST_SetStatRemoveCallback(struct D2StatList* pStatList, StatListRemoveCallback pfStatRemove);
//D2Common.0x6FDB8CC0 (#10469)
D2COMMON_DLL_DECL void __cdecl D2Common_10469(struct D2Unit* pUnit);
//D2Common.0x6FDB8D30 (#10514)
D2COMMON_DLL_DECL void __cdecl STATLIST_ClampStaminaManaHP(struct D2Unit* pUnit);
//D2Common.0x6FDB8EB0 (#10574)
D2COMMON_DLL_DECL BOOL __cdecl D2Common_10574(struct D2Unit* pUnit, int nStateId, BOOL bSet);
//D2Common.0x6FDB8F30 (#10525)
D2COMMON_DLL_DECL void __cdecl D2Common_10525(struct D2Unit* pUnit1, struct D2Unit* pUnit2);
//D2Common.0x6FDB91C0 (#10474)
D2COMMON_DLL_DECL void __cdecl D2Common_10474(struct D2Unit* pUnused, struct D2StatList* pStatList);
//D2Common.0x6FDB91D0 (#10564)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetMaxLifeFromUnit(struct D2Unit* pUnit);
//D2Common.0x6FDB92C0 (#10565)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetMaxManaFromUnit(struct D2Unit* pUnit);
//D2Common.0x6FDB93B0 (#10566)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetMaxStaminaFromUnit(struct D2Unit* pUnit);
//D2Common.0x6FDB94A0 (#10567)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetMaxDurabilityFromUnit(struct D2Unit* pUnit);
//D2Common.0x6FDB95D0 (#10568)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetMaxDamageFromUnit(struct D2Unit* pUnit, BOOL b2Handed);
//D2Common.0x6FDB96F0 (#10569)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetMinDamageFromUnit(struct D2Unit* pUnit, BOOL b2Handed);
//D2Common.0x6FDB9810 (#10570)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetMaxThrowDamageFromUnit(struct D2Unit* pUnit);
//D2Common.0x6FDB9900 (#10571)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetMinThrowDamageFromUnit(struct D2Unit* pUnit);
//D2Common.0x6FDB99F0 (#10572)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetDefenseFromUnit(struct D2Unit* pUnit);
//D2Common.0x6FDB9AE0 (#10524)
D2COMMON_DLL_DECL void __cdecl STATLIST_ExpireUnitStatlist(struct D2Unit* pUnused, struct D2Unit* pUnit);
//D2Common.0x6FDB9B00 (#10531)
D2COMMON_DLL_DECL int __cdecl D2Common_10531_SetStatInStatListLayer0(struct D2StatList* pStatList, int nStatId, int nValue, int nUnused);
//D2Common.0x6FDB9B10 (#11248)
D2COMMON_DLL_DECL int __cdecl D2Common_11248(struct D2Unit* pUnused, struct D2Unit* pUnit, int nStatId);
//D2Common.0x6FDA9E60 (#11264)
D2COMMON_DLL_DECL void __cdecl STATLIST_SetSkillId(struct D2StatList* pStatList, int nSkillId);
//D2Common.0x6FDB9C10 (#11265)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetSkillId(struct D2StatList* pStatList);
//D2Common.0x6FDB9C20 (#11266)
D2COMMON_DLL_DECL void __cdecl STATLIST_SetSkillLevel(struct D2StatList* pStatList, int nSkillLevel);
//D2Common.0x6FDA9E70 (#11267)
D2COMMON_DLL_DECL int __cdecl STATLIST_GetSkillLevel(struct D2StatList* pStatList);
//D2Common.0x6FDB9C30 (#11269)
D2COMMON_DLL_DECL int __cdecl D2COMMON_11269_CopyStats(struct D2StatListEx* pStatListEx, int nStatId, struct D2Stat* pBuffer, int nBufferSize);
//D2Common.0x6FDB9C50
int __cdecl D2Common_CopyStats_6FDB9C50(struct D2StatList* pStatListEx, int nStatId, struct D2Stat* pBuffer, int nBufferSize);
//D2Common.0x6FDB9D20 (#11270)
D2COMMON_DLL_DECL int __cdecl STATLIST_CopyStats(struct D2Unit* pUnit, int nStatId, struct D2Stat* pBuffer, int nBufferSize);
//D2Common.0x6FDB9D60 (#11273)
D2COMMON_DLL_DECL int __cdecl D2Common_11273(struct D2Unit* pUnit, int nStatId);
//D2Common.0x6FDB9D90 (#11274)
D2COMMON_DLL_DECL BOOL __cdecl D2Common_11274(struct D2Unit* pTarget, struct D2Unit* pUnit);
//D2Common.0x6FDB9E60 (#11275)
D2COMMON_DLL_DECL BOOL __cdecl D2Common_11275(struct D2Unit* pTarget, struct D2Unit* pUnit);
