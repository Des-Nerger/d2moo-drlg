#pragma once

#include "CommonDefinitions.h"


struct D2Unit;
struct D2InventoryGridInfo;

#pragma pack(1)

struct D2InvRect
{
	int32_t nLeft;		//0x00
	int32_t nRight;		//0x04
	int32_t nTop;		//0x08
	int32_t nBottom;	//0x0C
};

enum D2C_PlayerBodyLocs
{
	BODYLOC_NONE,		//Not Equipped
	BODYLOC_HEAD,		//Helm
	BODYLOC_NECK,		//Amulet
	BODYLOC_TORSO,		//Body Armor
	BODYLOC_RARM,		//Right-Hand
	BODYLOC_LARM,		//Left-Hand
	BODYLOC_RRIN,		//Right Ring
	BODYLOC_LRIN,		//Left Ring
	BODYLOC_BELT,		//Belt
	BODYLOC_FEET,		//Boots
	BODYLOC_GLOVES,		//Gloves
	BODYLOC_SWRARM,		//Right-Hand on Switch
	BODYLOC_SWLARM,		//Left-Hand on Switch
	NUM_BODYLOC
};

#define D2C_InventoryHeader 0x1020304

enum D2C_ItemInvPage
{
	INVPAGE_INVENTORY = 0,
	INVPAGE_EQUIP = 1,
	INVPAGE_TRADE = 2,
	INVPAGE_CUBE = 3,
	INVPAGE_STASH = 4,
	INVPAGE_BELT = 5,
	INVPAGE_NULL = 255
};

enum D2C_InventoryRecords
{
	// 640x420
	INVENTORYRECORD_AMAZON,
	INVENTORYRECORD_SORCERESS,
	INVENTORYRECORD_NECROMANCER,
	INVENTORYRECORD_PALADIN,
	INVENTORYRECORD_BARBARIAN,
	INVENTORYRECORD_MONSTER,
	INVENTORYRECORD_TRADE_PAGE_1,
	INVENTORYRECORD_TRADE_PAGE_2,
	INVENTORYRECORD_BANK_PAGE_1,
	INVENTORYRECORD_TRANSMOGRIFY_BOX_PAGE_1,
	INVENTORYRECORD_GUILD_VAULT_PAGE_1,
	INVENTORYRECORD_TROPHY_CASE_PAGE_1,
	INVENTORYRECORD_BIG_BANK_PAGE_1,
	INVENTORYRECORD_HIRELING,
	INVENTORYRECORD_DRUID,
	INVENTORYRECORD_ASSASSIN,
	NUM_INVENTORY_PAGE_STATS,

	// 800x600
	INVENTORYRECORD_AMAZON2 = NUM_INVENTORY_PAGE_STATS,
	INVENTORYRECORD_SORCERESS2,
	INVENTORYRECORD_NECROMANCER2,
	INVENTORYRECORD_PALADIN2,
	INVENTORYRECORD_BARBARIAN2,
	INVENTORYRECORD_MONSTER2,
	INVENTORYRECORD_TRADE_PAGE_1_2,
	INVENTORYRECORD_TRADE_PAGE_2_2,
	INVENTORYRECORD_BANK_PAGE2,
	INVENTORYRECORD_TRANSMOGRIFY_BOX2,
	INVENTORYRECORD_GUILD_VAULT_PAGE2,
	INVENTORYRECORD_TROPHY_CASE_PAGE2,
	INVENTORYRECORD_BIG_BANK_PAGE2,
	INVENTORYRECORD_HIRELING2,
	INVENTORYRECORD_DRUID2,
	INVENTORYRECORD_ASSASSIN2
};

enum D2C_NodePages
{
	NODEPAGE_STORAGE = 1,
	NODEPAGE_BELTSLOTS = 2,
	NODEPAGE_EQUIP = 3
};

enum D2C_InventoryGrids
{
	INVGRID_BODYLOC,
	INVGRID_BELT,
	INVGRID_INVENTORY,
};

enum D2TradeStates
{
	TRADESTATE_OTHERNOROOM,
	TRADESTATE_SELFNOROOM,
};

struct D2InventoryGrid
{
	struct D2Unit* pItem;						//0x00
	struct D2Unit* pLastItem;					//0x04
	uint8_t nGridWidth;						//0x08
	uint8_t nGridHeight;					//0x09
	uint16_t pad0x0A;						//0x0A
	struct D2Unit** ppItems;					//0x0C
};

struct D2Corpse
{
	uint32_t unk0x00;						//0x00
	uint32_t dwUnitId;						//0x04
	uint32_t unk0x08;						//0x08
	struct D2Corpse* pNextCorpse;				//0x0C
};

struct D2InventoryNode
{
	int32_t nItemId;						//0x00
	struct D2InventoryNode* pNext;				//0x04
};

struct D2Inventory
{
	uint32_t dwSignature;					//0x00
	void* pMemPool;							//0x04
	struct D2Unit* pOwner;						//0x08
	struct D2Unit* pFirstItem;					//0x0C
	struct D2Unit* pLastItem;					//0x10
	struct D2InventoryGrid* pGrids;			//0x14
	int32_t nGridCount;						//0x18
	D2UnitGUID dwLeftItemGUID;				//0x1C
	struct D2Unit* pCursorItem;				//0x20
	D2UnitGUID dwOwnerGuid;					//0x24
	uint32_t dwItemCount;					//0x28
	struct D2InventoryNode* pFirstNode;		//0x2C
	struct D2InventoryNode* pLastNode;			//0x30
	struct D2Corpse* pFirstCorpse;				//0x34
	struct D2Corpse* pLastCorpse;				//0x38
	int32_t nCorpseCount;					//0x3C
};

struct D2ItemExtraData
{
	struct D2Inventory* pParentInv;			//0x00
	struct D2Unit* pPreviousItem;				//0x04
	struct D2Unit* pNextItem;					//0x08
	char nNodePos;							//0x0C
	char nNodePosOther;						//0x0D
	uint16_t unk0x0E;						//0x0E
	struct D2Unit* unk0x10;					//0x10
	struct D2Unit* unk0x14;					//0x14
};
#pragma pack()

// Helper functions
// Check if the header signature is correct. Assumes non null ptr.
static inline bool INVENTORY_CheckSignature(struct D2Inventory* pInventory) { return pInventory->dwSignature == D2C_InventoryHeader; }
// Check if ptr is non null and if header signature is correct.
static inline struct D2Inventory* INVENTORY_GetPtrIfValid(struct D2Inventory* pInventory) { return (pInventory && INVENTORY_CheckSignature(pInventory)) ? pInventory : nullptr; }
// Return true if matches a valid body location
static inline bool INVENTORY_ValidateBodyLoc(int nBodyLoc) { return nBodyLoc >= 0 && nBodyLoc < NUM_BODYLOC; }

//D2Common.0x6FD8E210
BOOL INVENTORY_RemoveItem(struct D2Unit* pItem);
//D2Common.0x6FD8E4A0
struct D2ItemExtraData* INVENTORY_GetItemExtraDataFromItem(struct D2Unit* pItem);
//D2Common.0x6FD8E4C0 (#10240)
D2COMMON_DLL_DECL struct D2Inventory* INVENTORY_AllocInventory(void* pMemPool, struct D2Unit* pOwner);
//D2Common.0x6FD8E520 (#10241)
D2COMMON_DLL_DECL void INVENTORY_FreeInventory(struct D2Inventory* pInventory);
//D2Common.0x6FD8E620 (#10244)
D2COMMON_DLL_DECL BOOL INVENTORY_CompareWithItemsParentInventory(struct D2Inventory* pInventory, struct D2Unit* pItem);
//D2Common.0x6FD8E660 (#10243)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_RemoveItemFromInventory(struct D2Inventory* pInventory, struct D2Unit* pItem);
//D2Common.0x6FD8E6A0 (#10242)
D2COMMON_DLL_DECL BOOL INVENTORY_PlaceItemInSocket(struct D2Inventory* pInventory, struct D2Unit* pItem, int nUnused);
//D2Common.0x6FD8E7A0 (#10277)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_GetFirstItem(struct D2Inventory* pInventory);
//D2Common.0x6FD8E7C0 (#10278)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_GetLastItem(struct D2Inventory* pInventory);
//D2Common.0x6FD8E7E0 (#10245)
D2COMMON_DLL_DECL BOOL INVENTORY_GetFreePosition(struct D2Inventory* pInventory, struct D2Unit* pItem, int nInventoryRecordId, int* pFreeX, int* pFreeY, uint8_t nPage);
//D2Common.0x6FD8EAF0
struct D2InventoryGrid* INVENTORY_GetGrid(struct D2Inventory* pInventory, int nInventoryGrid, struct D2InventoryGridInfo* pInventoryGridInfo);
//D2Common.0x6FD8EC70
BOOL INVENTORY_CanItemBePlacedAtPos(struct D2InventoryGrid* pInventoryGrid, int nX, int nY, uint8_t nItemWidth, uint8_t nItemHeight);
//D2Common.0x6FD8ECF0
BOOL INVENTORY_FindFreePositionBottomRightToTopLeftWithWeight(struct D2InventoryGrid* pInventoryGrid, int* pFreeX, int* pFreeY, uint8_t nItemWidth, uint8_t nItemHeight);
//D2Common.0x6FD8EE20
uint8_t INVENTORY_GetPlacementWeight(struct D2InventoryGrid* pInventoryGrid, int nXPos, int nYPos, uint8_t nItemWidth, uint8_t nItemHeight);
//D2Common.0x6FD8EFB0
BOOL INVENTORY_FindFreePositionTopLeftToBottomRightWithWeight(struct D2InventoryGrid* pInventoryGrid, int* pFreeX, int* pFreeY, uint8_t nItemWidth, uint8_t nItemHeight);
//D2Common.0x6FD8F0E0
BOOL INVENTORY_FindFreePositionTopLeftToBottomRight(struct D2InventoryGrid* pInventoryGrid, int* pFreeX, int* pFreeY, uint8_t nItemWidth, uint8_t nItemHeight);
//D2Common.0x6FD8F1E0 (#10246)
D2COMMON_DLL_DECL BOOL INVENTORY_PlaceItemAtFreePosition(struct D2Inventory* pInventory, struct D2Unit* pItem, int nInventoryRecordId, BOOL bUnused, uint8_t nPage, const char* szFile, int nLine);
//D2Common.0x6FD8F250
BOOL INVENTORY_PlaceItemInGrid(struct D2Inventory* pInventory, struct D2Unit* pItem, int nXPos, int nYPos, int nInventoryGrid, int nInventoryRecordId, BOOL bUnused);
//D2Common.0x6FD8F600 (#10247)
D2COMMON_DLL_DECL BOOL INVENTORY_CanItemBePlaced(struct D2Inventory* pInventory, struct D2Unit* pItem, int nXPos, int nYPos, int nInventoryRecordId, struct D2Unit** ppExchangeItem, unsigned int* pHoveredItems, uint8_t nPage);
//D2Common.0x6FD8F780 (#10248)
D2COMMON_DLL_DECL BOOL INVENTORY_CanItemsBeExchanged(struct D2Inventory* pInventory, struct D2Unit* pItem, int nXPos, int nYPos, int nInventoryRecordId, struct D2Unit** ppExchangeItem, uint8_t nPage, BOOL bCheckIfCube);
//D2Common.0x6FD8F930 (#10249)
D2COMMON_DLL_DECL BOOL INVENTORY_PlaceItemAtInventoryPage(struct D2Inventory* pInventory, struct D2Unit* pItem, int nXPos, int nYPos, int nInventoryRecordId, BOOL bUnused, uint8_t nPage);
//D2Common.0x6FD8F970 (#10250)
D2COMMON_DLL_DECL void INVENTORY_Return(const char* szFile, int nLine, struct D2Inventory* pInventory, int nX, int nY, int nInventoryRecordId, BOOL bClient, uint8_t nPage);
//D2Common.0x6FD8F980 (#10252)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_GetItemFromInventoryPage(struct D2Inventory* pInventory, int nGridX, int nGridY, int* pX, int* pY, int nInventoryRecordId, uint8_t nPage);
//D2Common.0x6FD8FAB0 (#10253)
D2COMMON_DLL_DECL BOOL INVENTORY_PlaceItemInBodyLoc(struct D2Inventory* pInventory, struct D2Unit* pItem, int nBodyLoc);
//D2Common.0x6FD8FAE0 (#10257)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_GetItemFromBodyLoc(struct D2Inventory* pInventory, int nBodyLoc);
//D2Common.0x6FD8FB20 (#10255)
D2COMMON_DLL_DECL void INVENTORY_GetSecondWieldingWeapon(struct D2Unit* pPlayer, struct D2Inventory* pInventory, struct D2Unit** ppItem, int nBodyLoc);
//D2Common.0x6FD8FBB0 (#10256)
D2COMMON_DLL_DECL BOOL INVENTORY_CheckEquipmentForWeaponByClass(struct D2Inventory* pInventory, int nWeaponClass);
//D2Common.0x6FD8FC60 (#10258)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_GetLeftHandWeapon(struct D2Inventory* pInventory);
//D2Common.0x6FD8FD10 (#11301)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_GetSecondaryWeapon(struct D2Inventory* pInventory);
//D2Common.0x6FD8FDD0 (#10259)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_GetCompositItem(struct D2Inventory* pInventory, int nComponent);
//D2Common.0x6FD8FE80 (#10260)
D2COMMON_DLL_DECL int INVENTORY_GetBodyLocFromEquippedItem(struct D2Inventory* pInventory, struct D2Unit* pItem);
//D2Common.0x6FD8FED0 (#11278)
D2COMMON_DLL_DECL int INVENTORY_GetItemsXPosition(struct D2Inventory* pInventory, struct D2Unit* pItem);
//D2Common.0x6FD8FF20 (#10261)
D2COMMON_DLL_DECL void INVENTORY_SetCursorItem(struct D2Inventory* pInventory, struct D2Unit* pItem);
//D2Common.0x6FD8FF80 (#10262)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_GetCursorItem(struct D2Inventory* pInventory);
//D2Common.0x6FD8FFA0 (#10263)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_FindBackPackItemForStack(struct D2Inventory* pInventory, struct D2Unit* pStackable, struct D2Unit* pCheckItem);
//D2Common.0x6FD90080 (#10264)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_FindEquippedItemForStack(struct D2Inventory* pInventory, struct D2Unit* pStackable, struct D2Unit* pCheckItem);
//D2Common.0x6FD90130 (#10265)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_FindFillableBook(struct D2Inventory* pInventory, struct D2Unit* pScrolls, struct D2Unit* pCheckItem);
//D2Common.0x6FD90230 (#10266)
D2COMMON_DLL_DECL BOOL INVENTORY_PlaceItemInBeltSlot(struct D2Inventory* pInventory, struct D2Unit* pItem, int nSlot);
//D2Common.0x6FD902B0 (#10268)
D2COMMON_DLL_DECL BOOL INVENTORY_HasSimilarPotionInBelt(struct D2Inventory* pInventory, struct D2Unit* pPotion);
//D2Common.0x6FD90340 (#10269)
D2COMMON_DLL_DECL BOOL INVENTORY_GetFreeBeltSlot(struct D2Inventory* pInventory, struct D2Unit* pItem, int* pFreeSlotId);
//D2Common.0x6FD904F0 (#10270)
D2COMMON_DLL_DECL BOOL INVENTORY_PlaceItemInFreeBeltSlot(struct D2Inventory* pInventory, struct D2Unit* pItem);
//D2Common.0x6FD90550 (#10271)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_GetItemFromBeltSlot(struct D2Inventory* pInventory, int nSlotId);
//D2Common.0x6FD90590 (#10272)
D2COMMON_DLL_DECL BOOL INVENTORY_GetUseableItemFromBeltSlot(struct D2Inventory* pInventory, struct D2Unit* pItem, int nSlotId, struct D2Unit** ppItem);
//D2Common.0x6FD90690 (#10273)
D2COMMON_DLL_DECL BOOL INVENTORY_GetEquippedShield(struct D2Inventory* pInventory, struct D2Unit** ppItem);
//D2Common.0x6FD90760 (#10274)
D2COMMON_DLL_DECL BOOL INVENTORY_GetEquippedWeapon(struct D2Inventory* pInventory, struct D2Unit** ppItem, int* pBodyLoc, BOOL* pIsLeftHandItem);
//D2Common.0x6FD90850 (#10275)
D2COMMON_DLL_DECL BOOL INVENTORY_HasBodyArmorEquipped(struct D2Inventory* pInventory);
//D2Common.0x6FD908A0 (#10276)
D2COMMON_DLL_DECL BOOL INVENTORY_IsItemBodyLocFree(struct D2Inventory* pInventory, struct D2Unit* pItem, int nBodyLoc, int nInventoryRecordId);
//D2Common.0x6FD90910 (#10279)
D2COMMON_DLL_DECL void INVENTORY_RemoveInventoryItems(struct D2Inventory* pInventory);
//D2Common.0x6FD90940 (#10280)
D2COMMON_DLL_DECL struct D2InventoryNode* INVENTORY_GetTradeInventory(struct D2Inventory* pInventory);
//D2Common.0x6FD90960 (#10281)
D2COMMON_DLL_DECL void INVENTORY_FreeTradeInventory(struct D2Inventory* pInventory);
//D2Common.0x6FD909B0 (#10282)
D2COMMON_DLL_DECL BOOL INVENTORY_CheckForItemInTradeInventory(struct D2Inventory* pInventory, int nItemId);
//D2Common.0x6FD909F0 (#10283)
D2COMMON_DLL_DECL void INVENTORY_AddItemToTradeInventory(struct D2Inventory* pInventory, struct D2Unit* pItem);
//D2Common.0x6FD90AB0 (#10316)
D2COMMON_DLL_DECL int D2Common_10316(struct D2Corpse* pCorpse);
//D2Common.0x6FD90AC0 (#10284)
D2COMMON_DLL_DECL int INVENTORY_GetItemCount(struct D2Inventory* pInventory);
//D2Common.0x6FD90AE0 (#10285)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_GetBackPackItemByType(struct D2Inventory* pInventory, int nItemType, struct D2Unit* pCheckItem);
//D2Common.0x6FD90BC0 (#10286)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_GetEquippedItemByType(struct D2Inventory* pInventory, int nItemType, struct D2Unit* pCheckItem);
//D2Common.0x6FD90C80 (#10287)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_GetEquippedItemByCode(struct D2Inventory* pInventory, int nItemCode, struct D2Unit* pCheckItem);
//D2Common.0x6FD90D50 (#11306)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_GetBackPackItemByCode(struct D2Inventory* pInventory, int nItemCode, struct D2Unit* pCheckItem);
//D2Common.0x6FD90E20 (#10288)
D2COMMON_DLL_DECL int INVENTORY_GetSetItemEquipCountByFileIndex(struct D2Inventory* pInventory, int nItemFileIndex);
//D2Common.0x6FD90ED0 (#10289)
D2COMMON_DLL_DECL void INVENTORY_UpdateWeaponGUIDOnInsert(struct D2Inventory* pInventory, struct D2Unit* pItem);
//D2Common.0x6FD90F80 (#10290)
D2COMMON_DLL_DECL void INVENTORY_UpdateWeaponGUIDOnRemoval(struct D2Inventory* pInventory, struct D2Unit* pItem);
//D2Common.0x6FD91050 (#10291)
D2COMMON_DLL_DECL int INVENTORY_GetWieldType(struct D2Unit* pPlayer, struct D2Inventory* pInventory);
//D2Common.0x6FD91140 (#10292)
D2COMMON_DLL_DECL void INVENTORY_SetOwnerId(struct D2Inventory* pInventory, D2UnitGUID nOwnerGuid);
//D2Common.0x6FD91160 (#10293)
D2COMMON_DLL_DECL int INVENTORY_GetOwnerId(struct D2Inventory* pInventory);
//D2Common.0x6FD91190 (#10294)
D2COMMON_DLL_DECL void INVENTORY_CreateCorpseForPlayer(struct D2Inventory* pInventory, int nUnitId, int a3, int a4);
//D2Common.0x6FD91210 (#10295)
D2COMMON_DLL_DECL BOOL INVENTORY_FreeCorpse(struct D2Inventory* pInventory, int nUnitId, int a3);
//D2Common.0x6FD91290 (#10296)
D2COMMON_DLL_DECL struct D2Corpse* INVENTORY_GetFirstCorpse(struct D2Inventory* pInventory);
//D2Common.0x6FD912B0 (#10297)
D2COMMON_DLL_DECL int INVENTORY_GetCorpseCount(struct D2Inventory* pInventory);
//D2Common.0x6FD912D0 (#10313)
D2COMMON_DLL_DECL struct D2Corpse* INVENTORY_GetNextCorpse(struct D2Corpse* pCorpse);
//D2Common.0x6FDAFEA0 (#10314)
D2COMMON_DLL_DECL D2UnitGUID INVENTORY_GetUnitGUIDFromCorpse(struct D2Corpse* pCorpse);
//D2Common.0x6FDB18D0 (#10315)
D2COMMON_DLL_DECL int D2Common_10315(struct D2Corpse* pCorpse);
//D2Common.0x6FD912F0 (#10298)
D2COMMON_DLL_DECL void INVENTORY_GetItemSaveGfxInfo(struct D2Unit* pPlayer, uint8_t* pComponents, uint8_t* pColor);
//D2Common.0x6FD915C0
void INVENTORY_InitializeComponentArray();
//D2Common.0x6FD917B0
void sub_6FD917B0(struct D2Unit* pUnit, uint8_t* a2, uint8_t* pColor, struct D2Unit* pItem);
//D2Common.0x6FD91B60 (#10299)
D2COMMON_DLL_DECL int D2Common_10299(struct D2Unit* pUnit, int nBodyLoc, struct D2Unit* pItem, BOOL bDontCheckReqs);
//D2Common.0x6FD91D50
int sub_6FD91D50(struct D2Unit* pPlayer, int a2, int nBodyLoc, struct D2Unit* a3, struct D2Unit* a4, struct D2Unit* pItem, int nUnused);
//D2Common.0x6FD91E80
BOOL sub_6FD91E80(struct D2Unit* pUnit, struct D2Unit* pItem1, struct D2Unit* pItem2);
//D2Common.0x6FD92080 (#10304)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_GetNextItem(struct D2Unit* pItem);
//Inlined at various places
struct D2Unit* INVENTORY_GetUnknownItem(struct D2Unit* pItem);
//D2Common.0x6FD920C0 (#10305)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_UnitIsItem(struct D2Unit* pItem);
//D2Common.0x6FD920E0 (#10306)
D2COMMON_DLL_DECL D2UnitGUID INVENTORY_GetItemGUID(struct D2Unit* pItem);
//D2Common.0x6FD92100 (#10307)
D2COMMON_DLL_DECL int INVENTORY_GetItemNodePage(struct D2Unit* pItem);
//D2Common.0x6FD92140 (#10310)
D2COMMON_DLL_DECL struct D2Unit* INVENTORY_IsItemInInventory(struct D2Inventory* pInventory, struct D2Unit* pItem);
//D2Common.0x6FDAFEA0 (#10311)
D2COMMON_DLL_DECL struct D2InventoryNode* INVENTORY_GetNextNode(struct D2InventoryNode* pNode);
//D2Common.0x6FD90AB0 (#10312)
D2COMMON_DLL_DECL D2UnitGUID INVENTORY_GetItemGUIDFromNode(struct D2InventoryNode* pNode);
//D2Common.0x6FD92180 (#10300)
D2COMMON_DLL_DECL BOOL INVENTORY_RemoveAllItems(struct D2Inventory* pInventory);
//D2Common.0x6FD921D0 (#10302)
D2COMMON_DLL_DECL BOOL INVENTORY_CanItemsBeTraded(void* pMemPool, struct D2Unit* pPlayer1, struct D2Unit* pPlayer2, enum D2TradeStates* pTradeState);
//D2Common.0x6FD923C0
BOOL INVENTORY_CopyUnitItemsToTradeInventory(struct D2Inventory* pTradeInventory, struct D2Unit* pUnit);
//D2Common.0x6FD92490
BOOL INVENTORY_CanItemBePlacedInInventory(struct D2Unit* pPlayer, struct D2Unit* pItem, struct D2Inventory* pInventory);
//D2Common.0x6FD925E0
int UNITS_GetXPosition(struct D2Unit* pUnit);
//D2Common.0x6FD92610
int UNITS_GetYPosition(struct D2Unit* pUnit);
