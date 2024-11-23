#pragma once

#include "CommonDefinitions.h"
#include "Item.h"
#include "Missile.h"
#include "Monster.h"
#include "Object.h"
#include "Player.h"
#include "D2Chat.h"
#include <DataTbls/AnimTbls.h>

struct D2Game; // From D2Game
struct D2QuestChain; // From D2Game
struct D2TimerArg; // From D2Game
struct D2DrlgAct;
struct D2StatListEx;
struct D2UnitEvent;
struct D2SkillList;
struct D2Skill;

struct D2GfxData;
struct D2GfxLight;

#pragma pack(1)

enum D2C_UnitTypes
{
	UNIT_PLAYER,
	UNIT_MONSTER,
	UNIT_OBJECT,
	UNIT_MISSILE,
	UNIT_ITEM,
	UNIT_TILE,
	UNIT_TYPES_COUNT // Used as an invalid value
};

enum D2C_UnitFlags
{
	UNITFLAG_DOUPDATE = 0x00000001,				//tells to update the unit
	UNITFLAG_TARGETABLE = 0x00000002,			//whenever the unit can be selected or not
	UNITFLAG_CANBEATTACKED = 0x00000004,		//whenever the unit can be attacked
	UNITFLAG_ISVALIDTARGET = 0x00000008,		//used to check if unit is a valid target
	UNITFLAG_INITSEEDSET = 0x00000010,			//tells whenever the unit seed has been initialized
	UNITFLAG_DRAWSHADOW = 0x00000020,			//tells whenver to draw a shadow or not (client only)
	UNITFLAG_SKSRVDOFUNC = 0x00000040,			//set when skill srvdofunc is executed
	UNITFLAG_OBJPREOPERATE = 0x00000080,		//unknown, used by objects with pre-operate disabled
	UNITFLAG_HASTXTMSG = 0x00000100,			//whenever this unit has a text message attached to it
	UNITFLAG_ISMERC = 0x00000200,				//is mercenary unit
	UNITFLAG_HASEVENTSOUND = 0x00000400,		//does this unit have an event-sound attached to it (server)
	UNITFLAG_SUMMONER = 0x00000800,				//set for the summoner only
	UNITFLAG_SENDREFRESHMSG = 0x00001000,		//used by items to send a refresh message when it drops on ground
	UNITFLAG_ISLINKREFRESHMSG = 0x00002000,		//tells whenever this unit is linked to an update message chain
	UNITFLAG_SQGFXCHANGE = 0x00004000,			//tells whenever to load new anim for skill SQ
	UNITFLAG_UPGRLIFENHITCLASS = 0x00008000,	//updates life% and hitclass on client
	UNITFLAG_ISDEAD = 0x00010000,				//unit is dead
	UNITFLAG_NOTC = 0x00020000,					//disables treasureclass drops
	UNITFLAG_MONMODEISCHANGING = 0x00080000,	//set when monmode changes
	UNITFLAG_PREDRAW = 0x00100000,				//pre-draw this unit (like floor tiles, client only)
	UNITFLAG_ISASYNC = 0x00200000,				//is async unit (critters)
	UNITFLAG_ISCLIENTUNIT = 0x00400000,			//is client unit
	UNITFLAG_ISINIT = 0x01000000,				//set when unit has been initialized
	UNITFLAG_ISRESURRECT = 0x02000000,			//set for resurrected units and items on floor
	UNITFLAG_NOXP = 0x04000000,					//no xp gain from killing this unit
	UNITFLAG_AUTOMAP = 0x10000000,				//automap stuff
	UNITFLAG_AUTOMAP2 = 0x20000000,				//automap stuff
	UNITFLAG_PETIGNORE = 0x40000000,			//ignored by pets
	UNITFLAG_ISREVIVE = 0x80000000				//is revived monster
};

enum D2C_UnitFlagsEx
{
	UNITFLAGEX_HASINV = 0x00000001,				//unit has inventory attached to it
	UNITFLAGEX_UPDATEINV = 0x00000002,			//tells to update inventory content
	UNITFLAGEX_ISVENDORITEM = 0x00000004,		//set for vendor shop items
	UNITFLAGEX_ISSHAPESHIFTED = 0x00000008,		//unit is shapeshifted
	UNITFLAGEX_ITEMINIT = 0x00000010,			//set for items, related to init
	UNITFLAGEX_ISINLOS = 0x00000080,			//unit is in client's line of sight
	UNITFLAGEX_HASBEENDELETED = 0x00000100,		//unit has been deleted but not free'd yet
	UNITFLAGEX_STOREOWNERINFO = 0x00000400,		//unit stores info about owner
	UNITFLAGEX_ISCORPSE = 0x00001000,			//unit is a corpse (use UNITFLAG_ISDEAD instead)
	UNITFLAGEX_UNK_PATH_RELATED = 0x00002000,	//related to path
	UNITFLAGEX_TELEPORTED = 0x00010000,			//unit has been teleported, needs resync
	UNITFLAGEX_STORELASTATTACKER = 0x00020000,	//unit stores info about last attacker
	UNITFLAGEX_NODRAW = 0x00040000,				//don't draw this unit
	UNITFLAGEX_ISEXPANSION = 0x02000000,		//is expansion unit
	UNITFLAGEX_SERVERUNIT = 0x04000000			//is server-side unit
};

enum D2C_UnitAlignment {

	UNIT_ALIGNMENT_EVIL = 0,
	UNIT_ALIGNMENT_NEUTRAL = 1,
	UNIT_ALIGNMENT_GOOD = 2,
	UNIT_NUM_ALIGNMENT = 3,
	UNIT_ALIGNMENT_UNASSIGNED = 4,
};

//TODO: Redo Header defs when .cpp is done


struct D2EventTimer;

struct D2UnitPacketList
{
	struct D2UnitPacketList* pNext;
	uint8_t nHeader;
	//uint8_t nData[255];
};

struct D2Unit
{
	uint32_t dwUnitType;						//0x00 D2C_UnitTypes
	int32_t dwClassId;							//0x04
	void* pMemoryPool;							//0x08
	D2UnitGUID dwUnitId;						//0x0C
	union										//0x10
	{
		uint32_t dwAnimMode;					//Player, Monster, Object
		uint32_t dwItemMode;					//Items, see D2C_ItemModes
		uint32_t dwMissileMode;					// see D2C_MissileModes
	};
	union										//0x14
	{
		struct D2PlayerData* pPlayerData;
		struct D2ItemData* pItemData;
		struct D2MonsterData* pMonsterData;
		struct D2ObjectData* pObjectData;
		struct D2MissileData* pMissileData;
	};
	uint8_t nAct;								//0x18
	uint8_t unk0x19[3];							//0x19
	struct D2DrlgAct* pDrlgAct;					//0x1C
	struct D2Seed pSeed;							//0x20
	uint32_t dwInitSeed;						//0x28
	union										//0x2C
	{
		struct D2DynamicPath* pDynamicPath;
		struct D2StaticPath* pStaticPath;
	};
	struct D2AnimSeqTxt* pAnimSeq;				//0x30
	uint32_t dwSeqFrameCount;					//0x34
	int32_t dwSeqFrame;							//0x38
	uint32_t dwSeqSpeed;						//0x3C
	uint32_t dwSeqMode;							//0x40
	int32_t nSeqCurrentFramePrecise;			//0x44 8-bits fixed point. Actually reused as stop frame when not using a seq. For example for missiles / inferno.
	int32_t dwFrameCountPrecise;				//0x48 8-bits fixed point.
	int16_t wAnimSpeed;							//0x4C
	uint8_t nActionFrame;						//0x4E
	uint8_t unk0x4F;							//0x4F
	const struct D2AnimDataRecord* pAnimData;		//0x50
	struct D2GfxData* pGfxData;					//0x54
	struct D2GfxData* pGfxDataCopy;				//0x58
	struct D2StatListEx* pStatListEx;				//0x5C
	struct D2Inventory* pInventory;				//0x60
	union
	{
		struct									//Server Unit
		{
			D2UnitGUID dwInteractGUID;			//0x064
			uint32_t dwInteractType;			//0x068
			uint16_t nInteract;					//0x06C
			uint16_t nUpdateType;				//0x06E
			struct D2Unit* pUpdateUnit;			//0x070
			struct D2QuestChain* pQuestEventList;	//0x074
			BOOL bSparkChest;					//0x078
			void* pTimerParams;					//0x07C
			struct D2Game* pGame;					//0x080
			uint32_t unk0x084[3];				//0x084
			struct D2UnitEvent* pSrvUnitEventsList;//0x090
		};

		struct									//Client Unit
		{
			struct D2GfxLight* pLight;				//0x064
			uint32_t dwStartLight;				//0x068
			int32_t nPaletteIndex;				//0x06C
			BOOL bUnitSfx;						//0x070
			uint32_t dwSfxMode;					//0x074
			void* pUnitSfxData;					//0x078
			uint32_t dwSfxTicks;				//0x07C
			uint32_t dwSfxAsyncTicks;			//0x080
			uint32_t dwSfxStepTicks;			//0x084
			BOOL bHasActiveSound;				//0x088
			uint16_t nLastClickX;				//0x08C
			uint16_t nLastClickY;				//0x08E
			struct D2UnitEvent* pCltTimerList;		//0x090
		};
	};
	uint32_t dwOwnerType;						//0x94
	D2UnitGUID dwOwnerGUID;						//0x98
	uint32_t dwKillerType;						//0x09C
	D2UnitGUID dwKillerGUID;						//0x0A0
	struct D2HoverText* pHoverText;				//0xA4
	struct D2SkillList* pSkills;					//0xA8
	struct D2Combat* pCombat;				//0xAC
	uint32_t dwLastHitClass;					//0xB0
	uint32_t unk0xB4;							//0xB4
	uint32_t dwDropItemCode;					//0xB8
	uint32_t unk0xBC[2];						//0xBC
	uint32_t dwFlags;							//0xC4
	uint32_t dwFlagEx;							//0xC8
	void* pUnused0xCC;							//0xCC may be quest related ?

	uint32_t dwNodeIndex;						//0xD0
	uint32_t dwTickCount;						//0xD4
	union										//0xD8
	{
		uint32_t dwSrvTickCount;				//Server pUnit
		struct D2PacketList* pPacketList;	//Client pUnit
	};
	struct D2EventTimer* pTimer;					//0xDC
	struct D2Unit* pChangeNextUnit;				//0xE0
	struct D2Unit* pListNext;						//0xE4
	struct D2Unit* pRoomNext;						//0xE8
	struct D2UnitPacketList* pMsgFirst;			//0xEC
	struct D2UnitPacketList* pMsgLast;				//0xF0
};

#pragma pack()

// Helper function
static inline struct D2AnimSeqTxt* UNITS_GetAnimSeq(struct D2Unit* pUnit) { 
	return (pUnit->dwUnitType == UNIT_PLAYER || pUnit->dwUnitType == UNIT_MONSTER) ? pUnit->pAnimSeq : nullptr;
}

//D2Common.0x6FDBD520 (#10457)
D2COMMON_DLL_DECL uint8_t UNITS_GetDirection(struct D2Unit* pUnit);
//D2Common.0x6FDBD570 (#10320)
D2COMMON_DLL_DECL struct D2Skill* UNITS_GetStartSkill(struct D2Unit* pUnit);
//D2Common.0x6FDBD5B0 (#10321)
D2COMMON_DLL_DECL struct D2Skill* UNITS_GetLeftSkill(struct D2Unit* pUnit);
//D2Common.0x6FDBD5F0 (#10322)
D2COMMON_DLL_DECL struct D2Skill* UNITS_GetRightSkill(struct D2Unit* pUnit);
//D2Common.0x6FDBD630 (#10324)
D2COMMON_DLL_DECL void UNITS_SetUsedSkill(struct D2Unit* pUnit, struct D2Skill* pUsedSkill);
//D2Common.0x6FDBD670 (#10323)
D2COMMON_DLL_DECL struct D2Skill* UNITS_GetUsedSkill(struct D2Unit* pUnit);
//D2Common.0x6FDBD6B0 (#11259)
D2COMMON_DLL_DECL struct D2Unit* UNITS_AllocUnit(void* pMemPool, int nUnitType);
//D2Common.0x6FDBD720 (#11260)
D2COMMON_DLL_DECL void UNITS_FreeUnit(struct D2Unit* pUnit);
//D2Common.0x6FDBD780 (#10327)
D2COMMON_DLL_DECL int UNITS_GetPrecisionX(struct D2Unit* pUnit);
//D2Common.0x6FDBD7D0 (#10330)
D2COMMON_DLL_DECL int UNITS_GetPrecisionY(struct D2Unit* pUnit);
//D2Common.0x6FDBD820 (#10328)
D2COMMON_DLL_DECL void UNITS_SetXForStaticUnit(struct D2Unit* pUnit, int nX);
//D2Common.0x6FDBD890 (#10331)
D2COMMON_DLL_DECL void UNITS_SetYForStaticUnit(struct D2Unit* pUnit, int nY);
//D2Common.0x6FDBD900 (#10336)
D2COMMON_DLL_DECL int UNITS_GetUnitSizeX(struct D2Unit* pUnit);
//D2Common.0x6FDBDA00 (#10337)
D2COMMON_DLL_DECL int UNITS_GetUnitSizeY(struct D2Unit* pUnit);
//D2Common.0x6FDBDB10 (#10333)
D2COMMON_DLL_DECL int UNITS_GetClientCoordX(struct D2Unit* pUnit);
//D2Common.0x6FDBDB60 (#10334)
D2COMMON_DLL_DECL int UNITS_GetClientCoordY(struct D2Unit* pUnit);
//D2Common.0x6FDBDBB0 (#10411)
D2COMMON_DLL_DECL int UNITS_GetAbsoluteXDistance(struct D2Unit* pUnit1, struct D2Unit* pUnit2);
//D2Common.0x6FDBDC20 (#10412)
D2COMMON_DLL_DECL int UNITS_GetAbsoluteYDistance(struct D2Unit* pUnit1, struct D2Unit* pUnit2);
//D2Common.0x6FDBDC90 (#10340)
D2COMMON_DLL_DECL void UNITS_SetTargetX(struct D2Unit* pUnit, int nTargetX);
//D2Common.0x6FDBDCD0 (#10341)
D2COMMON_DLL_DECL void UNITS_SetTargetY(struct D2Unit* pUnit, int nTargetY);
//D2Common.0x6FDBDD10 (#10332)
D2COMMON_DLL_DECL void UNITS_GetCoords(struct D2Unit* pUnit, struct D2Coord* pCoord);
//D2Common.0x6FDBDDA0 (#10335)
D2COMMON_DLL_DECL void UNITS_GetClientCoords(struct D2Unit* pUnit, struct D2Coord* pClientCoords);
//D2Common.0x6FDBDE10 (#10338)
D2COMMON_DLL_DECL int UNITS_GetCollisionMask(struct D2Unit* pUnit);
//D2Common.0x6FDBDEC0 (#10352)
D2COMMON_DLL_DECL void UNITS_FreeCollisionPath(struct D2Unit* pUnit);
//D2Common.0x6FDBE060 (#10351)
D2COMMON_DLL_DECL void UNITS_BlockCollisionPath(struct D2Unit* pUnit, struct D2ActiveRoom* pRoom, int nX, int nY);
//D2Common.0x6FDBE1A0 (#10350)
D2COMMON_DLL_DECL void UNITS_InitializeStaticPath(struct D2Unit* pUnit, struct D2ActiveRoom* pRoom, int nX, int nY);
//D2Common.0x6FDBE210 (#10343)
D2COMMON_DLL_DECL void UNITS_ResetRoom(struct D2Unit* pUnit);
//D2Common.0x6FDBE270 (#10342)
D2COMMON_DLL_DECL struct D2ActiveRoom* UNITS_GetRoom(struct D2Unit* pUnit);
//D2Common.0x6FDBE2D0 (#10344)
D2COMMON_DLL_DECL void UNITS_SetTargetUnitForDynamicUnit(struct D2Unit* pUnit, struct D2Unit* pTargetUnit);
//D2Common.0x6FDBE330 (#10345)
D2COMMON_DLL_DECL int UNITS_GetTargetTypeFromDynamicUnit(struct D2Unit* pUnit);
//D2Common.0x6FDBE3A0 (#10346)
D2COMMON_DLL_DECL D2UnitGUID UNITS_GetTargetGUIDFromDynamicUnit(struct D2Unit* pUnit);
//D2Common.0x6FDBE410 (#10347)
D2COMMON_DLL_DECL void UNITS_SetTargetUnitForPlayerOrMonster(struct D2Unit* pUnit, struct D2Unit* pTargetUnit);
//D2Common.0x6FDBE470 (#10354)
D2COMMON_DLL_DECL void UNITS_GetRunAndWalkSpeedForPlayer(int nUnused, int nCharId, int* pWalkSpeed, int* pRunSpeed);
//D2Common.0x6FDBE4C0 (#10325)
D2COMMON_DLL_DECL void UNITS_SetAnimData(struct D2Unit* pUnit, int nUnitType, int nClassId, int nMode);
//D2Common.0x6FDBE510
void UNITS_SetAnimStartFrame(struct D2Unit* pUnit);
//D2Common.0x6FDBEA60 (#10348)
D2COMMON_DLL_DECL BOOL UNITS_ChangeAnimMode(struct D2Unit* pUnit, int nMode);
//D2Common.0x6FDBEAD0 (#10355)
D2COMMON_DLL_DECL int UNITS_IsCurrentRoomInvalid(struct D2Unit* pUnit);
//D2Common.0x6FDBEB20 (#10356)
D2COMMON_DLL_DECL void UNITS_SetCurrentRoomInvalid(struct D2Unit* pUnit, int a2);
//D2Common.0x6FDBEB80 (#10357)
D2COMMON_DLL_DECL void UNITS_RefreshInventory(struct D2Unit* pUnit, BOOL bSetFlag);
//D2Common.0x6FDBEBE0 (#10409)
D2COMMON_DLL_DECL int UNITS_GetInventoryRecordId(struct D2Unit* pUnit, int nInvPage, BOOL bLoD);
//D2Common.0x6FDBECD0 (#10383)
D2COMMON_DLL_DECL struct D2GfxLight* UNITS_ResetLightMap(struct D2Unit* pUnit);
//D2Common.0x6FDBED10 (#10369)
D2COMMON_DLL_DECL int UNITS_GetAnimOrSeqMode(struct D2Unit* pUnit);
//D2Common.0x6FDBED40 (#10370)
D2COMMON_DLL_DECL void UNITS_SetAnimOrSeqMode(struct D2Unit* pUnit, int nAnimMode);
//D2Common.0x6FDBED90 (#10371)
D2COMMON_DLL_DECL void UNITS_InitializeSequence(struct D2Unit* pUnit);
//D2Common.0x6FDBEE20 (#10372)
D2COMMON_DLL_DECL void UNITS_SetAnimationFrame(struct D2Unit* pUnit, int nFrame);
//D2Common.0x6FDBEE60 (#10373)
D2COMMON_DLL_DECL void UNITS_StopSequence(struct D2Unit* pUnit);
//D2Common.0x6FDBEFF0 (#10374)
D2COMMON_DLL_DECL void UNITS_UpdateFrame(struct D2Unit* pUnit);
//D2Common.0x6FDBF020 (#10375)
D2COMMON_DLL_DECL void D2COMMON_10375_UNITS_SetFrameNonRate(struct D2Unit* pUnit, int nRate, int nFailRate);
//1.10f: D2Common.0x6FDBF050 (#10376)
//1.13c: D2Common.0x6FD83110 (#10819)
D2COMMON_DLL_DECL void UNITS_UpdateAnimRateAndVelocity(struct D2Unit* pUnit, const char* szFile, int nLine);
//D2Common.0x6FDBF8D0 (#10377)
D2COMMON_DLL_DECL void UNITS_SetAnimationSpeed(struct D2Unit* pUnit, int nSpeed);
//D2Common.0x6FDBF910 (#10378)
D2COMMON_DLL_DECL int UNITS_IsAtEndOfFrameCycle(struct D2Unit* pUnit);
//D2Common.0x6FDBF970 (#10379)
D2COMMON_DLL_DECL void UNITS_GetShiftedFrameMetrics(struct D2Unit* pUnit, int* pFrameNo, int* pFrameCount);
//D2Common.0x6FDBF9E0 (#10380)
D2COMMON_DLL_DECL void UNITS_GetFrameMetrics(struct D2Unit* pUnit, int* pFrame, int* pFrameCount);
//D2Common.0x6FDBFA40 (#10381)
D2COMMON_DLL_DECL void UNITS_SetAnimActionFrame(struct D2Unit* pUnit, int nFrame);
//D2Common.0x6FDBFA90 (#10382)
D2COMMON_DLL_DECL int UNITS_GetEventFrameInfo(struct D2Unit* pUnit, int nFrame);
//D2Common.0x6FDBFB40 (#10410)
D2COMMON_DLL_DECL BOOL UNITS_HasCollision(struct D2Unit* pUnit);
//D2Common.0x6FDBFB70 (#10358)
D2COMMON_DLL_DECL struct D2Skill* UNITS_GetSkillFromSkillId(struct D2Unit* pUnit, int nSkillId);
//D2Common.0x6FDBFC10 (#10392)
D2COMMON_DLL_DECL BOOL UNITS_IsDoor(struct D2Unit* pUnit);
//D2Common.0x6FDBFC50
bool UNITS_CheckIfObjectOrientationIs1(struct D2Unit* pUnit);
//D2Common.0x6FDBFC90 (#10393)
D2COMMON_DLL_DECL BOOL UNITS_IsShrine(struct D2Unit* pUnit);
//D2Common.0x6FDBFCB0 (#10394)
D2COMMON_DLL_DECL struct D2ObjectsTxt* UNITS_GetObjectTxtRecordFromObject(struct D2Unit* pUnit);
//D2Common.0x6FDBFD00 (#10395)
D2COMMON_DLL_DECL struct D2ShrinesTxt* UNITS_GetShrineTxtRecordFromObject(struct D2Unit* pUnit);
//D2Common.0x6FDBFD50 (#10396)
D2COMMON_DLL_DECL void UNITS_SetShrineTxtRecordInObjectData(struct D2Unit* pUnit, struct D2ShrinesTxt* pShrinesTxtRecord);
//D2Common.0x6FDBFDB0 (#10413)
D2COMMON_DLL_DECL void UNITS_UpdateDirectionAndSpeed(struct D2Unit* pUnit, int nX, int nY);
//D2Common.0x6FDBFDD0 (#10414)
D2COMMON_DLL_DECL int UNITS_GetNewDirection(struct D2Unit* pUnit);
//D2Common.0x6FDBFF20 (#10416)
D2COMMON_DLL_DECL void UNITS_StoreOwnerTypeAndGUID(struct D2Unit* pUnit, int nOwnerType, D2UnitGUID nOwnerId);
//D2Common.0x6FDBFF40
void UNITS_StoreOwnerInfo(struct D2Unit* pUnit, int nOwnerType, int nOwnerId);
//D2Common.0x6FDBFFE0 (#10415)
D2COMMON_DLL_DECL void UNITS_StoreOwner(struct D2Unit* pUnit, struct D2Unit* pOwner);
//D2Common.0x6FDC0060 (#10417)
D2COMMON_DLL_DECL void UNITS_StoreLastAttacker(struct D2Unit* pUnit, struct D2Unit* pKiller);
//D2Common.0x6FDC00E0 (#10418)
D2COMMON_DLL_DECL int UNITS_GetDirectionToCoords(struct D2Unit* pUnit, int nNewX, int nNewY);
//D2Common.0x6FDC0160 (#10437)
D2COMMON_DLL_DECL void UNITS_SetOverlay(struct D2Unit* pUnit, int nOverlay, int nUnused);
//D2Common.0x6FDC01F0 (#10367)
D2COMMON_DLL_DECL int UNITS_GetBeltType(struct D2Unit* pUnit);
//D2Common.0x6FDC0260 (#10368)
D2COMMON_DLL_DECL int UNITS_GetCurrentLifePercentage(struct D2Unit* pUnit);
//D2Common.0x6FDC02A0 (#10359)
D2COMMON_DLL_DECL BOOL UNITS_IsSoftMonster(struct D2Unit* pUnit);
//D2Common.0x6FDC0320 (#10420)
D2COMMON_DLL_DECL void UNITS_AllocPlayerData(struct D2Unit* pUnit);
//D2Common.0x6FDC03F0 (#10421)
D2COMMON_DLL_DECL void UNITS_FreePlayerData(void* pMemPool, struct D2Unit* pPlayer);
//D2Common.0x6FDC04A0 (#10422)
D2COMMON_DLL_DECL void UNITS_SetNameInPlayerData(struct D2Unit* pUnit, char* szName);
//D2Common.0x6FDC0530 (#10423)
D2COMMON_DLL_DECL char* UNITS_GetPlayerName(struct D2Unit* pUnit);
//D2Common.0x6FDC05B0 (#10424)
D2COMMON_DLL_DECL struct D2PlayerData* UNITS_GetPlayerData(struct D2Unit* pUnit);
//D2Common.0x6FDC0600 (#10425)
D2COMMON_DLL_DECL void UNITS_SetPlayerPortalFlags(struct D2Unit* pUnit, int nPortalFlags);
//D2Common.0x6FDC0660 (#10426)
D2COMMON_DLL_DECL int UNITS_GetPlayerPortalFlags(struct D2Unit* pUnit);
//D2Common.0x6FDC06C0 (#10353)
D2COMMON_DLL_DECL uint32_t UNITS_GetNameOffsetFromObject(struct D2Unit* pUnit);
//D2Common.0x6FDC0700 (#10427)
D2COMMON_DLL_DECL uint8_t UNITS_GetObjectPortalFlags(struct D2Unit* pUnit);
//D2Common.0x6FDC0760 (#10428)
D2COMMON_DLL_DECL void UNITS_SetObjectPortalFlags(struct D2Unit* pUnit, uint8_t nPortalFlag);
//D2Common.0x6FDC07C0 (#10429)
D2COMMON_DLL_DECL BOOL UNITS_CheckObjectPortalFlag(struct D2Unit* pUnit, uint8_t nFlag);
//D2Common.0x6FDC0820 (#10430)
D2COMMON_DLL_DECL int UNITS_GetOverlayHeight(struct D2Unit* pUnit);
//D2Common.0x6FDC08B0 (#10431)
D2COMMON_DLL_DECL int UNITS_GetDefense(struct D2Unit* pUnit);
//D2Common.0x6FDC0AC0 (#10432)
D2COMMON_DLL_DECL int UNITS_GetAttackRate(struct D2Unit* pAttacker);
//D2Common.0x6FDC0B60 (#10433)
D2COMMON_DLL_DECL int UNITS_GetBlockRate(struct D2Unit* pUnit, BOOL bExpansion);
//D2Common.0x6FDC0DA0 (#10434)
D2COMMON_DLL_DECL struct D2Unit* D2Common_10434(struct D2Unit* pUnit, BOOL a2);
//D2Common.0x6FDC0F70 (#10435)
D2COMMON_DLL_DECL struct D2Unit* UNITS_GetEquippedWeaponFromMonster(struct D2Unit* pMonster);
//D2Common.0x6FDC0FC0 (#10436)
D2COMMON_DLL_DECL int UNITS_GetFrameBonus(struct D2Unit* pUnit);
//D2Common.0x6FDC1120 (#10360)
D2COMMON_DLL_DECL int UNITS_GetMeleeRange(struct D2Unit* pUnit);
//D2Common.0x6FDC1230 (#10364)
D2COMMON_DLL_DECL BOOL UNITS_TestCollisionByCoordinates(struct D2Unit* pUnit, int nX, int nY, int nFlags);
//D2Common.0x6FDC13D0
BOOL UNITS_TestCollision(int nX1, int nY1, int nSize1, int nX2, int nY2, int nSize2, struct D2ActiveRoom* pRoom, int nCollisionMask);
//D2Common.0x6FDC14C0 (#10362)
D2COMMON_DLL_DECL BOOL UNITS_TestCollisionWithUnit(struct D2Unit* pUnit1, struct D2Unit* pUnit2, int nCollisionMask);
//D2Common.0x6FDC1760
void UNITS_ToggleUnitFlag(struct D2Unit* pUnit, int nFlag, BOOL bSet);
//D2Common.0x6FDC1790 (#10363)
D2COMMON_DLL_DECL BOOL UNITS_TestCollisionBetweenInteractingUnits(struct D2Unit* pUnit1, struct D2Unit* pUnit2, int nCollisionMask);
//D2Common.0x6FDC1A70 (#10361)
D2COMMON_DLL_DECL BOOL UNITS_IsInMeleeRange(struct D2Unit* pUnit1, struct D2Unit* pUnit2, int nRangeBonus);
//D2Common.0x6FDC1B40 (#10318)
D2COMMON_DLL_DECL BOOL UNITS_IsInMovingMode(struct D2Unit* pUnit);
//D2Common.0x6FDC1C30 (#10319)
D2COMMON_DLL_DECL BOOL UNITS_IsInMovingModeEx(struct D2Unit* pUnit);
//D2Common.0x6FDC1C50 (#10365)
D2COMMON_DLL_DECL int UNITS_GetHitClass(struct D2Unit* pUnit);
//D2Common.0x6FDC1CE0 (#10366)
D2COMMON_DLL_DECL int UNITS_GetWeaponClass(struct D2Unit* pUnit);
//D2Common.0x6FDC1D00 (#10438)
D2COMMON_DLL_DECL unsigned int UNITS_GetHealingCost(struct D2Unit* pUnit);
//D2Common.0x6FDC1D90 (#10439)
D2COMMON_DLL_DECL unsigned int UNITS_GetInventoryGoldLimit(struct D2Unit* pUnit);
//D2Common.0x6FDC1DB0 (#10440)
D2COMMON_DLL_DECL void UNITS_MergeDualWieldWeaponStatLists(struct D2Unit* pUnit, int a2);
//D2Common.0x6FDC1EE0
struct D2MonStats2Txt* UNITS_GetMonStats2TxtRecord(int nRecordId);
//D2Common.0x6FDC1F10 (#10442)
D2COMMON_DLL_DECL uint8_t UNITS_GetItemComponentId(struct D2Unit* pUnit, struct D2Unit* pItem);
//D2Common.0x6FDC1FE0
struct D2MonStats2Txt* UNITS_GetMonStats2TxtRecordFromMonsterId(int nMonsterId);
//D2Common.0x6FDC2030 (#10443)
D2COMMON_DLL_DECL void UNITS_InitRightSkill(struct D2Unit* pUnit);
//D2Common.0x6FDC20A0 (#10444)
D2COMMON_DLL_DECL void UNITS_InitLeftSkill(struct D2Unit* pUnit);
//D2Common.0x6FDC2110 (#10445)
D2COMMON_DLL_DECL void UNITS_InitSwitchRightSkill(struct D2Unit* pUnit);
//D2Common.0x6FDC2180 (#10446)
D2COMMON_DLL_DECL void UNITS_InitSwitchLeftSkill(struct D2Unit* pUnit);
//D2Common.0x6FDC21F0 (#10447)
D2COMMON_DLL_DECL void UNITS_GetRightSkillData(struct D2Unit* pUnit, int* pRightSkillId, int* pRightSkillFlags);
//D2Common.0x6FDC2250 (#10448)
D2COMMON_DLL_DECL void UNITS_GetLeftSkillData(struct D2Unit* pUnit, int* pLeftSkillId, int* pLeftSkillFlags);
//D2Common.0x6FDC22B0 (#10449)
D2COMMON_DLL_DECL void UNITS_GetSwitchRightSkillDataResetRightSkill(struct D2Unit* pUnit, int* pSwitchRightSkillId, int* pSwitchRightSkillFlags);
//D2Common.0x6FDC2330 (#10450)
D2COMMON_DLL_DECL void UNITS_GetSwitchLeftSkillDataResetLeftSkill(struct D2Unit* pUnit, int* pSwitchLeftSkillId, int* pSwitchLeftSkillFlags);
//D2Common.0x6FDC23B0 (#10451)
D2COMMON_DLL_DECL void UNITS_GetSwitchLeftSkillData(struct D2Unit* pUnit, int* pSwitchLeftSkillId, int* pSwitchLeftSkillFlags);
//D2Common.0x6FDC2420 (#10452)
D2COMMON_DLL_DECL void UNITS_GetSwitchRightSkillData(struct D2Unit* pUnit, int* pSwitchRightSkillId, int* pSwitchRightSkillFlags);
//D2Common.0x6FDC2490 (#10453)
D2COMMON_DLL_DECL void UNITS_SetSwitchLeftSkill(struct D2Unit* pUnit, int nSwitchLeftSkillId, int nSwitchLeftSkillFlags);
//D2Common.0x6FDC24E0 (#10454)
D2COMMON_DLL_DECL void UNITS_SetSwitchRightSkill(struct D2Unit* pUnit, int nSwitchRightSkillId, int nSwitchRightSkillFlags);
//D2Common.0x6FDC2530 (#10455)
D2COMMON_DLL_DECL void UNITS_SetWeaponGUID(struct D2Unit* pUnit, struct D2Unit* pWeapon);
//D2Common.0x6FDC25B0 (#10456)
D2COMMON_DLL_DECL D2UnitGUID UNITS_GetWeaponGUID(struct D2Unit* pUnit);
//D2Common.0x6FDC2630 (#10339)
D2COMMON_DLL_DECL unsigned int UNITS_GetStashGoldLimit(struct D2Unit* pUnit);
//D2Common.0x6FDC2680 (#10317)
D2COMMON_DLL_DECL BOOL UNITS_CanSwitchAI(int nMonsterId);
//D2Common.0x6FDC2720 (#10458)
D2COMMON_DLL_DECL void UNITS_SetTimerArg(struct D2Unit* pUnit, struct D2TimerArg* pTimerArg);
//D2Common.0x6FDC2750 (#10459)
D2COMMON_DLL_DECL struct D2TimerArg* UNITS_GetTimerArg(struct D2Unit* pUnit);
//D2Common.0x6FDC2780 (#10460)
D2COMMON_DLL_DECL void UNITS_AllocStaticPath(struct D2Unit* pUnit);
//D2Common.0x6FDC27C0 (#10461)
D2COMMON_DLL_DECL void UNITS_FreeStaticPath(struct D2Unit* pUnit);
//D2Common.0x6FDC27F0 (#10462)
D2COMMON_DLL_DECL BOOL UNITS_CanDualWield(struct D2Unit* pUnit);
//D2Common.0x6FDC2860 (#11238)
D2COMMON_DLL_DECL BOOL UNITS_IsCorpseUseable(struct D2Unit* pUnit);
//D2Common.0x6FDC2910 (#11307)
D2COMMON_DLL_DECL BOOL UNITS_IsObjectInInteractRange(struct D2Unit* pUnit, struct D2Unit* pObject);
//D2Common.0x6FDC2C80
struct D2CharStatsTxt* UNITS_GetCharStatsTxtRecord(int nRecordId);
//1.10f: D2Common.0x6FDC2CB0 (#10399)
//1.13c: D2Common.0x6FDCFCD0 (#10407)
D2COMMON_DLL_DECL int D2Common_10399(struct D2Unit* pUnit1, struct D2Unit* pUnit2);
//D2Common.0x6FDC2E40 (#10397)
D2COMMON_DLL_DECL int UNITS_GetDistanceToOtherUnit(struct D2Unit* pUnit1, struct D2Unit* pUnit2);
//D2Common.0x6FDC2F50 (#10398)
D2COMMON_DLL_DECL unsigned int UNITS_GetDistanceToCoordinates(struct D2Unit* pUnit, int nX, int nY);
//D2Common.0x6FDC2FF0 (#10400)
D2COMMON_DLL_DECL BOOL UNITS_IsInRange(struct D2Unit* pUnit, struct D2Coord* pCoord, int nDistance);
//D2Common.0x6FDC3090 (#10406)
D2COMMON_DLL_DECL struct D2Unit* D2Common_10406(struct D2Unit* pUnit, int(* pCallback)(struct D2Unit*, void*), void* a3);
//D2Common.0x6FDC33C0 (#10407)
D2COMMON_DLL_DECL struct D2Unit* D2Common_10407(struct D2ActiveRoom* pRoom, int nX, int nY, int(* pCallback)(struct D2Unit*, void*), void* a5, int a6);
//D2Common.0x6FDC3680 (#10419)
D2COMMON_DLL_DECL void UNITS_SetInteractData(struct D2Unit* pUnit, int nSkillId, int nUnitType, D2UnitGUID nUnitGUID);
