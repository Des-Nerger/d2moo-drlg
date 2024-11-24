#pragma once 

#include <D2BitManip.h>

#pragma pack(1)

struct D2ArenaUnit; // From D2Game
struct D2Client; // From D2Game
struct D2WaypointData;

enum D2C_PlayerModes
{
	PLRMODE_DEATH,		// DT
	PLRMODE_NEUTRAL,	// NU
	PLRMODE_WALK,		// WL
	PLRMODE_RUN,		// RN
	PLRMODE_GETHIT,		// GH
	PLRMODE_TOWNNEUTRAL,// TN
	PLRMODE_TOWNWALK,	// TW
	PLRMODE_ATTACK1,	// A1
	PLRMODE_ATTACK2,	// A2
	PLRMODE_BLOCK,		// BL
	PLRMODE_CAST,		// SC
	PLRMODE_THROW,		// TH
	PLRMODE_KICK,		// KK
	PLRMODE_SPECIAL1,	// S1
	PLRMODE_SPECIAL2,	// S2
	PLRMODE_SPECIAL3,	// S3
	PLRMODE_SPECIAL4,	// S4
	PLRMODE_DEAD,		// DD
	PLRMODE_SEQUENCE,	// SQ
	PLRMODE_KNOCKBACK,	// KB
	NUMBER_OF_PLRMODES
};

enum D2C_PlayerClasses
{
	PCLASS_AMAZON,
	PCLASS_SORCERESS,
	PCLASS_NECROMANCER,
	PCLASS_PALADIN,
	PCLASS_BARBARIAN,
	PCLASS_DRUID,
	PCLASS_ASSASSIN,
	PCLASS_EVILFORCE,
	PCLASS_INVALID = 7,
	NUMBER_OF_PLAYERCLASSES = 7,
};

struct D2PlayerCountBonus
{
	int32_t nHp;								//0x00
	int32_t nExperience;						//0x04
	int32_t nMonsterSkillBonus;					//0x08
	int32_t nDifficulty;						//0x0C
	int32_t nPlayerCount;						//0x10
};

struct D2ItemTrade
{
	int32_t nItemGUID1;							//0x00
	int32_t nItemGUID2;							//0x04
	struct D2ItemTrade* pNext;						//0x08
};

struct D2PlayerTrade
{
	int32_t nSaveLength;						//0x00
	uint8_t* pSaveData;							//0x04
	struct D2ItemTrade* pItemTrade;				//0x08
	int32_t nGoldInTrade;						//0x0C
	int32_t nGoldInTradeOtherPlayer;			//0x10
	int32_t nNextUpdateTick;					//0x14
};

struct D2PlrIntro
{
	struct D2BitBuffer* pQuestIntroFlags;
	struct D2BitBuffer* pNpcIntroFlags;
};

struct D2PetInfo
{
	uint32_t nSeed;								//0x00
	uint16_t wName;							//0x04
	int16_t unk0x06;							//0x06
	int32_t nHirelingId;							//0x08
};

struct D2PetData
{
	uint32_t nFlags;							//0x00
	int32_t nUnitGUID;							//0x04
	struct D2PetInfo petInfo;						//0x08
	struct D2PetData* pNext;						//0x14
};

struct D2PetList
{
	struct D2PetData* pPetData;					//0x00
	int32_t nCurrent;							//0x04
	int32_t nMax;								//0x08
};

struct D2PlayerPet
{
	struct D2PetList* pPetList;					//0x00
};

struct D2PetArg
{
	int32_t nPetGUID;							//0x00
	int32_t nUnitGUID;							//0x04
	int16_t nPetClass;							//0x08
	int16_t unk0x0A;							//0x0A
	int32_t nPetType;							//0x0C
	uint32_t nSeed;								//0x10
	int16_t wName;								//0x14
	int16_t unk0x16;							//0x16
	int32_t unk0x18;							//0x18
};

struct D2PlayerList
{
	int32_t nUnitGUID;							//0x00
	uint32_t dwFlags;							//0x04
	int32_t field_8;							//0x08
	int32_t field_C;							//0x0C
	struct D2PlayerList* pNext;					//0x10
};

struct D2UnkPlayerData
{
	int32_t nUnitGUID;							//0x00
	int32_t unk0x04;							//0x04
	int32_t unk0x08;							//0x08
	uint8_t unk0x0C;							//0x0C
	uint8_t unk0x0D[3];							//0x0D
	struct D2UnkPlayerData* pNext;					//0x10
};

struct D2PlayerData
{
	char szName[16];							//0x00
	struct D2BitBuffer* pQuestData[3];				//0x10
	struct D2WaypointData* pWaypointData[3];		//0x1C
	uint32_t unk0x28;							//0x28
	int32_t nPortalFlags;						//0x2C
	int32_t unk0x30;							//0x30
	struct D2ArenaUnit* pArenaUnit;				//0x34
	struct D2PlayerList* pPlayerList;				//0x38
	uint32_t unk0x3C[2];						//0x3C
	struct D2PlayerPet* pPlayerPets;				//0x44
	uint32_t dwUniqueId;						//0x48
	uint32_t bBusy;								//0x4C
	uint32_t dwTradeState;						//0x50
	uint32_t unk0x54;							//0x54
	uint32_t dwAcceptTradeTick;					//0x58
	struct D2PlayerTrade* pTrade;					//0x5C
	struct D2PlrIntro* pPlayerIntro[3];			//0x60
	uint32_t dwBoughtItemId;					//0x6C
	int32_t nRightSkillId;						//0x70
	int32_t nLeftSkillId;						//0x74
	int32_t nRightSkillFlags;					//0x78
	int32_t nLeftSkillFlags;					//0x7C
	int32_t nSwitchRightSkillId;				//0x80
	int32_t nSwitchLeftSkillId;					//0x84
	int32_t nSwitchRightSkillFlags;				//0x88
	int32_t nSwitchLeftSkillFlags;				//0x8C
	D2UnitGUID nWeaponGUID;						//0x90
	uint32_t unk0x94;							//0x94
	struct D2UnkPlayerData* unk0x98;				//0x98
	struct D2Client* pClient;						//0x9C
	uint8_t unk0xA0;							//0xA0
	uint8_t unk0xA1[3];							//0xA1
	uint32_t unk0xA4;							//0xA4
	uint32_t unk0xA8[46];						//0xA8
	uint32_t dwHostileDelay;					//0x160
	uint32_t unk0x164;							//0x164
	uint32_t dwGameFrame;						//0x168
};


#pragma pack()
