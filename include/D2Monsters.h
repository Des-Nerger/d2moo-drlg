#pragma once

#include "D2CommonDefinitions.h"
#include <D2Unicode.h>


struct D2Unit;
struct D2ActiveRoom;
struct D2MonStatsTxt;

#pragma pack(1)

enum D2InactiveMonsterFlags
{
	INACTIVEMONSTERFLAG_TYPE_OTHER = 0x00000001,
	INACTIVEMONSTERFLAG_TYPE_CHAMPION = 0x00000002,
	INACTIVEMONSTERFLAG_DEAD = 0x00000004,
	INACTIVEMONSTERFLAG_MINIONRELATED1 = 0x00000008,
	INACTIVEMONSTERFLAG_MINIONRELATED2 = 0x00000010,
	INACTIVEMONSTERFLAG_TYPE_MINION = 0x00000020,
	INACTIVEMONSTERFLAG_UNKSUMMONERFLAG = 0x00000040,
	INACTIVEMONSTERFLAG_ALIGNMENT_NEUTRAL = 0x00000080,
	INACTIVEMONSTERFLAG_ALIGNMENT_GOOD = 0x00000100,
	INACTIVEMONSTERFLAG_ALIGNMENT_EVIL = 0x00000200,
	INACTIVEMONSTERFLAG_NODEINDEXUNEQUAL11 = 0x00000400,
	INACTIVEMONSTERFLAG_TYPE_SUPERUNIQUE = 0x00000800,
};

enum D2C_MonTypeFlags
{
	MONTYPEFLAG_OTHER = 0x01,
	MONTYPEFLAG_SUPERUNIQUE = 0x02,
	MONTYPEFLAG_CHAMPION = 0x04,
	MONTYPEFLAG_UNIQUE = 0x08,
	MONTYPEFLAG_MINION = 0x10,
	MONTYPEFLAG_POSSESSED = 0x20,
	MONTYPEFLAG_GHOSTLY = 0x40,
	MONTYPEFLAG_MULTISHOT = 0x80
};

enum D2C_MonModes
{
	MONMODE_DEATH, 		//0x00 Death DT
	MONMODE_NEUTRAL, 	//0x01 Neutral NU
	MONMODE_WALK, 		//0x02 Walk WL
	MONMODE_GETHIT, 	//0x03 Get Hit GH
	MONMODE_ATTACK1, 	//0x04 Melee Attack A1
	MONMODE_ATTACK2, 	//0x05 Melee Attack A2
	MONMODE_BLOCK, 		//0x06 Block BL
	MONMODE_CAST, 		//0x07 Spell Cast SC
	MONMODE_SKILL1, 	//0x08 Special S1
	MONMODE_SKILL2, 	//0x09 Special S2
	MONMODE_SKILL3, 	//0x0A Special S3
	MONMODE_SKILL4, 	//0x0B Special S4
	MONMODE_DEAD, 		//0x0C Dead DD
	MONMODE_KNOCKBACK, 	//0x0D Knockback KB
	MONMODE_SEQUENCE, 	//0x0E Sequence SQ
	MONMODE_RUN,		//0x0F Run RN
	NUMBER_OF_MONMODES
};

enum D2C_MercenaryClasses
{
	MERC_A1 = 0x10F, 	//Monstats Id Act 1 Mercenary
	MERC_A2 = 0x152, 	//Monstats Id Act 2 Mercenary
	MERC_A3 = 0x167, 	//Monstats Id Act 3 Mercenary
	MERC_A5 = 0x231		//Monstats Id Act 5 Mercenary
};

enum D2C_PetWarpMode
{
	PETMOVE_OWNERROOM,
	PETMOVE_OWNERPOS,
	PETMOVE_TOWNIDLE,
	PETMOVE_TELE,
	PETMOVE_SCATTER,
	PETMOVE_IDLE
};

enum D2C_MonUMods
{
	MONUMOD_NONE, 					//none
	MONUMOD_RNDNAME, 				//randomized name
	MONUMOD_HPMULTIPLY, 			//adds life%
	MONUMOD_LIGHT, 					//increased light radius
	MONUMOD_LEVELADD, 				//adds three mlvl
	MONUMOD_EXTRASTRONG, 			//extra strong, dmg
	MONUMOD_EXTRAFAST, 				//extra fast, faster
	MONUMOD_CURSED, 				//amplify damage on hit
	MONUMOD_MAGICRESISTANT, 		//increased elemental resists
	MONUMOD_FIRECHANT, 				//fire enchanted
	MONUMOD_POISDEATH, 				//poison cloud on death
	MONUMOD_WORMDEATH, 				//releases worms and insects on death (Duriel)
	MONUMOD_BRAVENDEATH, 			//only works for Blood raven
	MONUMOD_IGNOREAC, 				//Ignore defense
	MONUMOD_SPCDAMAGE, 				//unknown
	MONUMOD_KILLMINIONSDEATH, 		//all minions of the boss die when the boss is killed
	MONUMOD_CHAMPMODS, 				//related to champions mods
	MONUMOD_LIGHTCHANT, 			//lightning enchanted
	MONUMOD_COLDCHANT, 				//cold enchanted
	MONUMOD_UNUSEDMERCMOD, 			//old unused mercenary dmg mod, buggy
	MONUMOD_CHARGEDBOLTS, 			//charged bolts when struck (scarabs)
	MONUMOD_TEMPSUMMON, 			//used by summons that that are destroyed after a set time
	MONUMOD_QUESTMOD, 				//related to quests
	MONUMOD_POISONFIELD, 			//the boss is dealing poison damage in an aura-like method
	MONUMOD_THIEF, 					//unused, thief mod
	MONUMOD_MANABURN, 				//mana burn
	MONUMOD_TELEHEAL, 				//teleports randomly and heal
	MONUMOD_SPECTRALHIT, 			//spectral hit, elemental damage
	MONUMOD_STONESKIN, 				//physical resistance
	MONUMOD_MULTISHOT, 				//multi-shot
	MONUMOD_AURACHANT, 				//aura enchanted, random aura when eqquipped (from aura table)
	MONUMOD_CORPSEBOOMDEATH, 		//explosion of the corpse on death
	MONUMOD_FIREBOOMDEATH, 			//fire explosion on death
	MONUMOD_FREEZINDEATH, 			//freeze you on death
	MONUMOD_SELFRESURRECT, 			//self-resurrect for reanimated-horde
	MONUMOD_ICESHATTERDEATH, 		//ice shatter on death
	MONUMOD_CHAMPSTONED, 			//slowed down but stronger, for champions
	MONUMOD_CHAMPSTATS, 			//champs stats related
	MONUMOD_CHAMPCURSEIMMUNE, 		//champion cannot be cursed
	MONUMOD_CHAMPSTATS2, 			//related to champ stats
	MONUMOD_PAINWORMDEATH, 			//summons a pain work on death
	MONUMOD_ALWAYSRUNAI, 			//unknown
	MONUMOD_NOVADEATH				//nova on death
};


enum D2MapAIActions
{
	AIACTION_MODE_NU = 1,
	AIACTION_MODE_S1 = 4,
	AIACTION_MODE_S2 = 5,
};

struct D2HirelingInit
{
	int32_t nId;								//0x00
	int32_t nLevel;								//0x04
	int32_t nHitpoints;							//0x08
	int32_t nStrength;							//0x0C
	int32_t nDexterity;							//0x10
	int32_t nGold;								//0x14
	int32_t nExperience;						//0x18
	int32_t nDefense;							//0x1C
	int32_t nMinDamage;							//0x20
	int32_t nMaxDamage;							//0x24
	int32_t nShare;								//0x28
	int32_t nResist;							//0x2C
	int32_t nHireDesc;							//0x30
	int32_t field_34;							//0x34
	int16_t nFlags;							//0x38
};
#pragma pack()

//D2Common.0x6FDA4C10 (#11082)
D2COMMON_DLL_DECL int __cdecl MONSTERS_HirelingInit(BOOL bExpansion, struct D2Unit* pMonster, int nLowSeed, int nAct, int nDifficulty, struct D2HirelingInit* pHirelingInit);
//D2Common.0x6FDA4E20 (#11081)
D2COMMON_DLL_DECL BOOL __cdecl D2Common_11081(int nLowSeed, struct D2HirelingInit* pHirelingInit, uint8_t a3);
//D2Common.0x6FDA51A0 (#11085)
D2COMMON_DLL_DECL const struct Unicode* __cdecl MONSTERS_GetHirelingDescString(int nId);
//D2Common.0x6FDA51C0 (#11086)
D2COMMON_DLL_DECL int __cdecl MONSTERS_GetActFromHirelingTxt(BOOL bExpansion, int nClassId, uint16_t nNameId);
//D2Common.0x6FDA5200 (#11084)
D2COMMON_DLL_DECL int __cdecl MONSTERS_GetHirelingExpForNextLevel(int nLevel, int nExpPerLevel);
//D2Common.0x6FDA5220 (#11083)
D2COMMON_DLL_DECL int __cdecl MONSTERS_GetHirelingResurrectionCost(struct D2Unit* pHireling);
//D2Common.0x6FDA5270 (#11068)
D2COMMON_DLL_DECL int __cdecl D2COMMON_11068_GetCompInfo(struct D2Unit* pMonster, int nComponent);
//D2Common.0x6FDA52F0 (#11069)
D2COMMON_DLL_DECL uint32_t __cdecl D2Common_11069(struct D2Unit* pMonster, unsigned int nIndex, unsigned int nComponent);
//D2Common.0x6FDA5450 (#11070)
D2COMMON_DLL_DECL int __cdecl D2Common_11070(int nMonsterId, unsigned int nComponent, unsigned int a3);
//D2Common.0x6FDA54E0 (#11050)
D2COMMON_DLL_DECL int __cdecl D2Common_11050(struct D2Unit* pUnit, int a2);
//D2Common.0x6FDA55E0 (#11052)
D2COMMON_DLL_DECL uint8_t __cdecl D2Common_11052(uint8_t a1);
//D2Common.0x6FDA5600 (#11053)
D2COMMON_DLL_DECL uint8_t __cdecl D2Common_11053(uint8_t a1);
//D2Common.0x6FDA5620 (#11054)
D2COMMON_DLL_DECL uint8_t __cdecl D2Common_11054(uint8_t a1);
//D2Common.0x6FDA5640 (#11055)
D2COMMON_DLL_DECL void __cdecl D2Common_11055(uint8_t a1, int* a2, int* a3);
//D2Common.0x6FDA5670 (#11297)
D2COMMON_DLL_DECL void __cdecl MONSTERS_SetMonsterNameInMonsterData(struct D2Unit* pMonster, const struct Unicode* wszName);
//D2Common.0x6FDA56C0
BOOL __cdecl MONSTERS_CanBeInTown(struct D2Unit* pMonster);
//D2Common.0x6FDA5750 (#11057)
D2COMMON_DLL_DECL BOOL __cdecl MONSTERS_IsSandLeaper(struct D2Unit* pMonster, BOOL bAlwaysReturnFalse);
//D2Common.0x6FDA57D0 (#11058)
D2COMMON_DLL_DECL BOOL __cdecl MONSTERS_IsDemon(struct D2Unit* pMonster);
//D2Common.0x6FDA5830 (#11059)
D2COMMON_DLL_DECL BOOL __cdecl MONSTERS_IsUndead(struct D2Unit* pMonster);
//D2Common.0x6FDA58A0 (#11060)
D2COMMON_DLL_DECL BOOL __cdecl MONSTERS_IsBoss(struct D2MonStatsTxt* pMonStatsTxtRecord, struct D2Unit* pMonster);
//D2Common.0x6FDA5900 (#11064)
D2COMMON_DLL_DECL BOOL __cdecl MONSTERS_IsDead(struct D2Unit* pMonster);
//D2Common.0x6FDA5930 (#11280)
D2COMMON_DLL_DECL int __cdecl MONSTERS_GetSpawnMode_XY(struct D2Unit* pMonster, BOOL bFromMonster, int nSkillId, int nSkillLevel, int* pSpawnMode, int* pX, int* pY);
//D2Common.0x6FDA5B30 (#11061)
D2COMMON_DLL_DECL void __cdecl MONSTERS_GetMinionSpawnInfo(struct D2Unit* pMonster, int* pId, int* pX, int* pY, int* pSpawnMode, int nDifficulty, int(__cdecl* pfSpawnClassCallback)(struct D2Unit*));
//D2Common.0x6FDA6410 (#11051)
D2COMMON_DLL_DECL uint8_t __cdecl MONSTERS_GetMaximalLightRadius(struct D2Unit* pMonster);
//D2Common.0x6FDA64B0 (#11063)
D2COMMON_DLL_DECL int __cdecl D2Common_11063(struct D2ActiveRoom* pRoom, int nMonsterId);
//D2Common.0x6FDA6620 (#11065)
D2COMMON_DLL_DECL BOOL __cdecl MONSTERS_IsPrimeEvil(struct D2Unit* pMonster);
//D2Common.0x6FDA6680 (#11066)
D2COMMON_DLL_DECL void __cdecl D2Common_11066(struct D2Unit* pMonster, int* pDirectionX, int* pDirectionY);
//D2Common.0x6FDA6730 (#11067)
D2COMMON_DLL_DECL int __cdecl MONSTERS_GetHirelingTypeId(struct D2Unit* pHireling);
//D2Common.0x6FDA6790 (#11246)
D2COMMON_DLL_DECL void __cdecl MONSTERS_ApplyClassicScaling(struct D2Unit* pMonster, BOOL bExpansion, uint8_t nDifficulty);
//D2Common.0x6FDA6920
int __cdecl MONSTERS_GetBaseIdFromMonsterId(int nMonsterId);
//D2Common.0x6FDA6950
int __cdecl MONSTERS_GetClassIdFromMonsterChain(int nMonsterId, int nChainId);
//D2Common.0x6FDA69C0
int __cdecl MONSTERS_ValidateMonsterId(int nMonsterId);
