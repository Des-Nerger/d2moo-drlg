#pragma once

#include <D2BasicTypes.h>
#include <Fog.h>
#include <Calc.h>

#include <stdio.h> // for FILE
#include <Archive.h>

#include "DataTbls/AnimTbls.h"
#include "DataTbls/ArenaTbls.h"
#include "DataTbls/BeltsTbls.h"
#include "DataTbls/DataTbls.h"
#include "DataTbls/FieldTbls.h"
#include "DataTbls/HoradricCube.h"
#include "DataTbls/InvTbls.h"
#include "DataTbls/ItemsTbls.h"
#include "DataTbls/LevelsTbls.h"
#include "DataTbls/MissilesTbls.h"
#include "DataTbls/MonsterTbls.h"
#include "DataTbls/ObjectsTbls.h"
#include "DataTbls/OverlayTbls.h"
#include "DataTbls/SkillsTbls.h"
#include "DataTbls/SequenceTbls.h"
#include "DataTbls/TokenTbls.h"
#include "DataTbls/TransformTbls.h"
#include <D2Seed.h>

#pragma pack(1)

struct D2BodyLocsTxt
{
	uint32_t dwCode;						//0x00
};


struct D2CharStatsTxt
{
	struct Unicode wszClassName[16];				//0x00
	char szClassName[16];					//0x20
	uint8_t nStr;							//0x30
	uint8_t nDex;							//0x31
	uint8_t nInt;							//0x32
	uint8_t nVit;							//0x33
	uint8_t nStamina;						//0x34
	uint8_t nLifeAdd;						//0x35
	uint8_t nPercentStr;					//0x36
	uint8_t nPercentInt;					//0x37
	uint8_t nPercentDex;					//0x38
	uint8_t nPercentVit;					//0x39
	uint8_t nManaRegen;						//0x3A
	uint8_t pad0x3B;						//0x3B
	uint32_t dwToHitFactor;					//0x3C
	uint8_t nWalkSpeed;						//0x40
	uint8_t nRunSpeed;						//0x41
	uint8_t nRunDrain;						//0x42
	uint8_t nLifePerLevel;					//0x43
	uint8_t nStaminaPerLevel;				//0x44
	uint8_t nManaPerLevel;					//0x45
	uint8_t nLifePerVitality;				//0x46
	uint8_t nStaminaPerVitality;			//0x47
	uint8_t nManaPerMagic;					//0x48
	uint8_t nBlockFactor;					//0x49
	uint16_t pad0x4A;						//0x4A
	uint32_t dwBaseWClass;					//0x4C
	uint8_t nStatsPerLevel;					//0x50
	uint8_t pad0x51;						//0x51
	uint16_t wStrAllSkills;					//0x52
	uint16_t wStrSkillTab[3];				//0x54
	uint16_t wStrClassOnly;					//0x5A
	struct D2CharItem pItems[10];				//0x5C
	uint16_t wStartSkill;					//0xAC
	int16_t nBaseSkill[10];					//0xAE
	uint16_t pad0xC2;						//0xC2
};

struct D2DifficultyLevelsTxt
{
	uint32_t dwResistPenalty;				//0x00
	uint32_t dwDeathExpPenalty;				//0x04
	uint32_t dwUberCodeOddsNorm;			//0x08
	uint32_t dwUberCodeOddsGood;			//0x0C
	uint32_t dwMonsterSkillBonus;			//0x10
	uint32_t dwMonsterFreezeDiv;			//0x14
	uint32_t dwMonsterColdDiv;				//0x18
	uint32_t dwAiCurseDiv;					//0x1C
	uint32_t dwUltraCodeOddsNorm;			//0x20
	uint32_t dwUltraCodeOddsGood;			//0x24
	uint32_t dwLifeStealDiv;				//0x28
	uint32_t dwManaStealDiv;				//0x2C
	uint32_t dwUniqueDmgBonus;				//0x30
	uint32_t dwChampionDmgBonus;			//0x34
	uint32_t dwHireableBossDmgPercent;		//0x38
	uint32_t dwMonsterCEDmgPercent;			//0x3C
	uint32_t dwStaticFieldMin;				//0x40
	uint32_t dwGambleRare;					//0x44
	uint32_t dwGambleSet;					//0x48
	uint32_t dwGambleUniq;					//0x4C
	uint32_t dwGambleUber;					//0x50
	uint32_t dwGambleUltra;					//0x54
};

struct D2HireDescTxt
{
	uint32_t dwCode;						//0x00
};

enum D2C_HitClassIds {
	// Base
	HITCLASS_None                = 0,
	HITCLASS_HandToHand          = 1,
	HITCLASS_OneHandSwingVsSmall = 2,
	HITCLASS_OneHandSwingVsLarge = 3,
	HITCLASS_TwoHandSwingVsSmall = 4,
	HITCLASS_TwoHandSwingVsLarge = 5,
	HITCLASS_OneHandThrust       = 6,
	HITCLASS_TwoHandThrust       = 7,
	HITCLASS_Club                = 8,
	HITCLASS_Staff               = 9,
	HITCLASS_Bow                 = 10,
	HITCLASS_Crossbow			 = 11,
	HITCLASS_Claw				 = 12,
	HITCLASS_Overlay			 = 13,
	// Layers
	HITCLASS_Layer_Double	     = 16,
	HITCLASS_Layer_Fire		     = 32,
	HITCLASS_Layer_Cold		     = 48,
	HITCLASS_Layer_Lightning	 = 64,
	HITCLASS_Layer_Poison	     = 80,
	HITCLASS_Layer_Stun		     = 96,
	HITCLASS_Layer_Bash		     = 112,
	HITCLASS_Layer_Thorns	     = 128,
	HITCLASS_Layer_Sanctuary	 = 144,
	HITCLASS_Layer_SilentVoice   = 160,
	HITCLASS_Layer_Goo		     = 176,
};

struct D2HitClassTxt
{
	uint32_t dwCode;						//0x00
};

struct D2MissCalcTxt
{
	uint32_t dwCode;						//0x00
};

struct D2EventsTxt
{
	uint16_t wEvent;						//0x00
};

struct D2ElemTypesTxt
{
	uint32_t dwCode;						//0x00
};

struct D2ColorsTxt
{
	uint32_t dwCode;						//0x00
};

struct D2ExperienceTxt
{
	uint32_t dwClass[7];					//0x00
	uint32_t dwExpRatio;					//0x1C
};

struct D2ExperienceDataTbl
{
	struct D2ExperienceTxt tMax;
	struct D2ExperienceTxt aLevels[];
};

struct D2PlayerClassTxt
{
	uint32_t dwCode;						//0x00
};

struct D2PlrModeTxtStub
{
	uint32_t dwCode;						//0x00
};

struct D2MonAiTxt
{
	uint16_t wAi;							//0x00
};

struct D2MonModeTxtStub
{
	uint32_t dwCode;						//0x00
};

struct D2MonPlaceTxt
{
	uint16_t nCode;							//0x00
};

struct D2StorePageTxt
{
	uint32_t dwCode;						//0x00
};

enum D2C_PetTypeTxtFlagIndices
{
	PETTYPEFLAGINDEX_WARP = 0,
	PETTYPEFLAGINDEX_RANGE,
	PETTYPEFLAGINDEX_PARTYSEND,
	PETTYPEFLAGINDEX_UNSUMMON,
	PETTYPEFLAGINDEX_AUTOMAP,
	PETTYPEFLAGINDEX_DRAWHP,
};

enum D2C_PetTypeTxtFlags
{
	PETTYPEFLAG_WARP = (1 << PETTYPEFLAGINDEX_WARP),
	PETTYPEFLAG_RANGE = (1 << PETTYPEFLAGINDEX_RANGE),
	PETTYPEFLAG_PARTYSEND = (1 << PETTYPEFLAGINDEX_PARTYSEND),
	PETTYPEFLAG_UNSUMMON = (1 << PETTYPEFLAGINDEX_UNSUMMON),
	PETTYPEFLAG_AUTOMAP = (1 << PETTYPEFLAGINDEX_AUTOMAP),
	PETTYPEFLAG_DRAWHP = (1 << PETTYPEFLAGINDEX_DRAWHP),
};

struct D2PetTypeTxt
{
	uint32_t dwHcIdx;						//0x00
	uint32_t dwPetFlags;					//0x04
	uint16_t wGroup;						//0x08
	uint16_t wBaseMax;						//0x0A
	uint16_t wStringId;						//0x0C
	uint8_t nIconType;						//0x0E
	char szBaseicon[32];					//0x0F
	char szIcon[4][32];						//0x2F
	uint8_t pad0xAF[3];						//0xAF
	uint16_t wClass[4];						//0xB2
	uint8_t unk0xBA[2];						//0xBA
	int32_t nSkillCount;					//0xBC
	uint16_t wSkillIds[15];					//0xC0
	uint16_t unk0xDE;						//0xDE
};

struct D2StatesTxt
{
	uint16_t wState;						//0x00
	uint16_t wOverlay[4];					//0x02
	uint16_t wCastOverlay;					//0x0A
	uint16_t wRemoveOverlay;				//0x0C
	uint16_t wPrgOverlay;					//0x0E
	union
	{
		uint8_t nStateFlags[4];				//0x10
		uint32_t dwStateFlags;				//0x10
	};
	uint32_t dwStateFlagsEx;				//0x14
	uint16_t wStat;							//0x18
	uint16_t wSetFunc;						//0x1A
	uint16_t wRemFunc;						//0x1C
	uint16_t wGroup;						//0x1E
	uint8_t nColorPri;						//0x20
	uint8_t nColorShift;					//0x21
	uint8_t nLightRGB[3];					//0x22
	uint8_t pad0x25;						//0x25
	uint16_t wOnSound;						//0x26
	uint16_t wOffSound;						//0x28
	uint16_t wItemType;						//0x2A
	char nItemTrans;						//0x2C
	uint8_t nGfxType;						//0x2D
	uint16_t wGfxClass;						//0x2E
	uint16_t wCltEvent;						//0x30
	uint16_t wCltEventFunc;					//0x32
	uint16_t wCltActiveFunc;				//0x34
	uint16_t wSrvActiveFunc;				//0x36
	uint16_t wSkill;						//0x38
	uint16_t wMissile;						//0x3A
};

//TODO: see comments
struct D2DataTables
{
	struct D2PlayerClassTxt* pPlayerClassTxt;					//0x00
	struct D2TxtLink* pPlayerClassLinker;					//0x04
	struct D2BodyLocsTxt* pBodyLocsTxt;						//0x08
	struct D2TxtLink* pBodyLocsLinker;						//0x0C
	struct D2StorePageTxt* pStorePageTxt;						//0x10
	struct D2TxtLink* pStorePageLinker;					//0x14
	struct D2ElemTypesTxt* pElemTypesTxt;						//0x18
	struct D2TxtLink* pElemTypesLinker;					//0x1C
	struct D2HitClassTxt* pHitClassTxt;						//0x20
	struct D2TxtLink* pHitClassLinker;						//0x24
	struct D2MonModeTxtStub* pMonModeTxtStub;					//0x28
	struct D2TxtLink* pMonModeLinker;						//0x2C
	struct D2PlrModeTxtStub* pPlrModeTxtStub;					//0x30
	struct D2TxtLink* pPlrModeLinker;						//0x34
	struct D2SkillCalcTxt* pSkillCalcTxt;						//0x38
	struct D2TxtLink* pSkillCalcLinker;					//0x3C
	union FOGASTNode* pSkillsCode;						//0x40
	unsigned int nSkillsCodeSize;						//0x44
	unsigned int nSkillsCodeSizeEx;						//0x48
	union FOGASTNode* pSkillDescCode;						//0x4C
	unsigned int nSkillDescCodeSize;					//0x50
	unsigned int nSkillDescCodeSizeEx;					//0x54
	struct D2MissCalcTxt* pMissileCalcTxt;						//0x58
	struct D2TxtLink* pMissileCalcLinker;					//0x5C
	union FOGASTNode* pMissCode;							//0x60
	unsigned int nMissCodeSize;							//0x64
	int nMissCodeSizeEx;								//0x68

	/**/	const char* pSkillCode;                             //+0000006C   052C445C      skillcode.txt (Id from skills.txt)
	/**/	struct D2TxtLink* iSkillCode;                       //+00000070   0141F084      skillcode info

	struct D2EventsTxt* pEventsTxt;							//0x74
	struct D2TxtLink* pEventsLinker;						//0x78
	struct D2CompCodeTxt* pCompCodeTxt;						//0x7C
	struct D2TxtLink* pCompCodeLinker;						//0x80
	int nCompCodeTxtRecordCount;						//0x84
	struct D2MonAiTxt* pMonAiTxt;								//0x88
	struct D2TxtLink* pMonAiLinker;						//0x8C
	int nMonAiTxtRecordCount;							//0x90
	struct D2TxtLink* pItemsLinker;						//0x94
	union FOGASTNode* pItemsCode;							//0x98
	unsigned int nItemsCodeSize;						//0x9C
	int nItemsCodeSizeEx;								//0xA0
	struct D2PropertiesTxt* pPropertiesTxt;					//0xA4
	struct D2TxtLink* pPropertiesLinker;					//0xA8
	int nPropertiesTxtRecordCount;						//0xAC
	struct D2TxtLink* pRunesLinker;						//0xB0
	struct D2HireDescTxt* pHireDescTxt;						//0xB4
	struct D2TxtLink* pHireDescLinker;						//0xB8
	struct D2StatesTxt* pStatesTxt;							//0xBC
	struct D2TxtLink* pStatesLinker;						//0xC0
	int nStatesTxtRecordCount;							//0xC4
	uint32_t* pStateMasks;								//0xC8
	uint32_t* fStateMasks[40];							//0xCC
	short* pProgressiveStates;							//0x16C
	int nProgressiveStates;								//0x170
	short* pCurseStates;								//0x174
	int nCurseStates;									//0x178
	short* pTransformStates;							//0x17C
	int nTransformStates;								//0x180
	short* pActionStates;								//0x184
	int nActionStates;									//0x188
	short* pColourStates;								//0x18C
	int nColourStates;									//0x190
	struct D2SoundsTxtStub* pSoundsTxtCodes;					//0x194
	struct D2TxtLink* pSoundsLinker;						//0x198
	int nSoundsTxtCodes;								//0x19C
	struct D2HirelingTxt* pHirelingTxt;						//0x1A0
	int nHirelingTxtRecordCount;						//0x1A4
	int nClassicHirelingStartRecordIds[256];			//0x1A8
	int nExpansionHirelingStartRecordIds[256];			//0x5A8
	struct D2NpcTxt* pNpcTxt;									//0x9A8
	int nNpcTxtRecordCount;								//0x9AC
	struct D2ColorsTxt* pColorsTxt;							//0x9B0
	struct D2TxtLink* pColorsLinker;						//0x9B4
	struct D2TxtLink* pTreasureClassExLinker;				//0x9B8
	struct D2TCExShort* pTreasureClassEx;					//0x9BC
	int nTreasureClassEx;								//0x9C0
	struct D2TCExShort* pChestTreasureClasses[45];			//0x9C4
	struct D2MonStatsTxt* pMonStatsTxt;						//0xA78
	struct D2TxtLink* pMonStatsLinker;						//0xA7C
	int nMonStatsTxtRecordCount;						//0xA80
	struct D2MonSoundsTxt* pMonSoundsTxt;						//0xA84
	struct D2TxtLink* pMonSoundsLinker;					//0xA88
	int nMonSoundsTxtRecordCount;						//0xA8C
	struct D2MonStats2Txt* pMonStats2Txt;						//0xA90
	struct D2TxtLink* pMonStats2Linker;					//0xA94
	int nMonStats2TxtRecordCount;						//0xA98
	struct D2MonPlaceTxt* pMonPlaceTxt;						//0xA9C
	struct D2TxtLink* pMonPlaceLinker;						//0xAA0
	int nMonPlaceTxtRecordCount;						//0xAA4
	struct D2MonPresetTxt* pMonPresetTxt;						//0xAA8
	struct D2MonPresetTxt* pMonPresetTxtActSections[5];		//0xAAC
	int nMonPresetTxtActRecordCounts[5];				//0xAC0
	struct D2SuperUniquesTxt* pSuperUniquesTxt;				//0xAD4
	struct D2TxtLink* pSuperUniquesLinker;					//0xAD8
	int nSuperUniquesTxtRecordCount;					//0xADC
	short nSuperUniqueIds[66];							//0xAE0
	struct D2MissilesTxt* pMissilesTxt;						//0xB64
	struct D2TxtLink* pMissilesLinker;						//0xB68
	int nMissilesTxtRecordCount;						//0xB6C
	struct D2MonLvlTxt* pMonLvlTxt;							//0xB70
	int nMonLvlTxtRecordCount;							//0xB74
	struct D2AnimSeqTxt* pMonSeqTxt;							//0xB78
	struct D2TxtLink* pMonSeqLinker;						//0xB7C
	int nMonSeqTxtRecordCount;							//0xB80
	struct D2AnimSeqRecord* pMonSeqTable;						//0xB84
	int nMonSeqTableRecordCount;						//0xB88
	struct D2SkillDescTxt* pSkillDescTxt;						//0xB8C
	struct D2TxtLink* pSkillDescLinker;					//0xB90
	int nSkillDescTxtRecordCount;						//0xB94
	struct D2SkillsTxt* pSkillsTxt;							//0xB98
	struct D2TxtLink* pSkillsLinker;						//0xB9C
	int nSkillsTxtRecordCount;							//0xBA0
	int* nClassSkillCount;								//0xBA4
	int nHighestClassSkillCount;						//0xBA8
	short* nClassSkillList;								//0xBAC
	int nPassiveSkills;									//0xBB0
	uint16_t* pPassiveSkills;							//0xBB4
	struct D2TxtLink* pOverlayLinker;						//0xBB8
	struct D2OverlayTxt* pOverlayTxt;							//0xBBC
	int nOverlayTxtRecordCount;							//0xBC0
	struct D2CharStatsTxt* pCharStatsTxt;						//0xBC4
	int nCharStatsTxtRecordCount;						//0xBC8
	struct D2ItemStatCostTxt* pItemStatCostTxt;				//0xBCC
	struct D2TxtLink* pItemStatCostLinker;					//0xBD0
	int nItemStatCostTxtRecordCount;					//0xBD4
	uint16_t* pStatsWithDescFunc;						//0xBD8
	int nStatsWithDescFunc;								//0xBDC
	struct D2MonEquipTxt* pMonEquipTxt;						//0xBE0
	int nMonEquipTxtRecordCount;						//0xBE4
	struct D2PetTypeTxt* pPetTypeTxt;							//0xBE8
	struct D2TxtLink* pPetTypeLinker;						//0xBEC
	int nPetTypeTxtRecordCount;							//0xBF0
	struct D2TxtLink* pItemTypesLinker;					//0xBF4
	struct D2ItemTypesTxt* pItemTypesTxt;						//0xBF8
	int nItemTypesTxtRecordCount;						//0xBFC
	int nItemTypesIndex;								//0xC00
	uint32_t* pItemTypesEquivalenceLUTs;				//0xC04
	struct D2TxtLink* pSetsLinker;							//0xC08
	struct D2SetsTxt* pSetsTxt;								//0xC0C
	int nSetsTxtRecordCount;							//0xC10
	struct D2TxtLink* pSetItemsLinker;						//0xC14
	struct D2SetItemsTxt* pSetItemsTxt;						//0xC18
	int nSetItemsTxtRecordCount;						//0xC1C
	struct D2TxtLink* pUniqueItemsLinker;					//0xC20
	struct D2UniqueItemsTxt* pUniqueItemsTxt;					//0xC24
	int nUniqueItemsTxtRecordCount;						//0xC28
	struct D2TxtLink* pMonPropLinker;						//0xC2C
	struct D2MonPropTxt* pMonPropTxt;							//0xC30
	int nMonPropTxtRecordCount;							//0xC34
	struct D2TxtLink* pMonTypeLinker;						//0xC38
	struct D2MonTypeTxt* pMonTypeTxt;							//0xC3C
	int nMonTypeTxtRecordCount;							//0xC40
	uint32_t* pMonTypeNest;								//0xC44
	int nMonTypeIndex;									//0xC48
	struct D2TxtLink* pMonUModLinker;						//0xC4C
	struct D2MonUModTxt* pMonUModTxt;							//0xC50
	int nMonUModTxtRecordCount;							//0xC54
	struct D2LevelsTxt* pLevelsTxt;							//0xC58
	int nLevelsTxtRecordCount;							//0xC5C
	struct D2LevelDefBin* pLevelDefBin;						//0xC60
	struct D2LvlPrestTxt* pLvlPrestTxt;						//0xC64
	int nLvlPrestTxtRecordCount;						//0xC68
	int nStuff;											//0xC6C
	int nShiftedStuff;									//0xC70
	struct D2AnimDataTable* pAnimData;						//0xC74
	struct D2ExperienceDataTbl* pExperienceTxt;				//0xC78
	struct D2DifficultyLevelsTxt* pDifficultyLevelsTxt;		//0xC7C
	int nDifficultyLevelsTxtRecordCount;				//0xC80
	BOOL bCompileTxt;									//0xC84
	int ExpFieldI[9];									//0xC88
	uint8_t* pFieldData;								//0xCAC
	struct D2CollisionField pCollisionField;				//0xCB0
	struct D2CubeMainTxt* pCubeMainTxt;						//0xCC4
	int nCubeMainTxtRecordCount;						//0xCC8
	int nInventoryTxtRecordCount;						//0xCCC
	struct D2InventoryTxt* pInventoryTxt;						//0xCD0

	uint32_t unk0xCD4;									//0xCD4

	struct D2ItemDataTbl pItemDataTables;						//0xCD8
	uint16_t* pIndexOldToCurrent;						//0xCF8	
	struct D2GemDataTbl pGemDataTables;						//0xCFC
	struct D2LowQualityItemDataTbl pLowQualityItemDataTables;	//0xD04
	struct D2BookDataTbl pBookDataTables;						//0xD0C
	struct D2RareAffixDataTbl pRareAffixDataTables;			//0xD14
	struct D2ItemRatioDataTbl pItemRatioDataTables;			//0xD24

	uint32_t unk0xD2C;									//0xD2C

	struct D2GambleDataTbl pGambleDataTables;					//0xD30
	struct D2MagicAffixDataTbl pMagicAffixDataTables;			//0xEC8
	struct D2RuneDataTbl pRuneDataTables;						//0xEDC
	struct D2QualityItemDataTbl pQualityItemDataTables;		//0xEE4

	uint32_t unk0xEEC;									//0xEEC

	struct D2Seed pAutomapSeed;							//0xEF0
	struct D2AutomapRand pAutoMapRand[36];					//0xEF8
	struct D2LvlTypesTxt* pLvlTypesTxt;						//0x1018
	int* pPortalLevels;									//0x101C
	int nPortalLevels;									//0x1020
	int nLvlTypesTxtRecordCount;						//0x1024
	struct D2LvlWarpTxt* pLvlWarpTxt;							//0x1028
	int nLvlWarpTxtRecordCount;							//0x102C
	struct D2LvlMazeTxt* pLvlMazeTxt;							//0x1030
	int nLvlMazeTxtRecordCount;							//0x1034
	struct D2LvlSubTxt* pLvlSubTxt;							//0x1038
	int nLvlSubTxtRecordCount;							//0x103C
	int* pLvlSubTypeStartIds;							//0x1040
	struct D2TileLibraryHash** ppTileLibraryHash;			//0x1044
	struct D2DrlgFile** ppLvlPrestFiles;					//0x1048
	struct D2DrlgFile** ppLvlSubTypeFiles;					//0x104C
	struct D2AutomapShort* pAutoMap;						//0x1050
	int nAutoMap;										//0x1054
	char szDefaultString;								//0x1058
	char pad0x1059[3];									//0x1059
	struct D2MonItemPercentDataTbl pMonItemPercentDataTables;	//0x105C
	struct Unicode wszDefault;									//0x1064
	uint16_t unk0x1066;									//0x1066
	struct D2UniqueTitleTxt* pUniqueTitleTxt;					//0x1068
	struct D2UniquePrefixTxt* pUniquePrefixTxt;				//0x106C
	struct D2UniqueSuffixTxt* pUniqueSuffixTxt;				//0x1070
	struct D2UniqueAppellationTxt* pUniqueAppellationTxt;		//0x1074
	int nUniqueTitleTxtRecordCount;						//0x1078
	int nUniquePrefixTxtRecordCount;					//0x107C
	int nUniqueSuffixTxtRecordCount;					//0x1080
	int nUniqueAppellationTxtRecordCount;				//0x1084

	uint32_t unk7[2];									//+00001088
	short nTreasureClassItemTypes;						//0x1090
	short unk0x1092;									//0x1092

	struct D2ShrinesTxt* pShrinesTxt;							//0x1094
	int nShrinesTxtRecordCount;							//0x1098
	struct D2ObjectsTxt* pObjectsTxt;							//0x109C
	int nObjectsTxtRecordCount;							//0x10A0
	struct D2ObjGroupTxt* pObjGroupTxt;						//0x10A4
	int nObjGroupTxtRecordCount;						//0x10A8
	struct D2ArmTypeTxt* pArmTypeTxt;							//0x10AC
	struct D2MonModeDataTbl pMonModeDataTables;				//0x10B0
	struct D2CompositTxt* pCompositTxt;						//0x10C0
	struct D2ObjModeDataTbl pObjModeDataTables;				//0x10C4
	struct D2PlrModeDataTbl pPlrModeDataTables;				//0x10D4
};

// D2Common.0x6FDE9600
extern struct D2ArenaTxt* gpArenaTxtTable;
// D2Common.0x6FDE95F8
extern struct D2CharTemplateTxt* gpCharTemplateTxtTable;
extern int gnCharTemplateTxtTableRecordCount;
extern uint32_t gnCharTemplateStartIds[64];
// D2Common.0x6FDE9604
extern struct D2BeltsTxt* gpBeltsTxtTable;
extern struct D2DataTables gpDataTables;
// D2Common.0x6FDD6A20 (#10042)
extern D2COMMON_DLL_DECL struct D2DataTables * sgptDataTables;


//D2Common.0x6FDEA704
extern LPCRITICAL_SECTION gpLvlSubTypeFilesCriticalSection;

//TODO: Reimport defs from .cpps

//D2Common.0x6FDD6A24
extern BOOL DATATBLS_LoadFromBin;



#pragma pack()

//D2Common.0x6FD494D0
uint16_t __fastcall DATATBLS_GetStringIdFromReferenceString(char* szReference);
//D2Common.0x6FD49500 - Changed this function a lot (had 6 hardcoded (i.e. pre-defined) Args)
void __fastcall DATATBLS_InitUnicodeClassNamesInCharStatsTxt();
//D2Common.0x6FD49660 (#11255)
D2COMMON_DLL_DECL uint32_t __stdcall DATATBLS_GetCodeFromCompCodeTxt(int nCompCode);
//D2Common.0x6FD49680 (#11249)
D2COMMON_DLL_DECL uint32_t __stdcall DATATBLS_GetExpRatio(int nLevel);
//D2Common.0x6FD496B0 (#10628)
D2COMMON_DLL_DECL uint32_t __stdcall DATATBLS_GetLevelThreshold(int nClass, uint32_t dwLevel);
//D2Common.0x6FD496E0 (#10629)
D2COMMON_DLL_DECL int __stdcall DATATBLS_GetMaxLevel(int nClass);
//D2Common.0x6FD49710 (#10630)
D2COMMON_DLL_DECL uint32_t __stdcall DATATBLS_GetCurrentLevelFromExp(int nClass, uint32_t dwExperience);
//D2Common.0x6FD49760
void __fastcall DATATBLS_GetBinFileHandle(HD2ARCHIVE hArchive, const char* szFile, void** ppFileHandle, int* pSize, int* pSizeEx);
//D2Common.0x6FD49850
int __fastcall DATATBLS_AppendMemoryBuffer(char** ppCodes, int* pSize, int* pSizeEx, void* pBuffer, int nBufferSize);




//D2Common.0x6FD4E4B0 (#10593)
D2COMMON_DLL_DECL struct D2CharStatsTxt* __fastcall DATATBLS_GetCharstatsTxtTable();
//D2Common.0x6FD4E4C0
struct D2AnimDataTable* __fastcall DATATBLS_GetAnimData();
//D2Common.0x6FD4E4D0 (#10655)
D2COMMON_DLL_DECL struct D2DifficultyLevelsTxt* __stdcall DATATBLS_GetDifficultyLevelsTxtRecord(int nDifficulty);
//D2Common.0x6FD4E500
void __fastcall DATATBLS_LoadStatesTxt(HD2ARCHIVE hArchive);
//D2Common.0x6FD4F4A0
void __fastcall DATATBLS_UnloadStatesTxt();
// Helper function
struct D2StatesTxt* DATATBLS_GetStatesTxtRecord(int nStateId);
//D2Common.0x6FD4F5A0
void __fastcall DATATBLS_LoadPetTypeTxt(HD2ARCHIVE hArchive);
//D2Common.0x6FD4F990 (#11298)
D2COMMON_DLL_DECL char* __stdcall DATATBLS_GetUnitNameFromUnit(struct D2Unit* pUnit, char* szName);
//D2Common.0x6FD4FB50 (#11299)
D2COMMON_DLL_DECL char* __stdcall DATATBLS_GetUnitNameFromUnitTypeAndClassId(int nUnitType, int nClassId, char* szName);
//D2Common.0x6FD4FCF0 (#10580)
D2COMMON_DLL_DECL void __stdcall DATATBLS_WriteBinFile(char* szFileName, void* pWriteBuffer, size_t nBufferSize, int nRecordCount);
//D2Common.0x6FD4FD70 (#10578)
D2COMMON_DLL_DECL void* __stdcall DATATBLS_CompileTxt(HD2ARCHIVE hArchive, const char* szName, struct D2BinField* pTbl, int* pRecordCount, size_t dwSize);
//D2Common.0x6FD500F0 (#11242)
D2COMMON_DLL_DECL void __stdcall DATATBLS_ToggleCompileTxtFlag(BOOL bSilent);
//D2Common.0x6FD50110 (#10579)
D2COMMON_DLL_DECL void __stdcall DATATBLS_UnloadBin(void* pBinFile);
//D2Common.0x6FD50150 (#10575)
D2COMMON_DLL_DECL void __stdcall DATATBLS_UnloadAllBins();
//D2Common.0x6FD504B0 (#10576)
D2COMMON_DLL_DECL void __stdcall DATATBLS_LoadAllTxts(HD2ARCHIVE hArchive, int a2, int a3);
//D2Common.0x6FD507B0
void __fastcall DATATBLS_LoadSomeTxts(HD2ARCHIVE hArchive);
//D2Common.0x6FD50FB0
void __fastcall DATATBLS_LoadCharStatsTxt(HD2ARCHIVE hArchive);
//D2Common.0x6FD51BF0
void __fastcall DATATBLS_LoadDifficultyLevelsTxt(HD2ARCHIVE hArchive);


struct D2MonStatsTxt* __fastcall DATATBLS_GetMonStatsTxtRecord(int nMonsterId);

inline int __fastcall DATATBLS_GetMonStatsTxtRecordCount()
{
	return sgptDataTables->nMonStatsTxtRecordCount;
}
