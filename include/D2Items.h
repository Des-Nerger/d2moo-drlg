#pragma once

#include "D2CommonDefinitions.h"
#include <DataTbls/ItemsTbls.h>
#include <Units/Units.h>

struct D2Game; // From D2Game
struct D2StatList;

#pragma pack(1)

enum D2C_ItemQualities
{
	ITEMQUAL_INFERIOR = 0x01, 	//0x01 Inferior
	ITEMQUAL_NORMAL = 0x02, 	//0x02 Normal
	ITEMQUAL_SUPERIOR = 0x03, 	//0x03 Superior
	ITEMQUAL_MAGIC = 0x04, 		//0x04 Magic
	ITEMQUAL_SET = 0x05, 		//0x05 Set
	ITEMQUAL_RARE = 0x06, 		//0x06 Rare
	ITEMQUAL_UNIQUE = 0x07, 	//0x07 Unique
	ITEMQUAL_CRAFT = 0x08, 		//0x08 Crafted
	ITEMQUAL_TEMPERED = 0x09	//0x09 Tempered
};

enum D2C_ItemTypes
{
	ITEMTYPE_NONE_1 = 0,
	ITEMTYPE_NONE_2,
	ITEMTYPE_SHIELD,
	ITEMTYPE_ARMOR,
	ITEMTYPE_GOLD,
	ITEMTYPE_BOW_QUIVER,
	ITEMTYPE_CROSSBOW_QUIVER,
	ITEMTYPE_PLAYER_BODY_PART,
	ITEMTYPE_HERB,
	ITEMTYPE_POTION,
	ITEMTYPE_RING,
	ITEMTYPE_ELIXIR,
	ITEMTYPE_AMULET,
	ITEMTYPE_CHARM,
	ITEMTYPE_NONE_3,
	ITEMTYPE_BOOTS,
	ITEMTYPE_GLOVES,
	ITEMTYPE_NONE_4,
	ITEMTYPE_BOOK,
	ITEMTYPE_BELT,
	ITEMTYPE_GEM,
	ITEMTYPE_TORCH,
	ITEMTYPE_SCROLL,
	ITEMTYPE_NONE_5,
	ITEMTYPE_SCEPTER,
	ITEMTYPE_WAND,
	ITEMTYPE_STAFF,
	ITEMTYPE_BOW,
	ITEMTYPE_AXE,
	ITEMTYPE_CLUB,
	ITEMTYPE_SWORD,
	ITEMTYPE_HAMMER,
	ITEMTYPE_KNIFE,
	ITEMTYPE_SPEAR,
	ITEMTYPE_POLEARM,
	ITEMTYPE_CROSSBOW,
	ITEMTYPE_MACE,
	ITEMTYPE_HELM,
	ITEMTYPE_MISSILE_POTION,
	ITEMTYPE_QUEST,
	ITEMTYPE_BODY_PART,
	ITEMTYPE_KEY,
	ITEMTYPE_THROWING_KNIFE,
	ITEMTYPE_THROWING_AXE,
	ITEMTYPE_JAVELIN,
	ITEMTYPE_WEAPON,
	ITEMTYPE_MELEE_WEAPON,
	ITEMTYPE_MISSILE_WEAPON,
	ITEMTYPE_THROWN_WEAPON,
	ITEMTYPE_COMBO_WEAPON,
	ITEMTYPE_ANY_ARMOR,
	ITEMTYPE_ANY_SHIELD,
	ITEMTYPE_MISCELLANEOUS,
	ITEMTYPE_SOCKET_FILLER,
	ITEMTYPE_SECOND_HAND,
	ITEMTYPE_STAVES_AND_RODS,
	ITEMTYPE_MISSILE,
	ITEMTYPE_BLUNT,
	ITEMTYPE_JEWEL,
	ITEMTYPE_CLASS_SPECIFIC,
	ITEMTYPE_AMAZON_ITEM,
	ITEMTYPE_BARBARIAN_ITEM,
	ITEMTYPE_NECROMANCER_ITEM,
	ITEMTYPE_PALADIN_ITEM,
	ITEMTYPE_SORCERESS_ITEM,
	ITEMTYPE_ASSASSIN_ITEM,
	ITEMTYPE_DRUID_ITEM,
	ITEMTYPE_HAND_TO_HAND,
	ITEMTYPE_ORB,
	ITEMTYPE_VOODOO_HEADS,
	ITEMTYPE_AURIC_SHIELDS,
	ITEMTYPE_PRIMAL_HELM,
	ITEMTYPE_PELT,
	ITEMTYPE_CLOAK,
	ITEMTYPE_RUNE,
	ITEMTYPE_CIRCLET,
	ITEMTYPE_HEALING_POTION,
	ITEMTYPE_MANA_POTION,
	ITEMTYPE_REJUV_POTION,
	ITEMTYPE_STAMINA_POTION,
	ITEMTYPE_ANTIDOTE_POTION,
	ITEMTYPE_THAWING_POTION,
	ITEMTYPE_SMALL_CHARM,
	ITEMTYPE_MEDIUM_CHARM,
	ITEMTYPE_LARGE_CHARM,
	ITEMTYPE_AMAZON_BOW,
	ITEMTYPE_AMAZON_SPEAR,
	ITEMTYPE_AMAZON_JAVELIN,
	ITEMTYPE_HAND_TO_HAND_2,
	ITEMTYPE_MAGIC_BOW_QUIV,
	ITEMTYPE_UNK,
	ITEMTYPE_CHIPPED_GEM,
	ITEMTYPE_FLAWED_GEM,
	ITEMTYPE_STANDARD_GEM,
	ITEMTYPE_FLAWLESS_GEM,
	ITEMTYPE_PERFECT_GEM,
	ITEMTYPE_AMETHYST,
	ITEMTYPE_DIAMOND,
	ITEMTYPE_EMERALD,
	ITEMTYPE_RUBY,
	ITEMTYPE_SAPPHIRE,
	ITEMTYPE_TOPAZ,
	ITEMTYPE_SKULL,
	// Own ItemTypes
	ITEMTYPE_TOME,
	ITEMTYPE_CLUESCROLL
};

enum D2C_ItemModes
{
	IMODE_STORED, 		//Item is in Storage (inventory, cube, Stash?)
	IMODE_EQUIP, 		//Item is Equippped
	IMODE_INBELT, 		//Item is in Belt Rows
	IMODE_ONGROUND, 	//Item is on Ground
	IMODE_ONCURSOR, 	//Item is on Cursor
	IMODE_DROPPING, 	//Item is Being Dropped
	IMODE_SOCKETED		//Item is Socketed in another Item
};

enum D2C_ItemFlags
{
	IFLAG_NEWITEM = 0x00000001,
	IFLAG_TARGET = 0x00000002,
	IFLAG_TARGETING = 0x00000004,
	IFLAG_DELETED = 0x00000008,
	IFLAG_IDENTIFIED = 0x00000010,
	IFLAG_QUANTITY = 0x00000020,
	IFLAG_SWITCHIN = 0x00000040,
	IFLAG_SWITCHOUT = 0x00000080,
	IFLAG_BROKEN = 0x00000100,
	IFLAG_REPAIRED = 0x00000200,
	IFLAG_UNK1 = 0x00000400,
	IFLAG_SOCKETED = 0x00000800,
	IFLAG_NOSELL = 0x00001000,
	IFLAG_INSTORE = 0x00002000,
	IFLAG_NOEQUIP = 0x00004000,
	IFLAG_NAMED = 0x00008000,
	IFLAG_ISEAR = 0x00010000,
	IFLAG_STARTITEM = 0x00020000,
	IFLAG_UNK2 = 0x00040000,
	IFLAG_INIT = 0x00080000,
	IFLAG_UNK3 = 0x00100000,
	IFLAG_COMPACTSAVE = 0x00200000,
	IFLAG_ETHEREAL = 0x00400000,
	IFLAG_JUSTSAVED = 0x00800000,
	IFLAG_PERSONALIZED = 0x01000000,
	IFLAG_LOWQUALITY = 0x02000000,
	IFLAG_RUNEWORD = 0x04000000,
	IFLAG_ITEM = 0x08000000
};

enum D2C_UniqueItemFlags
{
	UNIQUEITEM_ENABLED = 0x00000001,
	UNIQUEITEM_NOLIMIT = 0x00000002,
	UNIQUEITEM_CARRY1 = 0x00000004,
	UNIQUEITEM_LADDER = 0x00000008,
};

enum D2C_ItemDropFlags
{
	ITEMDROPFLAG_ALWAYSETH = 0x00000004,
};

enum D2C_ItemCmdFlags
{
	ITEMCMDFLAG_DELETE = 0x00000020,
};

struct D2ItemSave
{
	int32_t nClassId;							//0x00
	uint16_t nX;								//0x04
	uint16_t nY;								//0x06
	uint8_t nAnimMode;							//0x08
	uint8_t pad0x09[3];							//0x09
	uint32_t dwFlags;							//0x0C
	uint8_t nStorePage;							//0x10
	uint8_t nBodyloc;							//0x11
	uint8_t pad0x12[2];							//0x12
	int32_t nItemFileIndex;						//0x14
};
#pragma pack()

// Helper function
// Checks that the given unit is an item with data
inline struct D2ItemData* ITEMS_GetItemData(struct D2Unit* pItem) { return (pItem && pItem->dwUnitType == UNIT_ITEM && pItem->pItemData) ? pItem->pItemData : nullptr; }

//D2Common.0x6FD98380 (#10687)
D2COMMON_DLL_DECL void __cdecl ITEMS_AllocItemData(void* pMemPool, struct D2Unit* pItem);
//D2Common.0x6FD983F0 (#10688)
D2COMMON_DLL_DECL void __cdecl ITEMS_FreeItemData(void* pMemPool, struct D2Unit* pItem);
//D2Common.0x6FD98430 (#10689)
D2COMMON_DLL_DECL uint8_t __cdecl ITEMS_GetBodyLocation(struct D2Unit* pItem);
//D2Common.0x6FD98450 (#10690)
D2COMMON_DLL_DECL void __cdecl ITEMS_SetBodyLocation(struct D2Unit* pItem, uint8_t nBodyLoc);
//D2Common.0x6FD98470 (#10691)
D2COMMON_DLL_DECL struct D2Seed* __cdecl ITEMS_GetItemSeed(struct D2Unit* pItem);
//D2Common.0x6FD98490 (#10692)
D2COMMON_DLL_DECL void __cdecl ITEMS_InitItemSeed(struct D2Unit* pItem);
//D2Common.0x6FD984B0 (#10693)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetItemStartSeed(struct D2Unit* pItem);
//D2Common.0x6FD984D0 (#10694)
D2COMMON_DLL_DECL void __cdecl ITEMS_SetItemStartSeed(struct D2Unit* pItem, int nSeed);
//D2Common.0x6FD98550 (#10695)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetItemQuality(struct D2Unit* pItem);
//D2Common.0x6FD98580 (#10696)
D2COMMON_DLL_DECL void __cdecl ITEMS_SetItemQuality(struct D2Unit* pItem, int nQuality);
//D2Common.0x6FD985A0 (#10699)
D2COMMON_DLL_DECL uint16_t __cdecl ITEMS_GetPrefixId(struct D2Unit* pItem, int nPrefixNo);
//D2Common.0x6FD985D0 (#10700)
D2COMMON_DLL_DECL void __cdecl ITEMS_AssignPrefix(struct D2Unit* pItem, uint16_t nPrefix, int nPrefixNo);
//D2Common.0x6FD98600 (#10697)
D2COMMON_DLL_DECL uint16_t __cdecl ITEMS_GetAutoAffix(struct D2Unit* pItem);
//D2Common.0x6FD98630 (#10698)
D2COMMON_DLL_DECL void __cdecl ITEMS_SetAutoAffix(struct D2Unit* pItem, uint16_t nAffix);
//D2Common.0x6FD98650 (#10701)
D2COMMON_DLL_DECL uint16_t __cdecl ITEMS_GetSuffixId(struct D2Unit* pItem, int nSuffixNo);
//D2Common.0x6FD98680 (#10702)
D2COMMON_DLL_DECL void __cdecl ITEMS_AssignSuffix(struct D2Unit* pItem, uint16_t nSuffix, int nSuffixNo);
//D2Common.0x6FD986B0 (#10703)
D2COMMON_DLL_DECL uint16_t __cdecl ITEMS_GetRarePrefixId(struct D2Unit* pItem);
//D2Common.0x6FD986E0 (#10704)
D2COMMON_DLL_DECL void __cdecl ITEMS_AssignRarePrefix(struct D2Unit* pItem, uint16_t nPrefix);
//D2Common.0x6FD98700 (#10705)
D2COMMON_DLL_DECL uint16_t __cdecl ITEMS_GetRareSuffixId(struct D2Unit* pItem);
//D2Common.0x6FD98730 (#10706)
D2COMMON_DLL_DECL void __cdecl ITEMS_AssignRareSuffix(struct D2Unit* pItem, uint16_t nSuffix);
//D2Common.0x6FD98750 (#10707)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_CheckItemFlag(struct D2Unit* pItem, uint32_t dwFlag, int nLine, const char* szFile);
//D2Common.0x6FD98780 (#10708)
D2COMMON_DLL_DECL void __cdecl ITEMS_SetItemFlag(struct D2Unit* pItem, uint32_t dwFlag, BOOL bSet);
//D2Common.0x6FD987C0 (#10709)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_GetItemFlags(struct D2Unit* pItem);
//D2Common.0x6FD987E0 (#10710)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_CheckItemCMDFlag(struct D2Unit* pItem, int nFlag);
//D2Common.0x6FD98810 (#10711)
D2COMMON_DLL_DECL void __cdecl ITEMS_SetItemCMDFlag(struct D2Unit* pItem, int nFlag, BOOL bSet);
//D2Common.0x6FD98850 (#10712)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_GetItemCMDFlags(struct D2Unit* pItem);
//D2Common.0x6FD98870 (#10717)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetItemLevel(struct D2Unit* pItem);
//D2Common.0x6FD988B0 (#10718)
D2COMMON_DLL_DECL void __cdecl ITEMS_SetItemLevel(struct D2Unit* pItem, int nItemLevel);
//D2Common.0x6FD988E0 (#10719)
D2COMMON_DLL_DECL uint8_t __cdecl ITEMS_GetInvPage(struct D2Unit* pItem);
//D2Common.0x6FD98900 (#10720)
D2COMMON_DLL_DECL void __cdecl ITEMS_SetInvPage(struct D2Unit* pItem, uint8_t nPage);
//D2Common.0x6FD98920 (#10721)
D2COMMON_DLL_DECL uint8_t __cdecl ITEMS_GetCellOverlap(struct D2Unit* pItem);
//D2Common.0x6FD98940 (#10722)
D2COMMON_DLL_DECL void __cdecl ITEMS_SetCellOverlap(struct D2Unit* pItem, int nCellOverlap);
//D2Common.0x6FD98960 (#10853)
D2COMMON_DLL_DECL uint8_t __cdecl ITEMS_GetItemCell(struct D2Unit* pItem);
//D2Common.0x6FD98980 (#10854)
D2COMMON_DLL_DECL void __cdecl ITEMS_SetItemCell(struct D2Unit* pItem, int nItemCell);
//D2Common.0x6FD989A0 (#10723)
D2COMMON_DLL_DECL char* __cdecl ITEMS_GetEarName(struct D2Unit* pItem);
//D2Common.0x6FD989C0 (#10724)
D2COMMON_DLL_DECL void __cdecl ITEMS_SetEarName(struct D2Unit* pItem, char* szName);
//D2Common.0x6FD989F0 (#10725)
D2COMMON_DLL_DECL uint8_t __cdecl ITEMS_GetEarLevel(struct D2Unit* pItem);
//D2Common.0x6FD98A10 (#10726)
D2COMMON_DLL_DECL void __cdecl ITEMS_SetEarLevel(struct D2Unit* pItem, uint8_t nLevel);
//D2Common.0x6FD98A30 (#10727)
D2COMMON_DLL_DECL uint8_t __cdecl ITEMS_GetVarGfxIndex(struct D2Unit* pItem);
//D2Common.0x6FD98A50 (#10728)
D2COMMON_DLL_DECL void __cdecl ITEMS_SetVarGfxIndex(struct D2Unit* pItem, uint8_t nIndex);
//D2Common.0x6FD98A70 (#10777)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_IsRepairable(struct D2Unit* pItem);
//D2Common.0x6FD98C60 (#10780)
D2COMMON_DLL_DECL int32_t __cdecl ITEMS_GetAmmoTypeFromItemType(int nItemType);
//D2Common.0x6FD98CA0 (#10781)
D2COMMON_DLL_DECL int32_t __cdecl ITEMS_GetAmmoType(struct D2Unit* pItem);
//D2Common.0x6FD98D20 (#10782)
D2COMMON_DLL_DECL int32_t __cdecl ITEMS_GetQuiverTypeFromItemType(int nItemType);
//D2Common.0x6FD98D60 (#10783)
D2COMMON_DLL_DECL int32_t __cdecl ITEMS_GetQuiverType(struct D2Unit* pItem);
//D2Common.0x6FD98DE0 (#10784)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_GetAutoStackFromItemType(int nItemType);
//D2Common.0x6FD98E20 (#10785)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_GetAutoStack(struct D2Unit* pItem);
//D2Common.0x6FD98EA0 (#10786)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_GetReload(struct D2Unit* pItem);
//D2Common.0x6FD98F20 (#10787)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_GetReEquip(struct D2Unit* pItem);
//D2Common.0x6FD98FA0 (#10788)
D2COMMON_DLL_DECL uint8_t __cdecl ITEMS_GetStorePage(struct D2Unit* pItem);
//D2Common.0x6FD99020 (#10789)
D2COMMON_DLL_DECL uint8_t __cdecl ITEMS_GetVarInvGfxCount(struct D2Unit* pItem);
//D2Common.0x6FD990A0 (#10790)
D2COMMON_DLL_DECL char* __cdecl ITEMS_GetVarInvGfxString(struct D2Unit* pItem, int nId);
//D2Common.0x6FD99140 (#10792)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_CanBeRare(struct D2Unit* pItem);
//D2Common.0x6FD991C0 (#10791)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_CanBeMagic(struct D2Unit* pItem);
//D2Common.0x6FD99240 (#10793)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_CanBeNormal(struct D2Unit* pItem);
//D2Common.0x6FD992C0 (#10744)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_GetWeaponClassCode(struct D2Unit* pItem);
//D2Common.0x6FD992F0 (#10745)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_Get2HandWeaponClassCode(struct D2Unit* pItem);
//D2Common.0x6FD99370 (#10746)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_GetBaseCode(struct D2Unit* pItem);
//D2Common.0x6FD993F0 (#10747)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_GetAltGfx(struct D2Unit* pItem);
//D2Common.0x6FD99480 (#10748)
D2COMMON_DLL_DECL uint8_t __cdecl ITEMS_GetComponent(struct D2Unit* pItem);
//D2Common.0x6FD99500 (#10749)
D2COMMON_DLL_DECL void __cdecl ITEMS_GetDimensions(struct D2Unit* pItem, uint8_t* pWidth, uint8_t* pHeight, const char* szFile, int nLine);
//D2Common.0x6FD99540 (#10750)
D2COMMON_DLL_DECL void __cdecl ITEMS_GetAllowedBodyLocations(struct D2Unit* pItem, uint8_t* pBodyLoc1, uint8_t* pBodyLoc2);
//D2Common.0x6FD995D0 (#10751)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_GetItemType(struct D2Unit* pItem);
//D2Common.0x6FD99640 (#10752)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_GetItemTypeFromItemId(uint32_t dwItemId);
//D2Common.0x6FD99680 (#10753)
D2COMMON_DLL_DECL uint8_t __cdecl ITEMS_GetItemQlvl(const struct D2Unit* pItem);
//D2Common.0x6FD99700 (#10754)
D2COMMON_DLL_DECL int __cdecl ITEMS_CheckIfFlagIsSet(int nFlags, int nFlag);
//D2Common.0x6FD99710 (#10755)
D2COMMON_DLL_DECL void __cdecl ITEMS_SetOrRemoveFlag(int* pFlags, int nFlag, BOOL bSet);
//D2Common.0x6FD99740 (#10756)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_CheckRequirements(struct D2Unit* pItem, struct D2Unit* pUnit, BOOL bEquipping, BOOL* bStrength, BOOL* bDexterity, BOOL* bLevel);
//D2Common.0x6FD99BC0 (#10741)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_GetQuestFromItemId(int nItemId);
//D2Common.0x6FD99C60 (#10742)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_GetQuest(struct D2Unit* pItem);
//D2Common.0x6FD99D40 (#10743)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_GetNormalCode(struct D2Unit* pItem);
//D2Common.0x6FD99DB0
int __cdecl ITEMS_GetRequiredLevel(struct D2Unit* pItem, struct D2Unit* pPlayer);
//D2Common.0x6FD9A3F0 (#10757)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetLevelRequirement(struct D2Unit* pItem, struct D2Unit* pUnit);
//D2Common.0x6FD9A400 (#10758)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_CheckBodyLocation(struct D2Unit* pItem, uint8_t nBodyLoc);
//D2Common.0x6FD9A4F0 (#10762)
D2COMMON_DLL_DECL int __cdecl ITEMS_CheckItemTypeIfThrowable(int nItemType);
//D2Common.0x6FD9A530 (#10759)
D2COMMON_DLL_DECL int __cdecl ITEMS_CheckIfThrowable(struct D2Unit* pItem);
//D2Common.0x6FD9A5B0 (#10760)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetMissileType(struct D2Unit* pItem);
//D2Common.0x6FD9A5E0 (#10761)
D2COMMON_DLL_DECL uint8_t __cdecl ITEMS_GetMeleeRange(struct D2Unit* pItem);
//D2Common.0x6FD9A610 (#10763)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_CheckWeaponClassByItemId(int nItemId, int nWeapClass);
//D2Common.0x6FD9A660 (#10764)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_CheckWeaponClass(struct D2Unit* pItem, int nWeapClass);
//D2Common.0x6FD9A6C0 (#10766)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_CheckWeaponIfTwoHandedByItemId(int nItemId);
//D2Common.0x6FD9A700 (#10765)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_CheckWeaponIfTwoHanded(struct D2Unit* pItem);
//D2Common.0x6FD9A750 (#10767)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_CheckIfStackable(struct D2Unit* pItem);
//D2Common.0x6FD9A7A0 (#10768)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_CheckIfBeltable(struct D2Unit* pItem);
//D2Common.0x6FD9A820 (#10769)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_ComparePotionTypes(struct D2Unit* pItem1, struct D2Unit* pItem2);
//D2Common.0x6FD9A960 (#10770)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_CheckIfAutoBeltable(struct D2Inventory* pInventory, struct D2Unit* pItem);
//D2Common.0x6FD9AA00 (#10771)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_CheckIfUseable(struct D2Unit* pItem);
//D2Common.0x6FD9AA70 (#10772)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetUniqueColumnFromItemsTxt(struct D2Unit* pItem);
//D2Common.0x6FD9AB00 (#10773)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_IsQuestItem(struct D2Unit* pItem);
//D2Common.0x6FD9AB90
int __cdecl ITEMS_CalculateAdditionalCostsForChargedSkills(struct D2Unit* pUnit, int nBaseCost);
//D2Common.0x6FD9ACE0
void __cdecl ITEMS_CalculateAdditionalCostsForBonusStats(struct D2Unit* pItem, int* pSellCost, int* pBuyCost, int* pRepCost, unsigned int nDivisor);
//D2Common.0x6FD9B1C0
int __cdecl ITEMS_CalculateTransactionCost(struct D2Unit* pPlayer, struct D2Unit* pItem, enum D2C_Difficulties nDifficulty, struct D2BitBuffer* pQuestFlags, int nVendorId, enum D2C_TransactionTypes nTransactionType);
//D2Common.0x6FD9CB50
void __cdecl ITEMS_CalculateAdditionalCostsForItemSkill(struct D2Unit* pItem, int* pSellCost, int* pBuyCost, int* pRepCost, unsigned int nDivisor);
//D2Common.0x6FD9CDC0
int __cdecl ITEMS_CheckUnitFlagEx(struct D2Unit* pUnit, int nFlag);
//D2Common.0x6FD9CDE0 (#10775)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetTransactionCost(struct D2Unit* pPlayer, struct D2Unit* pItem, enum D2C_Difficulties nDifficulty, struct D2BitBuffer* pQuestFlags, int nVendorId, enum D2C_TransactionTypes nTransactionType);
//D2Common.0x6FD9CE10 (#10794)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetMaxStack(int nItemId);
//D2Common.0x6FD9CE50 (#10795)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetTotalMaxStack(struct D2Unit* pItem);
//D2Common.0x6FD9CEF0 (#10798)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetSpawnStackFromItemId(int nItemId);
//D2Common.0x6FD9CF30 (#10799)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetSpawnStack(struct D2Unit* pItem);
//D2Common.0x6FD9CFB0 (#10796)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetMinStackFromItemId(int nItemId);
//D2Common.0x6FD9CFF0 (#10797)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetMinStack(struct D2Unit* pItem);
//D2Common.0x6FD9D070 (#10800) - Unused
int __cdecl ITEMS_CheckBitField1Flag8(struct D2Unit* pItem);
//D2Common.0x6FD9D0F0 (#10804)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetSpellIcon(struct D2Unit* pItem);
//D2Common.0x6FD9D1E0 (#10805)
D2COMMON_DLL_DECL uint8_t __cdecl ITEMS_GetDurWarnCount(struct D2Unit* pItem);
//D2Common.0x6FD9D260 (#10806)
D2COMMON_DLL_DECL uint8_t __cdecl ITEMS_GetQtyWarnCount(struct D2Unit* pItem);
//D2Common.0x6FD9D2E0 (#10807)
D2COMMON_DLL_DECL short __cdecl ITEMS_GetStrengthBonus(struct D2Unit* pItem);
//D2Common.0x6FD9D310 (#10808)
D2COMMON_DLL_DECL short __cdecl ITEMS_GetDexBonus(struct D2Unit* pItem);
//D2Common.0x6FD9D340 (#10809)
D2COMMON_DLL_DECL int __cdecl ITEMS_CheckIfSocketableByItemId(int nItemId);
//D2Common.0x6FD9D360 (#10810)
D2COMMON_DLL_DECL int __cdecl ITEMS_CheckIfSocketable(struct D2Unit* pItem);
//D2Common.0x6FD9D390 (#10811)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_HasDurability(struct D2Unit* pItem);
//D2Common.0x6FD9D3F0 (#10813)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetStaffMods(struct D2Unit* pItem);
//D2Common.0x6FD9D470 (#10814)
D2COMMON_DLL_DECL uint8_t __cdecl ITEMS_GetAllowedGemSocketsFromItemId(int nItemId);
//D2Common.0x6FD9D490 (#10815)
D2COMMON_DLL_DECL uint8_t __cdecl ITEMS_GetMaxSockets(struct D2Unit* pItem);
//D2Common.0x6FD9D580 (#10816)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetSockets(struct D2Unit* pItem);
//D2Common.0x6FD9D5E0 (#10817)
D2COMMON_DLL_DECL void __cdecl ITEMS_AddSockets(struct D2Unit* pItem, int nSockets);
//D2Common.0x6FD9D7C0 (#10818)
D2COMMON_DLL_DECL void __cdecl ITEMS_SetSockets(struct D2Unit* pItem, int nSockets);
//D2Common.0x6FD9D900 (#10819)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetGemApplyTypeFromItemId(int nItemId);
//D2Common.0x6FD9D940 (#10820)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetGemApplyType(struct D2Unit* pItem);
//D2Common.0x6FD9D9D0 (#10821)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_IsSocketFiller(struct D2Unit* pItem);
//D2Common.0x6FD9D9E0 (#10822) Retrieves the runes.txt record based on the socketed items
D2COMMON_DLL_DECL const struct D2RunesTxt* __cdecl ITEMS_GetRunesTxtRecordFromItem(const struct D2Unit* pItem);
//D2Common.0x6FD9DBA0 (#10729)
D2COMMON_DLL_DECL //Checks if the given item has a type equivalent to a given item type
BOOL __cdecl ITEMS_CheckItemTypeIdByItemId(int nItemId, int nItemType);
//D2Common.0x6FD9DC80 (#10730)
D2COMMON_DLL_DECL //Checks if the given item types are equivalent
BOOL __cdecl ITEMS_CheckType(int nItemType1, int nItemType2);
//D2Common.0x6FD9DCE0 (#10731)
D2COMMON_DLL_DECL //Checks if the given item has a type equivalent to a given item type
BOOL __cdecl ITEMS_CheckItemTypeId(const struct D2Unit* pItem, int nItemType);
//D2Common.0x6FD9DDD0 (#10803)
D2COMMON_DLL_DECL int __cdecl ITEMS_CheckBitField1Flag1(int nItemId);
//D2Common.0x6FD9DE10 (#10802)
D2COMMON_DLL_DECL int __cdecl ITEMS_IsMetalItem(int nItemId);
//D2Common.0x6FD9DE50 (#10801) - Unused
int __cdecl ITEMS_CheckBitField1Flag4(int nItemId);
//D2Common.0x6FD9DE90 (#10774)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_IsNotQuestItemByItemId(int nItemId);
//D2Common.0x6FD9DEE0 (#10732)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetFileIndex(struct D2Unit* pItem);
//D2Common.0x6FD9DF60 (#10733)
D2COMMON_DLL_DECL void __cdecl ITEMS_SetFileIndex(struct D2Unit* pItem, uint32_t dwFileIndex);
//D2Common.0x6FD9DFE0 (#11244)
D2COMMON_DLL_DECL void __cdecl ITEMS_GetRealmData(struct D2Unit* pItem, int* pRealmData0, int* pRealmData1);
//D2Common.0x6FD9E070 (#11245)
D2COMMON_DLL_DECL void __cdecl ITEMS_SetRealmData(struct D2Unit* pItem, int a2, int a3);
//D2Common.0x6FD9E0A0 (#10734)
D2COMMON_DLL_DECL void __cdecl ITEMS_SetOwnerId(struct D2Unit* pItem, D2UnitGUID nOwnerGUID);
//D2Common.0x6FD9E120 (#10735)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetOwnerId(struct D2Unit* pItem);
//D2Common.0x6FD9E1A0 (#10736)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_IsBodyItem(struct D2Unit* pItem);
//D2Common.0x6FD9E2A0 (#10738)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_IsClassValidByItemId(int nItemId);
//D2Common.0x6FD9E310 (#10737)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_IsClassValid(struct D2Unit* pItem);
//D2Common.0x6FD9E390 (#10739)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetClassOfClassSpecificItem(struct D2Unit* pItem);
//D2Common.0x6FD9E410 (#10823)
D2COMMON_DLL_DECL uint16_t __cdecl ITEMS_GetWeaponClassId(struct D2Unit* pItem);
//D2Common.0x6FD9E480 (#10824)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_GetTransmogrifyFromItemId(int nItemId);
//D2Common.0x6FD9E4C0 (#10825)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_GetTransmogrify(struct D2Unit* pItem);
//D2Common.0x6FD9E550 (#10826)
D2COMMON_DLL_DECL int __cdecl ITEMS_IsMagSetRarUniCrfOrTmp(struct D2Unit* pItem);
//D2Common.0x6FD9E580 (#10740)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_IsNotQuestItem(struct D2Unit* pItem);
//D2Common.0x6FD9E5F0 (#10827)
D2COMMON_DLL_DECL uint8_t __cdecl ITEMS_GetHitClassFromItem(struct D2Unit* pItem);
//D2Common.0x6FD9E670 (#10828)
D2COMMON_DLL_DECL int __cdecl ITEMS_Is1Or2Handed(struct D2Unit* pPlayer, struct D2Unit* pItem);
//D2Common.0x6FD9E710 (#10829)
D2COMMON_DLL_DECL uint8_t* __cdecl ITEMS_GetColor(struct D2Unit* pPlayer, struct D2Unit* pItem, uint8_t* pColor, int nTransType);
//D2Common.0x6FD9EE70
struct D2SetItemsTxt* __cdecl ITEMS_GetSetItemsTxtRecord(int nRecordId);
//D2Common.0x6FD9EEA0 (#10830)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_IsImbueable(struct D2Unit* pItem);
//D2Common.0x6FD9F080 (#10832)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_IsPersonalizable(struct D2Unit* pItem);
//D2Common.0x6FD9F260 (#10831)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_IsSocketable(struct D2Unit* pItem);
//D2Common.0x6FD9F490 (#10877)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetAllRepairCosts(struct D2Game* pGame, struct D2Unit* pUnit, int nNpcId, enum D2C_Difficulties nDifficulty, struct D2BitBuffer* pQuestFlags, void(__cdecl* pfCallback)(struct D2Game*, struct D2Unit*, struct D2Unit*));
//D2Common.0x6FD9F720 (#10833)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_AreStackablesEqual(struct D2Unit* pItem1, struct D2Unit* pItem2);
//D2Common.0x6FD9FA70 (#10834)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_CanItemBeUsedForThrowSkill(struct D2Unit* pItem);
//D2Common.0x6FD9FB40 (#11079)
D2COMMON_DLL_DECL int __cdecl D2COMMON_11079_Return0(int a1, int a2);
//D2Common.0x6FD9FB50 (#10836)
D2COMMON_DLL_DECL uint32_t __cdecl ITEMS_GetSetItemsMask(struct D2Unit* pPlayer, struct D2Unit* pSetItem, BOOL bDontIgnoreInputItem);
//D2Common.0x6FD9FD80 (#10838)
D2COMMON_DLL_DECL struct D2SetItemsTxt* __cdecl ITEMS_GetSetItemsTxtRecordFromItem(struct D2Unit* pItem);
//D2Common.0x6FD9FE20 (#10839)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_CanBeEquipped(struct D2Unit* pItem);
//D2Common.0x6FD9FE70 (#10840)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_IsCharmUsable(struct D2Unit* pItem, struct D2Unit* pPlayer);
//D2Common.0x6FD9FF00 (#10776)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetNoOfUnidItems(struct D2Unit* pUnit);
//D2Common.0x6FD9FF90 (#10841)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetBonusLifeBasedOnClass(struct D2Unit* pPlayer, int nValue);
//D2Common.0x6FD9FFE0 (#10842)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetBonusManaBasedOnClass(struct D2Unit* pPlayer, int nValue);
//D2Common.0x6FDA0030 (#10875)
D2COMMON_DLL_DECL uint16_t __cdecl ITEMS_GetItemFormat(struct D2Unit* pItem);
//D2Common.0x6FDA00B0 (#10876)
D2COMMON_DLL_DECL void __cdecl ITEMS_SetItemFormat(struct D2Unit* pItem, uint16_t nItemFormat);
//D2Common.0x6FDA0130 (#10878)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetWeaponAttackSpeed(struct D2Unit* pUnit, struct D2Unit* pWeapon);
//D2Common.0x6FDA02B0 (#10879)
D2COMMON_DLL_DECL int __cdecl ITEMS_HasUsedCharges(struct D2Unit* pItem, BOOL* pHasChargedSkills);
//D2Common.0x6FDA0340 (#10880)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_IsEthereal(struct D2Unit* pItem);
//D2Common.0x6FDA0370 (#10883)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_GetCompactItemDataFromBitstream(uint8_t* pBitstream, size_t nSize, BOOL bCheckForHeader, struct D2ItemSave* pItemSave);
//D2Common.0x6FDA0490 (#10882)
D2COMMON_DLL_DECL size_t __cdecl ITEMS_DecodeItemFromBitstream(struct D2Unit* pItem, uint8_t* pBitstream, size_t nSize, BOOL bCheckForHeader, int* pSocketedItemCount, uint32_t dwVersion, BOOL* pFail);
//D2Common.0x6FDA0620
int __cdecl ITEMS_DecodeItemBitstreamCompact(struct D2Unit* pItem, struct D2BitBuffer* pBuffer, BOOL bCheckForHeader, uint32_t dwVersion);
//D2Common.0x6FDA0A20
int __cdecl ITEMS_DecodeItemBitstreamComplete(struct D2Unit* pItem, struct D2BitBuffer* pBuffer, BOOL bCheckForHeader, BOOL bGamble, int* pSocketedItems, uint32_t dwVersion);
//D2Common.0x6FDA2690
void __cdecl ITEMS_SetDefenseOrDamage(struct D2Unit* pItem, int nStat);
//D2Common.0x6FDA29D0
void __cdecl ITEMS_ReadStatFromItemBitstream(struct D2BitBuffer* pBuffer, struct D2StatList* pStatList, struct D2ItemStatCostTxt* pItemStatCostTxtRecord, int nStatId, uint32_t dwVersion, int n109);
//D2Common.0x6FDA2BA0 (#10881)
D2COMMON_DLL_DECL size_t __cdecl ITEMS_SerializeItemToBitstream(struct D2Unit* pItem, uint8_t* pBitstream, size_t nSize, BOOL bServer, BOOL bSaveItemInv, BOOL bGamble);
//Inlined in D2Common.0x6FDA2C00
void __cdecl ITEMS_SerializeItemCompact(struct D2Unit* pItem, struct D2BitBuffer* pBuffer, struct D2ItemsTxt* pItemsTxtRecord, BOOL bServer);
//D2Common.0x6FDA2C00
size_t __cdecl ITEMS_SerializeItem(struct D2Unit* pItem, struct D2BitBuffer* pBuffer, BOOL bServer, BOOL bSaveItemInv, BOOL bGamble);
//D2Common.0x6FDA2FD0
void __cdecl ITEMS_WriteBitsToBitstream(struct D2BitBuffer* pBuffer, int nData, int nBits);
//D2Common.0x6FDA3010
void __cdecl ITEMS_SerializeItemComplete(struct D2Unit* pItem, struct D2BitBuffer* pBuffer, BOOL bServer, BOOL bGamble);
//D2Common.0x6FDA42B0
struct D2ItemStatCostTxt* __cdecl ITEMS_GetItemStatCostTxtRecord(int nStatId);
//D2Common.0x6FDA42E0 (#10837)
D2COMMON_DLL_DECL int __cdecl ITEMS_GetNoOfSetItemsFromItem(struct D2Unit* pItem);
//D2Common.0x6FDA4380
BOOL __cdecl sub_6FDA4380(struct D2Unit* pItem, unsigned int nSetItemMask);
//D2Common.0x6FDA4490
BOOL __cdecl sub_6FDA4490(struct D2Unit* pUnit, struct D2Unit* pItem, int a3);
//D2Common.0x6FDA4640 (#10866)
D2COMMON_DLL_DECL BOOL __cdecl ITEMS_UpdateSets(struct D2Unit* pUnit, struct D2Unit* pItem, int a3, int a4);
