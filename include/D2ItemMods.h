#pragma once

#include "D2CommonDefinitions.h"
#include <Units/Missile.h>
#include <DataTbls/ItemsTbls.h>

struct D2StatList;

#pragma pack(1)


typedef BOOL(__cdecl* PROPERTYASSIGN)(int32_t, struct D2Unit*, struct D2Unit*, const struct D2Property*, int32_t, int32_t, int32_t, int32_t, struct D2Unit*);

typedef int32_t(__cdecl* PROPERTYASSIGNFN)(int32_t, struct D2Unit*, struct D2Unit*, const struct D2Property*, int32_t, int16_t, int32_t, int32_t, int32_t, int32_t, struct D2Unit*);

struct D2PropertyAssign
{
	PROPERTYASSIGN pfAssign;			//0x00
	int32_t nStatId;					//0x04
};


struct D2ItemCalc
{
	struct D2Unit* pUnit;					//0x00
	struct D2Unit* pItem;					//0x04
};

#pragma pack()

//D2Common.0x6FD92640 (#10844)
D2COMMON_DLL_DECL void __cdecl D2Common_10844_ITEMMODS_First(int nDataBits, int* pLayer, int* pValue);
//D2Common.0x6FD92670 (#10846)
D2COMMON_DLL_DECL void __cdecl D2Common_10846(int nDataBits, int* a2, int* a3, int* a4, int* a5);
//D2Common.0x6FD926C0 (#11293)
D2COMMON_DLL_DECL BOOL __cdecl ITEMMODS_GetItemCharges(struct D2Unit* pItem, int nSkillId, int nSkillLevel, int* pValue, struct D2StatList** ppStatList);
//D2Common.0x6FD927D0 (#10847)
D2COMMON_DLL_DECL BOOL __cdecl ITEMMODS_UpdateItemWithSkillCharges(struct D2Unit* pItem, int nSkillId, int nSkillLevel, int a4);
//D2Common.0x6FD928D0 (#10843)
D2COMMON_DLL_DECL int __cdecl ITEMMODS_GetByTimeAdjustment(int nAmount, int nPeriodOfDay, int nBaseTime, int* pItemModPeriodOfDay, int* pItemModMin, int* pItemModMax);
//D2Common.0x6FD929A0 (#10849)
D2COMMON_DLL_DECL int __cdecl D2Common_10849(int a1, int a2);
//D2Common.0x6FD929B0 (#10845)
D2COMMON_DLL_DECL void __cdecl D2Common_10845(int nDataBits, int* a2, int* a3, int* a4);
//D2Common.0x6FD929E0 (#10850)
D2COMMON_DLL_DECL int __cdecl D2Common_10850(int a1, int a2, int a3);
//D2Common.0x6FD92A00 (#10848)
D2COMMON_DLL_DECL void __cdecl D2Common_10848(int nDataBits, int* pClass, int* pTab, int* pLevel);
//D2Common.0x6FD92A60 (#10851)
D2COMMON_DLL_DECL int __cdecl D2Common_10851(int a1, int a2, int a3);
//D2Common.0x6FD92A80
BOOL __cdecl sub_6FD92A80(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD92C40
struct D2StatList* __cdecl ITEMMODS_GetOrCreateStatList(struct D2Unit* pUnit, struct D2Unit* pItem, int nState, int fFilter);
//D2Common.0x6FD92CF0
void __cdecl sub_6FD92CF0(struct D2Unit* pItem, int nStatId);
//D2Common.0x6FD92E80
BOOL __cdecl sub_6FD92E80(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD92EB0
BOOL __cdecl sub_6FD92EB0(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int a7, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD93170
BOOL __cdecl sub_6FD93170(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD931C0
BOOL __cdecl sub_6FD931C0(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD93200
BOOL __cdecl sub_6FD93200(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD93230
BOOL __cdecl sub_6FD93230(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD93410
BOOL __cdecl sub_6FD93410(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, int a4, int nStatId, int nApplyType, int a7, int nState, int fStatList, struct D2Unit* a10);
//D2Common.0x6FD935B0
BOOL __cdecl sub_6FD935B0(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD93790
BOOL __cdecl sub_6FD93790(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD93A20
BOOL __cdecl sub_6FD93A20(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD93CB0
BOOL __cdecl sub_6FD93CB0(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD94060
void __cdecl sub_6FD94060(int nStatId, int* pValue);
//D2Common.0x6FD94160
BOOL __cdecl sub_6FD94160(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD94190
BOOL __cdecl sub_6FD94190(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD943C0
BOOL __cdecl sub_6FD943C0(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD944E0
BOOL __cdecl sub_6FD944E0(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD94AB0
BOOL __cdecl sub_6FD94AB0(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD94E80
BOOL __cdecl sub_6FD94E80(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD94F70
BOOL __cdecl sub_6FD94F70(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD95050
BOOL __cdecl sub_6FD95050(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD95200
BOOL __cdecl sub_6FD95200(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD95210
BOOL __cdecl sub_6FD95210(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nStatId, int nApplyType, int nState, int fStatList, struct D2Unit* a9);
//D2Common.0x6FD95430 (#10855)
D2COMMON_DLL_DECL void __cdecl ITEMMODS_AssignProperty(int nType, struct D2Unit* a2, struct D2Unit* pItem, const void* pMods, int nPropSet, int nApplyType);
//D2Common.0x6FD95810
void __cdecl sub_6FD95810(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const void* pMods, int nIndex, int nPropSet, int nApplyType, const struct D2Property* pProperty, int nState, int fStatlist, struct D2Unit* a11);
//D2Common.0x6FD958D0 (#10865)
D2COMMON_DLL_DECL void __cdecl ITEMMODS_ApplyEthereality(struct D2Unit* pItem);
//D2Common.0x6FD959F0 (#10867)
D2COMMON_DLL_DECL BOOL __cdecl ITEMMODS_UpdateRuneword(struct D2Unit* pUnit, struct D2Unit* pItem, int nUnused);
//D2Common.0x6FD95A70
void __cdecl ITEMMODS_UpdateFullSetBoni(struct D2Unit* pUnit, struct D2Unit* pItem, int nState);
//D2Common.0x6FD95BE0 (#10859)
D2COMMON_DLL_DECL BOOL __cdecl ITEMMODS_CanItemHaveMagicAffix(struct D2Unit* pItem, const struct D2MagicAffixTxt* pMagicAffixTxtRecord);
//D2Common.0x6FD95CC0 (#10860)
D2COMMON_DLL_DECL BOOL __cdecl ITEMMODS_CanItemHaveRareAffix(struct D2Unit* pItem, struct D2RareAffixTxt* pRareAffixTxtRecord);
//D2Common.0x6FD95D60 (#10861)
D2COMMON_DLL_DECL BOOL __cdecl ITEMMODS_CanItemBeHighQuality(struct D2Unit* pItem, struct D2QualityItemsTxt* pQualityItemsTxtRecord);
//D2Common.0x6FD95E90 (#10862)
D2COMMON_DLL_DECL void __cdecl ITEMMODS_SetRandomElixirFileIndex(struct D2Unit* pItem);
//D2Common.0x6FD95F90 (#10868)
D2COMMON_DLL_DECL void __cdecl ITEMMODS_AddCraftPropertyList(struct D2Unit* pItem, struct D2Property* pProperty, int nUnused);
//D2Common.0x6FD95FC0
int __cdecl ITEMMODS_PropertyFunc01(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD96110
int __cdecl ITEMMODS_AddPropertyToItemStatList(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* pUnused);
//D2Common.0x6FD96210
int __cdecl ITEMMODS_PropertyFunc02(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD96350
int __cdecl ITEMMODS_PropertyFunc03(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD964A0
int __cdecl ITEMMODS_PropertyFunc04(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD965F0
int __cdecl ITEMMODS_PropertyFunc05(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD96880
int __cdecl ITEMMODS_PropertyFunc06(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD96B00
int __cdecl ITEMMODS_PropertyFunc07(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD96DA0
int __cdecl ITEMMODS_PropertyFunc08(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD96EE0
int __cdecl ITEMMODS_PropertyFunc09(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD97040
int __cdecl ITEMMODS_PropertyFunc24(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD97180
int __cdecl ITEMMODS_PropertyFunc10(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD972E0
int __cdecl ITEMMODS_PropertyFunc11(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD97430
int __cdecl ITEMMODS_PropertyFunc14(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD975F0
int __cdecl ITEMMODS_PropertyFunc19(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD97830
int __cdecl ITEMMODS_PropertyFunc18(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD97920
int __cdecl ITEMMODS_PropertyFunc15(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD979A0
int __cdecl ITEMMODS_PropertyFunc16(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD97A20
int __cdecl ITEMMODS_PropertyFunc17(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD97BA0
int __cdecl ITEMMODS_PropertyFunc20(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD97C20
int __cdecl ITEMMODS_PropertyFunc21(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD97D50
int __cdecl ITEMMODS_PropertyFunc22(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD97E80
int __cdecl ITEMMODS_PropertyFunc12(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD97FB0
int __cdecl ITEMMODS_PropertyFunc13(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD98120
int __cdecl ITEMMODS_PropertyFunc23(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const struct D2Property* pProperty, int nSet, short nStatId, int nLayer, int nValue, int nState, int fStatList, struct D2Unit* a11);
//D2Common.0x6FD98160 (#11292)
D2COMMON_DLL_DECL void __cdecl D2COMMON_11292_ItemAssignProperty(int nType, struct D2Unit* pUnit, struct D2Unit* pItem, const void* pMods, int nIndex, int nPropSet, const struct D2Property* pProperty, int nState, int fStatlist, struct D2Unit* a10);
//D2Common.0x6FD98220
int __cdecl sub_6FD98220(int nMin, int nMax, int nUnused, void* pUserData);
//D2Common.0x6FD982A0
int __cdecl sub_6FD982A0(int nStatId, int a2, int nUnused, void* pUserData);
//D2Common.0x6FD98300 (#11300)
D2COMMON_DLL_DECL int __cdecl ITEMMODS_EvaluateItemFormula(struct D2Unit* pUnit, struct D2Unit* pItem, unsigned int nCalc);
