#include "D2Inventory.h"

#include "D2Composit.h"
#include "D2DataTbls.h"
#include <DataTbls/MonsterIds.h>
#include "D2Dungeon.h"
#include "D2Items.h"
#include "D2Monsters.h"
#include "D2StatList.h"
#include "Units/UnitRoom.h"
#include "Units/Units.h"
#include <Path/Path.h>

struct D2InventoryComponentItemType
{
	int dwCode;
	int nItemType;
};


//D2Common.0x6FDE2310
struct D2InventoryGridInfo gBodyLocInventoryGridInfo = { 13, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
//D2Common.0x6FDE2328
struct D2InventoryGridInfo gBeltInventoryGridInfo = { 16, 1, 0, 0, 0, 0, 0, 0, 0, 0 };

//D2Common.0x6FDE2820
struct D2InventoryComponentItemType gComponentItemTypeMap[] =
{
	{ 0, ITEMTYPE_NONE_2 },
	{ ' til', ITEMTYPE_NONE_2 },
	{ ' dem', ITEMTYPE_NONE_2 },
	{ ' yvh', ITEMTYPE_NONE_2 },
	{ ' pac', ITEMTYPE_HELM },
	{ ' pks', ITEMTYPE_HELM },
	{ ' mlh', ITEMTYPE_HELM },
	{ ' lhf', ITEMTYPE_HELM },
	{ ' mhg', ITEMTYPE_HELM },
	{ ' nrc', ITEMTYPE_HELM },
	{ ' ksm', ITEMTYPE_HELM },
	{ ' epc', ITEMTYPE_ARMOR },
	{ ' klc', ITEMTYPE_ARMOR },
	{ ' bor', ITEMTYPE_ARMOR },
	{ ' iuq', ITEMTYPE_ARMOR },
	{ ' ael', ITEMTYPE_ARMOR },
	{ ' alh', ITEMTYPE_ARMOR },
	{ ' uts', ITEMTYPE_ARMOR },
	{ ' gnr', ITEMTYPE_ARMOR },
	{ ' lcs', ITEMTYPE_ARMOR },
	{ ' nhc', ITEMTYPE_ARMOR },
	{ ' srb', ITEMTYPE_ARMOR },
	{ ' lps', ITEMTYPE_ARMOR },
	{ ' tlp', ITEMTYPE_ARMOR },
	{ ' dlf', ITEMTYPE_ARMOR },
	{ ' htg', ITEMTYPE_ARMOR },
	{ ' luf', ITEMTYPE_ARMOR },
	{ ' cub', ITEMTYPE_SHIELD },
	{ ' grl', ITEMTYPE_SHIELD },
	{ ' tik', ITEMTYPE_SHIELD },
	{ ' wot', ITEMTYPE_SHIELD },
	{ ' lgl', ITEMTYPE_GLOVES },
	{ ' lgm', ITEMTYPE_GLOVES },
	{ ' lgh', ITEMTYPE_GLOVES },
	{ ' tbl', ITEMTYPE_BOOTS },
	{ ' tbm', ITEMTYPE_BOOTS },
	{ ' tbh', ITEMTYPE_BOOTS },
	{ ' lbl', ITEMTYPE_BELT },
	{ ' lbm', ITEMTYPE_BELT },
	{ ' lbh', ITEMTYPE_BELT },
	{ ' mhb', ITEMTYPE_HELM },
	{ ' hsb', ITEMTYPE_SHIELD },
	{ ' kps', ITEMTYPE_SHIELD },
	{ ' dnw', ITEMTYPE_WAND },
	{ ' nwy', ITEMTYPE_WAND },
	{ ' nwb', ITEMTYPE_WAND },
	{ ' blc', ITEMTYPE_CLUB },
	{ ' xah', ITEMTYPE_THROWING_AXE },
	{ ' dss', ITEMTYPE_SWORD },
	{ ' mcs', ITEMTYPE_SWORD },
	{ ' cam', ITEMTYPE_MACE },
	{ ' exa', ITEMTYPE_AXE },
	{ ' clf', ITEMTYPE_SWORD },
	{ ' dsl', ITEMTYPE_SWORD },
	{ ' alf', ITEMTYPE_MACE },
	{ ' mdh', ITEMTYPE_HAMMER },
	{ ' mhw', ITEMTYPE_HAMMER },
	{ ' src', ITEMTYPE_SWORD },
	{ ' slf', ITEMTYPE_SWORD },
	{ ' lpg', ITEMTYPE_MISSILE_POTION },
	{ ' spg', ITEMTYPE_MISSILE_POTION },
	{ ' lpo', ITEMTYPE_MISSILE_POTION },
	{ ' spo', ITEMTYPE_MISSILE_POTION },
	{ ' rgd', ITEMTYPE_KNIFE },
	{ ' 33d', ITEMTYPE_KNIFE },
	{ ' 33g', ITEMTYPE_KNIFE },
	{ ' rid', ITEMTYPE_KNIFE },
	{ ' vaj', ITEMTYPE_SPEAR },
	{ ' vlg', ITEMTYPE_SPEAR },
	{ ' lip', ITEMTYPE_SPEAR },
	{ ' mlc', ITEMTYPE_SWORD },
	{ ' dsg', ITEMTYPE_SWORD },
	{ ' rps', ITEMTYPE_SPEAR },
	{ ' irt', ITEMTYPE_SPEAR },
	{ ' kip', ITEMTYPE_SPEAR },
	{ ' rps', ITEMTYPE_SPEAR },
	{ ' wbs', ITEMTYPE_BOW },
	{ ' wbl', ITEMTYPE_BOW },
	{ ' bbs', ITEMTYPE_BOW },
	{ ' bbl', ITEMTYPE_BOW },
	{ ' tss', ITEMTYPE_STAFF },
	{ ' tsl', ITEMTYPE_STAFF },
	{ ' tsc', ITEMTYPE_STAFF },
	{ ' tsb', ITEMTYPE_STAFF },
	{ ' xal', ITEMTYPE_AXE },
	{ ' ycs', ITEMTYPE_POLEARM },
	{ ' xig', ITEMTYPE_AXE },
	{ ' xtb', ITEMTYPE_AXE },
	{ ' lah', ITEMTYPE_POLEARM },
	{ ' uam', ITEMTYPE_HAMMER },
	{ ' xap', ITEMTYPE_POLEARM },
	{ ' lah', ITEMTYPE_POLEARM },
	{ ' bxh', ITEMTYPE_CROSSBOW },
	{ ' bxl', ITEMTYPE_CROSSBOW },
	{ ' xat', ITEMTYPE_THROWING_AXE },
	{ ' cps', ITEMTYPE_CLUB },
	{ ' rbs', ITEMTYPE_SWORD },
	{ ' tsm', ITEMTYPE_MACE },
	{ ' pcs', ITEMTYPE_SCEPTER },
	{ ' mpg', ITEMTYPE_MISSILE_POTION },
	{ ' mpo', ITEMTYPE_MISSILE_POTION },
	{ ' fkt', ITEMTYPE_THROWING_KNIFE },
	{ ' dlb', ITEMTYPE_KNIFE },
	{ ' dsb', ITEMTYPE_SWORD },
	{ ' wsb', ITEMTYPE_SWORD },
	{ ' sh2', ITEMTYPE_SWORD },
	{ ' nrb', ITEMTYPE_SPEAR },
	{ ' wbh', ITEMTYPE_BOW },
	{ ' wbc', ITEMTYPE_BOW },
	{ ' bws', ITEMTYPE_BOW },
	{ ' bwl', ITEMTYPE_BOW },
	{ ' tsw', ITEMTYPE_STAFF },
	{ ' xab', ITEMTYPE_AXE },
	{ ' rab', ITEMTYPE_POLEARM },
	{ ' xag', ITEMTYPE_AXE },
	{ ' bxr', ITEMTYPE_CROSSBOW },
	{ ' bxm', ITEMTYPE_CROSSBOW },
	{ ' tbz', ITEMTYPE_NONE_2 },
	{ ' raa', ITEMTYPE_ARMOR },
	{ ' ptl', ITEMTYPE_ARMOR },
	{ ' lms', ITEMTYPE_SHIELD },
	{ ' stg', ITEMTYPE_ARMOR },
	{ ' vqa', ITEMTYPE_BODY_PART },
	{ ' vqc', ITEMTYPE_BODY_PART },
	{ ' lbv', ITEMTYPE_BELT },
	{ ' lbt', ITEMTYPE_BELT },
	{ ' lgv', ITEMTYPE_GLOVES },
	{ ' lgt', ITEMTYPE_GLOVES },
	{ ' tbv', ITEMTYPE_BOOTS },
	{ ' tbt', ITEMTYPE_BOOTS },
	{ ' blf', ITEMTYPE_SWORD },
	{ ' ipm', ITEMTYPE_AXE },
	{ ' lab', ITEMTYPE_THROWING_AXE },
	{ ' gel', ITEMTYPE_CLUB },
	{ ' tlq', ITEMTYPE_ARMOR },
	{ ' xa2', ITEMTYPE_AXE },
	{ ' xaw', ITEMTYPE_AXE },
	{ ' nwg', ITEMTYPE_MACE },
	{ ' amg', ITEMTYPE_MACE },
	{ ' dsw', ITEMTYPE_SWORD },
	{ ' sig', ITEMTYPE_SWORD },
	{ ' dlb', ITEMTYPE_KNIFE },
	{ ' fkb', ITEMTYPE_KNIFE },
	{ ' pss', ITEMTYPE_SPEAR },
	{ ' pst', ITEMTYPE_SPEAR },
	{ ' eps', ITEMTYPE_SPEAR },
	{ ' uov', ITEMTYPE_POLEARM },
	{ ' csw', ITEMTYPE_POLEARM },
	{ ' irk', ITEMTYPE_KNIFE },
	{ ' tps', ITEMTYPE_SPEAR },
	{ ' csg', ITEMTYPE_SCEPTER },
	{ ' psw', ITEMTYPE_SCEPTER },
	{ ' tsh', ITEMTYPE_STAFF },
	{ ' fsm', ITEMTYPE_STAFF },
	{ ' hfh', ITEMTYPE_MACE },
	{ ' ah9', ITEMTYPE_AXE },
	{ ' xa9', ITEMTYPE_AXE },
	{ ' a29', ITEMTYPE_AXE },
	{ ' pm9', ITEMTYPE_AXE },
	{ ' aw9', ITEMTYPE_AXE },
	{ ' al9', ITEMTYPE_AXE },
	{ ' ab9', ITEMTYPE_AXE },
	{ ' tb9', ITEMTYPE_AXE },
	{ ' ag9', ITEMTYPE_AXE },
	{ ' ig9', ITEMTYPE_AXE },
	{ ' nw9', ITEMTYPE_WAND },
	{ ' wy9', ITEMTYPE_WAND },
	{ ' wb9', ITEMTYPE_WAND },
	{ ' wg9', ITEMTYPE_WAND },
	{ ' lc9', ITEMTYPE_MACE },
	{ ' cs9', ITEMTYPE_SCEPTER },
	{ ' sq9', ITEMTYPE_SCEPTER },
	{ ' sw9', ITEMTYPE_SCEPTER },
	{ ' ps9', ITEMTYPE_MACE },
	{ ' am9', ITEMTYPE_MACE },
	{ ' tm9', ITEMTYPE_MACE },
	{ ' lf9', ITEMTYPE_MACE },
	{ ' hw9', ITEMTYPE_MACE },
	{ ' 9m9', ITEMTYPE_MACE },
	{ ' mg9', ITEMTYPE_MACE },
	{ ' ss9', ITEMTYPE_SWORD },
	{ ' ms9', ITEMTYPE_SWORD },
	{ ' bs9', ITEMTYPE_SWORD },
	{ ' cf9', ITEMTYPE_SWORD },
	{ ' rc9', ITEMTYPE_SWORD },
	{ ' sb9', ITEMTYPE_SWORD },
	{ ' sl9', ITEMTYPE_SWORD },
	{ ' dw9', ITEMTYPE_SWORD },
	{ ' h29', ITEMTYPE_SWORD },
	{ ' mc9', ITEMTYPE_SWORD },
	{ ' sg9', ITEMTYPE_SWORD },
	{ ' 9b9', ITEMTYPE_SWORD },
	{ ' bf9', ITEMTYPE_SWORD },
	{ ' dg9', ITEMTYPE_SWORD },
	{ ' gd9', ITEMTYPE_KNIFE },
	{ ' id9', ITEMTYPE_KNIFE },
	{ ' rk9', ITEMTYPE_KNIFE },
	{ ' lb9', ITEMTYPE_KNIFE },
	{ ' kt9', ITEMTYPE_THROWING_KNIFE },
	{ ' at9', ITEMTYPE_THROWING_AXE },
	{ ' kb9', ITEMTYPE_THROWING_KNIFE },
	{ ' 8b9', ITEMTYPE_THROWING_AXE },
	{ ' aj9', ITEMTYPE_SPEAR },
	{ ' ip9', ITEMTYPE_SPEAR },
	{ ' 9s9', ITEMTYPE_SPEAR },
	{ ' lg9', ITEMTYPE_SPEAR },
	{ ' st9', ITEMTYPE_SPEAR },
	{ ' rs9', ITEMTYPE_SPEAR },
	{ ' rt9', ITEMTYPE_SPEAR },
	{ ' rb9', ITEMTYPE_SPEAR },
	{ ' ts9', ITEMTYPE_SPEAR },
	{ ' 9p9', ITEMTYPE_SPEAR },
	{ ' 7b9', ITEMTYPE_POLEARM },
	{ ' ov9', ITEMTYPE_POLEARM },
	{ ' 8s9', ITEMTYPE_POLEARM },
	{ ' ap9', ITEMTYPE_POLEARM },
	{ ' 9h9', ITEMTYPE_POLEARM },
	{ ' cw9', ITEMTYPE_POLEARM },
	{ ' ss8', ITEMTYPE_STAFF },
	{ ' sl8', ITEMTYPE_STAFF },
	{ ' sc8', ITEMTYPE_STAFF },
	{ ' sb8', ITEMTYPE_STAFF },
	{ ' sw8', ITEMTYPE_STAFF },
	{ ' bs8', ITEMTYPE_BOW },
	{ ' bh8', ITEMTYPE_BOW },
	{ ' bl8', ITEMTYPE_BOW },
	{ ' bc8', ITEMTYPE_BOW },
	{ ' 8s8', ITEMTYPE_BOW },
	{ ' 8l8', ITEMTYPE_BOW },
	{ ' ws8', ITEMTYPE_BOW },
	{ ' wl8', ITEMTYPE_BOW },
	{ ' xl8', ITEMTYPE_CROSSBOW },
	{ ' xm8', ITEMTYPE_CROSSBOW },
	{ ' xh8', ITEMTYPE_CROSSBOW },
	{ ' xr8', ITEMTYPE_CROSSBOW },
	{ ' pax', ITEMTYPE_HELM },
	{ ' pkx', ITEMTYPE_HELM },
	{ ' mlx', ITEMTYPE_HELM },
	{ ' lhx', ITEMTYPE_HELM },
	{ ' mhx', ITEMTYPE_HELM },
	{ ' nrx', ITEMTYPE_HELM },
	{ ' ksx', ITEMTYPE_HELM },
	{ ' iux', ITEMTYPE_ARMOR },
	{ ' aex', ITEMTYPE_ARMOR },
	{ ' alx', ITEMTYPE_ARMOR },
	{ ' utx', ITEMTYPE_ARMOR },
	{ ' gnx', ITEMTYPE_ARMOR },
	{ ' lcx', ITEMTYPE_ARMOR },
	{ ' nhx', ITEMTYPE_ARMOR },
	{ ' srx', ITEMTYPE_ARMOR },
	{ ' lpx', ITEMTYPE_ARMOR },
	{ ' tlx', ITEMTYPE_ARMOR },
	{ ' dlx', ITEMTYPE_ARMOR },
	{ ' htx', ITEMTYPE_ARMOR },
	{ ' lux', ITEMTYPE_ARMOR },
	{ ' rax', ITEMTYPE_ARMOR },
	{ ' ptx', ITEMTYPE_ARMOR },
	{ ' cux', ITEMTYPE_SHIELD },
	{ ' lmx', ITEMTYPE_SHIELD },
	{ ' grx', ITEMTYPE_SHIELD },
	{ ' tix', ITEMTYPE_SHIELD },
	{ ' wox', ITEMTYPE_SHIELD },
	{ ' stx', ITEMTYPE_SHIELD },
	{ ' glx', ITEMTYPE_GLOVES },
	{ ' gvx', ITEMTYPE_GLOVES },
	{ ' gmx', ITEMTYPE_GLOVES },
	{ ' gtx', ITEMTYPE_GLOVES },
	{ ' ghx', ITEMTYPE_GLOVES },
	{ ' blx', ITEMTYPE_BOOTS },
	{ ' bvx', ITEMTYPE_BOOTS },
	{ ' bmx', ITEMTYPE_BOOTS },
	{ ' btx', ITEMTYPE_BOOTS },
	{ ' bhx', ITEMTYPE_BOOTS },
	{ ' blz', ITEMTYPE_BELT },
	{ ' bvz', ITEMTYPE_BELT },
	{ ' bmz', ITEMTYPE_BELT },
	{ ' btz', ITEMTYPE_BELT },
	{ ' bhz', ITEMTYPE_BELT },
	{ ' 9hx', ITEMTYPE_HELM },
	{ ' hsx', ITEMTYPE_SHIELD },
	{ ' kpx', ITEMTYPE_SHIELD },
	{ ' 1fq', ITEMTYPE_MACE },
	{ ' 2fq', ITEMTYPE_MACE },
};

//D2Common.0x6FDEA708
struct D2InventoryComponentItemType gTxtComponentItemTypeMap[255] = {};

//D2Common.0x6FDEAF00
int gnComponentArrayRecordCount;
//D2Common.0x6FDEAF04
BOOL gbComponentArrayInitialized;


//D2Common.0x6FD8E210
BOOL __cdecl INVENTORY_RemoveItem(struct D2Unit* pItem)
{
	struct D2ItemExtraData* pItemExtraData = INVENTORY_GetItemExtraDataFromItem(pItem);

	if (!pItemExtraData || !INVENTORY_GetPtrIfValid(pItemExtraData->pParentInv))
	{
		return FALSE;
	}

	if (pItemExtraData->nNodePos > 0)
	{
		const int nNodePos = pItemExtraData->nNodePos - 1;
		if (pItemExtraData->pParentInv->nGridCount > nNodePos)
		{
			struct D2InventoryGrid* pInventoryGrid = &pItemExtraData->pParentInv->pGrids[nNodePos];

			if (pItemExtraData->unk0x10)
			{
				struct D2ItemExtraData* pExtraData = INVENTORY_GetItemExtraDataFromItem(pItemExtraData->unk0x10);
				if (pExtraData)
				{
					pExtraData->unk0x14 = pItemExtraData->unk0x14;
				}
			}
			else
			{
				if (pInventoryGrid->pItem == pItem)
				{
					pInventoryGrid->pItem = pItemExtraData->unk0x14;
				}
			}

			if (pItemExtraData->unk0x14)
			{
				struct D2ItemExtraData* pExtraData = INVENTORY_GetItemExtraDataFromItem(pItemExtraData->unk0x14);
				if (pExtraData)
				{
					pExtraData->unk0x10 = pItemExtraData->unk0x10;
				}
			}
			else
			{
				if (pInventoryGrid->pLastItem == pItem)
				{
					pInventoryGrid->pLastItem = pItemExtraData->unk0x10;
				}
			}

			if (pInventoryGrid->ppItems)
			{
				struct D2Coord pCoords = {};

				UNITS_GetCoords(pItem, &pCoords);

				if (nNodePos < 1)
				{
					pInventoryGrid->ppItems[pCoords.nX + pCoords.nY * pInventoryGrid->nGridWidth] = nullptr;
				}
				else
				{
					uint8_t nHeight = 0;
					uint8_t nWidth = 0;

					ITEMS_GetDimensions(pItem, &nWidth, &nHeight, __FILE__, __LINE__);

					for (int y = pCoords.nY; y < pCoords.nY + nHeight; ++y)
					{
						for (int x = pCoords.nX; x < pCoords.nX + nWidth; ++x)
						{
							pInventoryGrid->ppItems[y * pInventoryGrid->nGridWidth + x] = nullptr;
						}
					}
				}
			}

			pItemExtraData->unk0x14 = nullptr;
			pItemExtraData->unk0x10 = nullptr;
			pItemExtraData->nNodePos = 0;
		}
	}

	if (pItemExtraData->pParentInv->pCursorItem == pItem)
	{
		pItemExtraData->pParentInv->pCursorItem = nullptr;
	}
	else
	{
		if (pItemExtraData->pPreviousItem)
		{
			struct D2ItemExtraData* pExtraData = INVENTORY_GetItemExtraDataFromItem(pItemExtraData->pPreviousItem);
			if (pExtraData)
			{
				pExtraData->pNextItem = pItemExtraData->pNextItem;
			}
		}
		else
		{
			if (pItemExtraData->pParentInv->pFirstItem == pItem)
			{
				pItemExtraData->pParentInv->pFirstItem = pItemExtraData->pNextItem;
			}
		}

		if (pItemExtraData->pNextItem)
		{
			struct D2ItemExtraData* pExtraData = INVENTORY_GetItemExtraDataFromItem(pItemExtraData->pNextItem);
			if (pExtraData)
			{
				pExtraData->pPreviousItem = pItemExtraData->pPreviousItem;
			}
		}
		else
		{
			if (pItemExtraData->pParentInv->pLastItem == pItem)
			{
				pItemExtraData->pParentInv->pLastItem = pItemExtraData->pPreviousItem;
			}
		}

		pItemExtraData->pNextItem = nullptr;
		pItemExtraData->pPreviousItem = nullptr;

		--pItemExtraData->pParentInv->dwItemCount;
	}

	ITEMS_SetOwnerId(pItem, -1);

	if (pItemExtraData->pParentInv->pOwner)
	{
		STATLIST_ExpireUnitStatlist(pItemExtraData->pParentInv->pOwner, pItem);
	}

	if (pItemExtraData->pParentInv->dwLeftItemGUID == pItem->dwUnitId)
	{
		pItemExtraData->pParentInv->dwLeftItemGUID = D2UnitInvalidGUID;
	}

	pItemExtraData->pParentInv = nullptr;
	pItemExtraData->nNodePos = 0;
	pItemExtraData->nNodePosOther = 0;

	return TRUE;
}

//D2Common.0x6FD8E4A0
struct D2ItemExtraData* __cdecl INVENTORY_GetItemExtraDataFromItem(struct D2Unit* pItem)
{
	struct D2ItemData* pItemData = ITEMS_GetItemData(pItem);
	if (pItemData)
	{
		return &pItemData->pExtraData;
	}
	
	return nullptr;
}

//D2Common.0x6FD8E4C0 (#10240)
struct D2Inventory* __cdecl INVENTORY_AllocInventory(void* pMemPool, struct D2Unit* pOwner)
{
	if (!pMemPool && pOwner)
	{
		pMemPool = pOwner->pMemoryPool;
	}

	struct D2Inventory* pInventory = D2_ALLOC_STRC_POOL(pMemPool, struct D2Inventory);
	if (pInventory)
	{
		memset(pInventory, 0x00, sizeof(struct D2Inventory));

		pInventory->dwSignature = D2C_InventoryHeader;
		pInventory->pMemPool = pMemPool;
		pInventory->pOwner = pOwner;

		if (pOwner)
		{
			pOwner->pInventory = pInventory;
			pInventory->dwOwnerGuid = pOwner->dwUnitId;
		}
	}

	return pInventory;
}

//D2Common.0x6FD8E520 (#10241)
void __cdecl INVENTORY_FreeInventory(struct D2Inventory* pInventory)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		if (pInventory->pCursorItem)
		{
			INVENTORY_RemoveItem(pInventory->pCursorItem);
		}

		for (struct D2Unit* pItem = pInventory->pFirstItem; pItem; pItem = pInventory->pFirstItem)
		{
			INVENTORY_RemoveItem(pItem);
		}

		for (int i = 0; i < pInventory->nGridCount; ++i)
		{
			if (pInventory->pGrids[i].ppItems)
			{
				D2_FREE_POOL(pInventory->pMemPool, pInventory->pGrids[i].ppItems);
			}
		}

		if (pInventory->pGrids)
		{
			D2_FREE_POOL(pInventory->pMemPool, pInventory->pGrids);
		}

		if (pInventory->pOwner)
		{
			pInventory->pOwner->pInventory = nullptr;
		}
		
		struct D2InventoryNode* pNextNode = nullptr;
		for (struct D2InventoryNode* pNode = pInventory->pFirstNode; pNode; pNode = pNextNode)
		{
			pNextNode = pNode->pNext;
			D2_FREE_POOL(pInventory->pMemPool, pNode);
			
		}

		struct D2Corpse* pNextCorpse = nullptr;
		for (struct D2Corpse* pCorpse = pInventory->pFirstCorpse; pCorpse; pCorpse = pNextCorpse)
		{
			pNextCorpse = pCorpse->pNextCorpse;
			D2_FREE_POOL(pInventory->pMemPool, pCorpse);
		}

		D2_FREE_POOL(pInventory->pMemPool, pInventory);
	}
}

//D2Common.0x6FD8E620 (#10244)
BOOL __cdecl INVENTORY_CompareWithItemsParentInventory(struct D2Inventory* pInventory, struct D2Unit* pItem)
{
	if (pInventory)
	{
		struct D2ItemExtraData* pItemExtraData = INVENTORY_GetItemExtraDataFromItem(pItem);
		return pItemExtraData->pParentInv == pInventory;
	}

	return FALSE;
}

//D2Common.0x6FD8E660 (#10243)
struct D2Unit* __cdecl INVENTORY_RemoveItemFromInventory(struct D2Inventory* pInventory, struct D2Unit* pItem)
{
	if (INVENTORY_CompareWithItemsParentInventory(pInventory, pItem))
	{
		INVENTORY_RemoveItem(pItem);
		return pItem;
	}
	
	return nullptr;
}

//D2Common.0x6FD8E6A0 (#10242)
BOOL __cdecl INVENTORY_PlaceItemInSocket(struct D2Inventory* pInventory, struct D2Unit* pItem, int nUnused)
{
	D2_MAYBE_UNUSED(nUnused);
	if (!INVENTORY_GetPtrIfValid(pInventory))
	{
		return FALSE;
	}

	if (!pInventory->pOwner || pInventory->pOwner->dwUnitType != UNIT_ITEM)
	{
		return TRUE;
	}

	struct D2ItemExtraData* pItemExtraData = INVENTORY_GetItemExtraDataFromItem(pItem);
	if (!pItemExtraData)
	{
		return FALSE;
	}

	INVENTORY_RemoveItem(pItem);

	struct D2Unit* pLastItem = pInventory->pLastItem;
	if (pLastItem)
	{
		struct D2ItemExtraData* pLastItemExtraData = INVENTORY_GetItemExtraDataFromItem(pLastItem);
		if (pLastItemExtraData)
		{
			pLastItemExtraData->pNextItem = pItem;
		}
	}
	else
	{
		pInventory->pFirstItem = pItem;
	}

	pItemExtraData->pPreviousItem = pInventory->pLastItem;
	pInventory->pLastItem = pItem;
	pItemExtraData->pParentInv = pInventory;

	UNITS_SetXForStaticUnit(pItem, pInventory->dwItemCount);
	UNITS_SetYForStaticUnit(pItem, 0);

	pItemExtraData->nNodePos = 0;
	pItemExtraData->nNodePosOther = 1;

	++pInventory->dwItemCount;

	ITEMS_SetOwnerId(pItem, -1);

	return TRUE;
}

//D2Common.0x6FD8E7A0 (#10277)
struct D2Unit* __cdecl INVENTORY_GetFirstItem(struct D2Inventory* pInventory)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		return pInventory->pFirstItem;
	}

	return nullptr;
}

//D2Common.0x6FD8E7C0 (#10278)
struct D2Unit* __cdecl INVENTORY_GetLastItem(struct D2Inventory* pInventory)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		return pInventory->pLastItem;
	}

	return nullptr;
}

//D2Common.0x6FD8E7E0 (#10245)
BOOL __cdecl INVENTORY_GetFreePosition(struct D2Inventory* pInventory, struct D2Unit* pItem, int nInventoryRecordId, int* pFreeX, int* pFreeY, uint8_t nPage)
{
	if (!INVENTORY_GetPtrIfValid(pInventory) || !ITEMS_GetItemData(pItem))
	{
		return FALSE;
	}
	
	uint8_t nWidth = 0;
	uint8_t nHeight = 0;
	ITEMS_GetDimensions(pItem, &nWidth, &nHeight, __FILE__, __LINE__);
	if (!nWidth || !nHeight)
	{
		return FALSE;
	}

	struct D2InventoryGridInfo pInventoryGridInfo = {};
	DATATBLS_GetInventoryGridInfo(nInventoryRecordId, 0, &pInventoryGridInfo);

	struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, nPage + INVGRID_INVENTORY, &pInventoryGridInfo);
	if (!pInventoryGrid)
	{
		return FALSE;
	}

	if (nHeight == 1)
	{
		if (pInventory->pOwner && pInventory->pOwner->dwUnitType == UNIT_PLAYER)
		{
			return INVENTORY_FindFreePositionBottomRightToTopLeftWithWeight(pInventoryGrid, pFreeX, pFreeY, nWidth, 1);
		}

		for (int nX = pInventoryGrid->nGridWidth - 1; nX >= 0; --nX)
		{
			for (int nY = 0; nY < pInventoryGrid->nGridHeight; ++nY)
			{
				if (INVENTORY_CanItemBePlacedAtPos(pInventoryGrid, nX, nY, nWidth, 1))
				{
					*pFreeX = nX;
					*pFreeY = nY;

					return TRUE;
				}
			}
		}

		return FALSE;
	}

	if (pInventory->pOwner && pInventory->pOwner->dwUnitType == UNIT_PLAYER)
	{
		return INVENTORY_FindFreePositionTopLeftToBottomRightWithWeight(pInventoryGrid, pFreeX, pFreeY, nWidth, nHeight);
	}

	return INVENTORY_FindFreePositionTopLeftToBottomRight(pInventoryGrid, pFreeX, pFreeY, nWidth, nHeight);
}

//D2Common.0x6FD8EAF0
struct D2InventoryGrid* __cdecl INVENTORY_GetGrid(struct D2Inventory* pInventory, int nInventoryGrid, struct D2InventoryGridInfo* pInventoryGridInfo)
{
	struct D2InventoryGrid* pInventoryGrid = nullptr;

	if (pInventory->nGridCount <= nInventoryGrid)
	{
		if (!pInventoryGridInfo)
		{
			return nullptr;
		}

		pInventory->pGrids = (struct D2InventoryGrid*)D2_REALLOC_POOL(pInventory->pMemPool, pInventory->pGrids, sizeof(struct D2InventoryGrid) * (nInventoryGrid + 1));
		memset(&pInventory->pGrids[pInventory->nGridCount], 0x00, sizeof(struct D2InventoryGrid) * (nInventoryGrid - pInventory->nGridCount + 1));
		pInventory->nGridCount = nInventoryGrid + 1;

		pInventoryGrid = &pInventory->pGrids[nInventoryGrid];
		pInventoryGrid->nGridWidth = pInventoryGridInfo->nGridX;
		pInventoryGrid->nGridHeight = pInventoryGridInfo->nGridY;
		pInventoryGrid->ppItems = (struct D2Unit**)D2_ALLOC_POOL(pInventory->pMemPool, sizeof(struct D2Unit*) * pInventoryGrid->nGridHeight * pInventoryGrid->nGridWidth);
		memset(pInventoryGrid->ppItems, 0x00, sizeof(struct D2Unit*) * pInventoryGrid->nGridHeight * pInventoryGrid->nGridWidth);
	}
	else
	{
		pInventoryGrid = &pInventory->pGrids[nInventoryGrid];
		if (pInventoryGridInfo)
		{
			if (!pInventoryGrid->ppItems)
			{
				pInventoryGrid->nGridWidth = pInventoryGridInfo->nGridX;
				pInventoryGrid->nGridHeight = pInventoryGridInfo->nGridY;
				pInventoryGrid->ppItems = (struct D2Unit**)D2_ALLOC_POOL(pInventory->pMemPool, sizeof(struct D2Unit*) * pInventoryGrid->nGridHeight * pInventoryGrid->nGridWidth);
				memset(pInventoryGrid->ppItems, 0x00, sizeof(struct D2Unit*) * pInventoryGrid->nGridHeight * pInventoryGrid->nGridWidth);
			}

			if (pInventoryGrid->nGridWidth != pInventoryGridInfo->nGridX || pInventoryGrid->nGridHeight != pInventoryGridInfo->nGridY)
			{
				return nullptr;
			}
		}
		else if (!pInventoryGrid->ppItems)
		{
			return nullptr;
		}
	}

	return pInventoryGrid;
}

//D2Common.0x6FD8EC70
BOOL __cdecl INVENTORY_CanItemBePlacedAtPos(struct D2InventoryGrid* pInventoryGrid, int nX, int nY, uint8_t nItemWidth, uint8_t nItemHeight)
{
	if (nItemWidth + nX > pInventoryGrid->nGridWidth || nItemHeight + nY > pInventoryGrid->nGridHeight)
	{
		return FALSE;
	}

	for (int nTestY = 0; nTestY < nItemHeight; ++nTestY)
	{
		for (int nTestX = 0; nTestX < nItemWidth; ++nTestX)
		{
			if (pInventoryGrid->ppItems[(nX + nTestX) + (nY + nTestY) * pInventoryGrid->nGridWidth])
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

//D2Common.0x6FD8ECF0
BOOL __cdecl INVENTORY_FindFreePositionBottomRightToTopLeftWithWeight(struct D2InventoryGrid* pInventoryGrid, int* pFreeX, int* pFreeY, uint8_t nItemWidth, uint8_t nItemHeight)
{
	if (pInventoryGrid->nGridWidth < 1 || pInventoryGrid->nGridHeight < 1)
	{
		return FALSE;
	}

	uint8_t nMax = 0;
	for (int nX = pInventoryGrid->nGridWidth - 1; nX >= 0; --nX)
	{
		for (int nY = pInventoryGrid->nGridHeight - 1; nY >= 0; --nY)
		{
			if (INVENTORY_CanItemBePlacedAtPos(pInventoryGrid, nX, nY, nItemWidth, nItemHeight))
			{
				const uint8_t nWeight = INVENTORY_GetPlacementWeight(pInventoryGrid, nX, nY, nItemWidth, nItemHeight);
				if (nWeight > nMax)
				{
					nMax = nWeight;

					*pFreeX = nX;
					*pFreeY = nY;

					if (nWeight == 255)
					{
						return TRUE;
					}
				}
			}
		}
	}

	return nMax > 0;
}

//D2Common.0x6FD8EE20
uint8_t __cdecl INVENTORY_GetPlacementWeight(struct D2InventoryGrid* pInventoryGrid, int nXPos, int nYPos, uint8_t nItemWidth, uint8_t nItemHeight)
{
	uint8_t nResult = 0;

	if (nXPos > 0)
	{
		for (int i = 0; i < nItemHeight; ++i)
		{
			if (pInventoryGrid->ppItems[nXPos - 1 + (nYPos + i) * pInventoryGrid->nGridWidth])
			{
				++nResult;
			}
		}
	}
	else
	{
		nResult = nItemHeight;
	}

	if (nXPos + nItemWidth < pInventoryGrid->nGridWidth)
	{
		for (int i = 0; i < nItemHeight; ++i)
		{
			if (pInventoryGrid->ppItems[nXPos + nItemWidth + (nYPos + i) * pInventoryGrid->nGridWidth])
			{
				++nResult;
			}
		}
	}
	else
	{
		nResult += nItemHeight;
	}

	if (nYPos > 0)
	{
		for (int i = 0; i < nItemWidth; ++i)
		{
			if (pInventoryGrid->ppItems[(nXPos + i) + (nYPos - 1) * pInventoryGrid->nGridWidth])
			{
				++nResult;
			}
		}
	}
	else
	{
		nResult += nItemWidth;
	}

	if (nYPos + nItemHeight < pInventoryGrid->nGridHeight)
	{
		for (int i = 0; i < nItemWidth; ++i)
		{
			if (pInventoryGrid->ppItems[(nXPos + i) + (nYPos + nItemHeight) * pInventoryGrid->nGridWidth])
			{
				++nResult;
			}
		}
	}
	else
	{
		nResult += nItemWidth;
	}

	if (nResult >= 2 * (nItemHeight + nItemWidth))
	{
		nResult = 255;
	}

	return nResult;
}

//D2Common.0x6FD8EFB0
BOOL __cdecl INVENTORY_FindFreePositionTopLeftToBottomRightWithWeight(struct D2InventoryGrid* pInventoryGrid, int* pFreeX, int* pFreeY, uint8_t nItemWidth, uint8_t nItemHeight)
{
	if (pInventoryGrid->nGridWidth <= 0 || pInventoryGrid->nGridHeight <= 0)
	{
		return FALSE;
	}

	uint8_t nMax = 0;
	for (int nY = 0; nY < pInventoryGrid->nGridHeight; ++nY)
	{
		for (int nX = 0; nX < pInventoryGrid->nGridWidth; ++nX)
		{
			if (INVENTORY_CanItemBePlacedAtPos(pInventoryGrid, nX, nY, nItemWidth, nItemHeight))
			{
				const uint8_t nWeight = INVENTORY_GetPlacementWeight(pInventoryGrid, nX, nY, nItemWidth, nItemHeight);
				if (nWeight > nMax)
				{
					nMax = nWeight;

					*pFreeX = nX;
					*pFreeY = nY;

					if (nWeight == 255)
					{
						return TRUE;
					}
				}
			}
		}
	}

	return nMax > 0;
}

//D2Common.0x6FD8F0E0
BOOL __cdecl INVENTORY_FindFreePositionTopLeftToBottomRight(struct D2InventoryGrid* pInventoryGrid, int* pFreeX, int* pFreeY, uint8_t nItemWidth, uint8_t nItemHeight)
{
	for (int nX = 0; nX < pInventoryGrid->nGridWidth; ++nX)
	{
		for (int nY = 0; nY < pInventoryGrid->nGridHeight; ++nY)
		{
			if (INVENTORY_CanItemBePlacedAtPos(pInventoryGrid, nX, nY, nItemWidth, nItemHeight))
			{
				*pFreeX = nX;
				*pFreeY = nY;
				return TRUE;
			}
		}
	}

	return FALSE;
}

//D2Common.0x6FD8F1E0 (#10246)
BOOL __cdecl INVENTORY_PlaceItemAtFreePosition(struct D2Inventory* pInventory, struct D2Unit* pItem, int nInventoryRecordId, BOOL bUnused, uint8_t nPage, const char* szFile, int nLine)
{
	int nX = 0;
	int nY = 0;
	if (pInventory && INVENTORY_UnitIsItem(pItem) && INVENTORY_GetFreePosition(pInventory, pItem, nInventoryRecordId, &nX, &nY, nPage))
	{
		return INVENTORY_PlaceItemInGrid(pInventory, pItem, nX, nY, nPage + 2, nInventoryRecordId, bUnused);
	}

	return FALSE;
}

//D2Common.0x6FD8F250
BOOL __cdecl INVENTORY_PlaceItemInGrid(struct D2Inventory* pInventory, struct D2Unit* pItem, int nXPos, int nYPos, int nInventoryGrid, int nInventoryRecordId, BOOL bUnused)
{
	D2_MAYBE_UNUSED(bUnused);
	if (!INVENTORY_GetPtrIfValid(pInventory))
	{
		return FALSE;
	}

	struct D2ItemExtraData* pItemExtraData = INVENTORY_GetItemExtraDataFromItem(pItem);
	if (!pItemExtraData)
	{
		return FALSE;
	}

	uint8_t nHeight = 0;
	uint8_t nWidth = 0;
	ITEMS_GetDimensions(pItem, &nWidth, &nHeight, __FILE__, __LINE__);
	if (!nWidth || !nHeight)
	{
		return FALSE;
	}

	struct D2InventoryGrid* pInventoryGrid = nullptr;
	if (nInventoryGrid < INVGRID_INVENTORY)
	{
		nWidth = 1;
		nHeight = 1;
		if (nInventoryGrid == INVGRID_BODYLOC)
		{
			pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);
		}
		else if (nInventoryGrid == INVGRID_BELT)
		{
			pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BELT, &gBeltInventoryGridInfo);
		}
	}
	else
	{
		struct D2InventoryGridInfo pInventoryGridInfo = {};
		DATATBLS_GetInventoryGridInfo(nInventoryRecordId, 0, &pInventoryGridInfo);
		if (nXPos < 0 || nXPos + nWidth > pInventoryGridInfo.nGridX || nYPos < 0 || nYPos + nHeight > pInventoryGridInfo.nGridY)
		{
			return FALSE;
		}

		pInventoryGrid = INVENTORY_GetGrid(pInventory, nInventoryGrid, &pInventoryGridInfo);
	}

	if (!pInventoryGrid)
	{
		return FALSE;
	}

	if (!INVENTORY_CanItemBePlacedAtPos(pInventoryGrid, nXPos, nYPos, nWidth, nHeight))
	{
		return FALSE;
	}

	if (pItem->dwAnimMode == IMODE_ONGROUND && UNITS_GetRoom(pItem))
	{
		if (pItem->dwFlagEx & UNITFLAGEX_SERVERUNIT)
		{
			DUNGEON_AllocDrlgDelete(UNITS_GetRoom(pItem), pItem->dwUnitType, pItem->dwUnitId);
		}

		UNITS_FreeCollisionPath(pItem);
		UNITROOM_RemoveUnitFromRoom(pItem);
	}

	INVENTORY_RemoveItem(pItem);

	if (pInventory->pLastItem)
	{
		struct D2ItemExtraData* pLastItemExtraData = INVENTORY_GetItemExtraDataFromItem(pInventory->pLastItem);
		if (pLastItemExtraData)
		{
			pLastItemExtraData->pNextItem = pItem;
		}
	}
	else
	{
		pInventory->pFirstItem = pItem;
	}

	pItemExtraData->pPreviousItem = pInventory->pLastItem;
	pInventory->pLastItem = pItem;
	pItemExtraData->pParentInv = pInventory;

	if (pInventoryGrid->pLastItem)
	{
		struct D2ItemExtraData* pLastItemExtraData = INVENTORY_GetItemExtraDataFromItem(pInventoryGrid->pLastItem);
		if (pLastItemExtraData)
		{
			pLastItemExtraData->unk0x14 = pItem;
		}
	}
	else
	{
		pInventoryGrid->pItem = pItem;
	}

	pItemExtraData->unk0x10 = pInventoryGrid->pLastItem;
	pInventoryGrid->pLastItem = pItem;

	for (int y = 0; y < nHeight; ++y)
	{
		for (int x = 0; x < nWidth; ++x)
		{
			pInventoryGrid->ppItems[nXPos + x + (nYPos + y) * pInventoryGrid->nGridWidth] = pItem;
		}
	}

	pItemExtraData->nNodePos = nInventoryGrid + 1;
	++pInventory->dwItemCount;

	UNITS_SetXForStaticUnit(pItem, nXPos);
	UNITS_SetYForStaticUnit(pItem, nYPos);

	if (pInventory->pOwner && pInventory->pOwner->dwUnitType == UNIT_PLAYER)
	{
		ITEMS_SetOwnerId(pItem, pInventory->pOwner->dwUnitId);
	}
	else
	{
		ITEMS_SetOwnerId(pItem, -1);
	}
	
	if (nInventoryGrid >= 2)
	{
		ITEMS_SetInvPage(pItem, nInventoryGrid - 2);
	}

	if (nInventoryGrid == INVGRID_BODYLOC)
	{
		if (nXPos >= 11)
		{
			pItemExtraData->nNodePosOther = 4;
		}
		else
		{
			pItemExtraData->nNodePosOther = 3;
		}
	}
	else if (nInventoryGrid == INVGRID_BELT)
	{
		pItemExtraData->nNodePosOther = 2;
	}
	else
	{
		pItemExtraData->nNodePosOther = 1;
	}

	return TRUE;
}

//D2Common.0x6FD8F600 (#10247)
BOOL __cdecl INVENTORY_CanItemBePlaced(struct D2Inventory* pInventory, struct D2Unit* pItem, int nXPos, int nYPos, int nInventoryRecordId, struct D2Unit** ppExchangeItem, unsigned int* pHoveredItems, uint8_t nPage)
{
	*pHoveredItems = 0;

	if (!INVENTORY_GetPtrIfValid(pInventory) || !INVENTORY_UnitIsItem(pItem) || nPage == (uint8_t)(-1) || nXPos < 0 || nYPos < 0)
	{
		return FALSE;
	}

	uint8_t nHeight = 0;
	uint8_t nWidth = 0;
	ITEMS_GetDimensions(pItem, &nWidth, &nHeight, __FILE__, __LINE__);
	if (!nWidth || !nHeight)
	{
		return FALSE;
	}

	struct D2InventoryGridInfo pInventoryGridInfo = {};
	DATATBLS_GetInventoryGridInfo(nInventoryRecordId, FALSE, &pInventoryGridInfo);

	struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, nPage + 2, &pInventoryGridInfo);
	if (!pInventoryGrid)
	{
		return FALSE;
	}

	BOOL bFree = TRUE;

	for (int nY = nYPos; nY < nYPos + nHeight; ++nY)
	{
		if (nY >= pInventoryGrid->nGridHeight)
		{
			return FALSE;
		}

		for (int nX = nXPos; nX < nXPos + nWidth; ++nX)
		{
			if (nX >= pInventoryGrid->nGridWidth)
			{
				return FALSE;
			}

			struct D2Unit* pCurrentItem = pInventoryGrid->ppItems[nX + nY * pInventoryGrid->nGridWidth];
			if (pCurrentItem)
			{
				bFree = FALSE;

				if (*ppExchangeItem != pCurrentItem)
				{
					*ppExchangeItem = pCurrentItem;

					++*pHoveredItems;
				}
				else
				{
					break;
				}
			}
		}
	}

	return bFree;
}

//D2Common.0x6FD8F780 (#10248)
BOOL __cdecl INVENTORY_CanItemsBeExchanged(struct D2Inventory* pInventory, struct D2Unit* pItem, int nXPos, int nYPos, int nInventoryRecordId, struct D2Unit** ppExchangeItem, uint8_t nPage, BOOL bCheckIfCube)
{
	if (!INVENTORY_GetPtrIfValid(pInventory) || !INVENTORY_UnitIsItem(pItem) || nPage == (uint8_t)(-1) || nXPos < 0 || nYPos < 0)
	{
		return FALSE;
	}

	uint8_t nHeight = 0;
	uint8_t nWidth = 0;
	ITEMS_GetDimensions(pItem, &nWidth, &nHeight, __FILE__, __LINE__);
	if (!nWidth || !nHeight)
	{
		return FALSE;
	}

	struct D2InventoryGridInfo pInventoryGridInfo = {};
	DATATBLS_GetInventoryGridInfo(nInventoryRecordId, FALSE, &pInventoryGridInfo);
	struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, nPage + 2, &pInventoryGridInfo);
	if (!pInventoryGrid)
	{
		return FALSE;
	}

	const int nXMax = nXPos + nWidth;
	const int nYMax = nYPos + nHeight;

	if (nXMax > pInventoryGrid->nGridWidth || nYMax > pInventoryGrid->nGridHeight)
	{
		return FALSE;
	}

	struct D2Unit* pLastItem = nullptr;
	int nCounter = 0;
	for (int nY = nYPos; nY < nYMax; ++nY)
	{
		for (int nX = nXPos; nX < nXMax; ++nX)
		{
			struct D2Unit* pCurrentItem = pInventoryGrid->ppItems[nX + nY * pInventoryGrid->nGridWidth];
			if (pCurrentItem)
			{
				*ppExchangeItem = pCurrentItem;

				if (bCheckIfCube && DATATBLS_GetItemsTxtRecord(pCurrentItem->dwClassId)->dwCode == ' xob')
				{
					return FALSE;
				}

				if (pCurrentItem != pLastItem)
				{
					pLastItem = pCurrentItem;

					++nCounter;
				}
			}
		}
	}

	if (nCounter > 1)
	{
		*ppExchangeItem = nullptr;
		return FALSE;
	}

	return TRUE;
}

//D2Common.0x6FD8F930 (#10249)
BOOL __cdecl INVENTORY_PlaceItemAtInventoryPage(struct D2Inventory* pInventory, struct D2Unit* pItem, int nXPos, int nYPos, int nInventoryRecordId, BOOL bUnused, uint8_t nPage)
{
	if (pInventory)
	{
		return INVENTORY_PlaceItemInGrid(pInventory, pItem, nXPos, nYPos, nPage + 2, nInventoryRecordId, bUnused);
	}

	return FALSE;
}

//D2Common.0x6FD8F970 (#10250)
void __cdecl INVENTORY_Return(const char* szFile, int nLine, struct D2Inventory* pInventory, int nX, int nY, int nInventoryRecordId, BOOL bClient, uint8_t nPage)
{
	return;
}

//D2Common.0x6FD8F980 (#10252)
struct D2Unit* __cdecl INVENTORY_GetItemFromInventoryPage(struct D2Inventory* pInventory, int nGridX, int nGridY, int* pX, int* pY, int nInventoryRecordId, uint8_t nPage)
{
	if (!INVENTORY_GetPtrIfValid(pInventory))
	{
		return nullptr;
	}

	struct D2InventoryGridInfo pInventoryGridInfo = {};
	DATATBLS_GetInventoryGridInfo(nInventoryRecordId, 0, &pInventoryGridInfo);

	struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, nPage + 2, &pInventoryGridInfo);
	if (pInventoryGrid && nGridX >= 0 && nGridX <= pInventoryGrid->nGridWidth && nGridY >= 0 && nGridY <= pInventoryGrid->nGridHeight)
	{
		struct D2Unit* pItem = pInventoryGrid->ppItems[nGridX + nGridY * pInventoryGrid->nGridWidth];
		if (pItem)
		{
			switch (pItem->dwUnitType)
			{
			case UNIT_PLAYER:
			case UNIT_MONSTER:
			case UNIT_MISSILE:
				*pX = pItem->pDynamicPath ? pItem->pDynamicPath->tGameCoords.wPosX : 0;
				*pY = pItem->pDynamicPath ? pItem->pDynamicPath->tGameCoords.wPosY : 0;
				break;

			case UNIT_OBJECT:
			case UNIT_ITEM:
			case UNIT_TILE:
				*pX = pItem->pStaticPath ? pItem->pStaticPath->tGameCoords.nX : 0;
				*pY = pItem->pStaticPath ? pItem->pStaticPath->tGameCoords.nY : 0;
				break;

			default:
				*pX = 0;
				*pY = 0;
				break;
			}

			return pItem;
		}
	}

	return nullptr;
}

//D2Common.0x6FD8FAB0 (#10253)
BOOL __cdecl INVENTORY_PlaceItemInBodyLoc(struct D2Inventory* pInventory, struct D2Unit* pItem, int nBodyLoc)
{
	if (pInventory && INVENTORY_ValidateBodyLoc(nBodyLoc))
	{
		return INVENTORY_PlaceItemInGrid(pInventory, pItem, nBodyLoc, 0, INVGRID_BODYLOC, 0, 0);
	}

	return FALSE;
}

//D2Common.0x6FD8FAE0 (#10257)
struct D2Unit* __cdecl INVENTORY_GetItemFromBodyLoc(struct D2Inventory* pInventory, int nBodyLoc)
{
	if (INVENTORY_GetPtrIfValid(pInventory) && INVENTORY_ValidateBodyLoc(nBodyLoc))
	{
		struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);
		if (pInventoryGrid)
		{
			return pInventoryGrid->ppItems[nBodyLoc];
		}
	}

	return nullptr;
}

//D2Common.0x6FD8FB20 (#10255)
void __cdecl INVENTORY_GetSecondWieldingWeapon(struct D2Unit* pPlayer, struct D2Inventory* pInventory, struct D2Unit** ppItem, int nBodyLoc)
{
	if (INVENTORY_GetPtrIfValid(pInventory) && !*ppItem && INVENTORY_ValidateBodyLoc(nBodyLoc))
	{
		struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);
		if (pInventoryGrid)
		{
			if (nBodyLoc == BODYLOC_RARM)
			{
				if (INVENTORY_GetWieldType(pPlayer, pInventory) == 2)
				{
					*ppItem = pInventoryGrid->ppItems[BODYLOC_LARM];
				}
			}
			else if (nBodyLoc == BODYLOC_LARM)
			{
				if (INVENTORY_GetWieldType(pPlayer, pInventory) == 2)
				{
					*ppItem = pInventoryGrid->ppItems[BODYLOC_RARM];
				}
			}
		}
	}
}

//D2Common.0x6FD8FBB0 (#10256)
BOOL __cdecl INVENTORY_CheckEquipmentForWeaponByClass(struct D2Inventory* pInventory, int nWeaponClass)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);

		struct D2Unit* pItem = pInventoryGrid ? pInventoryGrid->ppItems[BODYLOC_LARM] : nullptr;

		if (ITEMS_CanBeEquipped(pItem) && ITEMS_CheckWeaponClass(pItem, nWeaponClass))
		{
			return TRUE;
		}

		pItem = pInventoryGrid ? pInventoryGrid->ppItems[BODYLOC_RARM] : nullptr;

		if (ITEMS_CanBeEquipped(pItem) && ITEMS_CheckWeaponClass(pItem, nWeaponClass))
		{
			return TRUE;
		}
	}

	return FALSE;
}

//D2Common.0x6FD8FC60 (#10258)
struct D2Unit* __cdecl INVENTORY_GetLeftHandWeapon(struct D2Inventory* pInventory)
{
	if (INVENTORY_GetPtrIfValid(pInventory) && pInventory->dwLeftItemGUID != D2UnitInvalidGUID)
	{
		struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);
		if (pInventoryGrid)
		{
			struct D2Unit* pItem = pInventoryGrid->ppItems[BODYLOC_LARM];
			if (pItem && ITEMS_CheckItemTypeId(pItem, ITEMTYPE_WEAPON) && pItem->dwUnitId == pInventory->dwLeftItemGUID)
			{
				return pItem;
			}

			pItem = pInventoryGrid->ppItems[BODYLOC_RARM];
			if (pItem && ITEMS_CheckItemTypeId(pItem, ITEMTYPE_WEAPON) && pItem->dwUnitId == pInventory->dwLeftItemGUID)
			{
				return pItem;
			}
		}
	}

	return nullptr;
}

//D2Common.0x6FD8FD10 (#11301)
struct D2Unit* __cdecl INVENTORY_GetSecondaryWeapon(struct D2Inventory* pInventory)
{
	if (INVENTORY_GetPtrIfValid(pInventory) && pInventory->dwLeftItemGUID != D2UnitInvalidGUID)
	{
		struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);
		if (pInventoryGrid)
		{
			struct D2Unit* pLeftHandItem = pInventoryGrid->ppItems[BODYLOC_LARM];
			if (!pLeftHandItem || !ITEMS_CheckItemTypeId(pLeftHandItem, ITEMTYPE_WEAPON))
			{
				pLeftHandItem = nullptr;
			}

			struct D2Unit* pRightHandItem = pInventoryGrid->ppItems[BODYLOC_RARM];
			if (!pRightHandItem || !ITEMS_CheckItemTypeId(pRightHandItem, ITEMTYPE_WEAPON))
			{
				pRightHandItem = nullptr;
			}

			if (pLeftHandItem && pLeftHandItem->dwUnitId == pInventory->dwLeftItemGUID)
			{
				return pRightHandItem;
			}

			if (pRightHandItem && pRightHandItem->dwUnitId == pInventory->dwLeftItemGUID)
			{
				return pLeftHandItem;
			}
		}
	}

	return nullptr;
}

//D2Common.0x6FD8FDD0 (#10259)
struct D2Unit* __cdecl INVENTORY_GetCompositItem(struct D2Inventory* pInventory, int nComponent)
{
	if (!INVENTORY_GetPtrIfValid(pInventory))
	{
		return nullptr;
	}

	struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);
	if (pInventoryGrid)
	{
		struct D2Unit* pLeftHandItem = INVENTORY_GetLeftHandWeapon(pInventory);

		for (int i = 0; i < 11; ++i)
		{
			struct D2Unit* pItem = pInventoryGrid->ppItems[i];
			if (pItem)
			{
				const int nWeaponClass = ITEMS_GetWeaponClassId(pInventoryGrid->ppItems[i]);
				if (nWeaponClass == WEAPONCLASS_1HS || nWeaponClass == WEAPONCLASS_1HT || nWeaponClass == WEAPONCLASS_HT1)
				{
					if (nComponent == COMPOSIT_LEFTHAND)
					{
						if (pItem != pLeftHandItem)
						{
							return pItem;
						}
					}
					else if (nComponent == COMPOSIT_RIGHTHAND && pItem == pLeftHandItem)
					{
						return pItem;
					}
				}
				else
				{
					if (ITEMS_GetComponent(pItem) == nComponent)
					{
						return pItem;
					}
				}
			}
		}
	}

	return nullptr;
}

//D2Common.0x6FD8FE80 (#10260)
int __cdecl INVENTORY_GetBodyLocFromEquippedItem(struct D2Inventory* pInventory, struct D2Unit* pItem)
{
	if (INVENTORY_GetPtrIfValid(pInventory) && INVENTORY_UnitIsItem(pItem) && pItem->pStaticPath->tGameCoords.nX < 11)
	{
		return pItem->pStaticPath->tGameCoords.nX;
	}

	return 0;
}

//D2Common.0x6FD8FED0 (#11278)
int __cdecl INVENTORY_GetItemsXPosition(struct D2Inventory* pInventory, struct D2Unit* pItem)
{
	if (INVENTORY_GetPtrIfValid(pInventory) && INVENTORY_UnitIsItem(pItem))
	{
		return pItem->pStaticPath->tGameCoords.nX;
	}

	return 0;
}

//D2Common.0x6FD8FF20 (#10261)
void __cdecl INVENTORY_SetCursorItem(struct D2Inventory* pInventory, struct D2Unit* pItem)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		if (pItem)
		{
			struct D2ItemExtraData* pItemExtraData = INVENTORY_GetItemExtraDataFromItem(pItem);
			if (pItemExtraData)
			{
				pInventory->pCursorItem = pItem;
				pItemExtraData->pParentInv = pInventory;
			}
		}
		else
		{
			INVENTORY_RemoveItem(pInventory->pCursorItem);
		}
	}
}

//D2Common.0x6FD8FF80 (#10262)
struct D2Unit* __cdecl INVENTORY_GetCursorItem(struct D2Inventory* pInventory)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		return pInventory->pCursorItem;
	}

	return nullptr;
}

//D2Common.0x6FD8FFA0 (#10263)
struct D2Unit* __cdecl INVENTORY_FindBackPackItemForStack(struct D2Inventory* pInventory, struct D2Unit* pStackable, struct D2Unit* pCheckItem)
{
	if (!INVENTORY_GetPtrIfValid(pInventory))
	{
		return nullptr;
	}

	struct D2InventoryGrid* pInventoryGrid = nullptr;
	if (pInventory->pOwner && pInventory->pOwner->dwUnitType == UNIT_PLAYER)
	{
		struct D2InventoryGridInfo pInventoryGridInfo = {};
		DATATBLS_GetInventoryGridInfo(UNITS_GetInventoryRecordId(pInventory->pOwner, 0, TRUE), FALSE, &pInventoryGridInfo);
		pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_INVENTORY, &pInventoryGridInfo);
	}
	else
	{
		pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_INVENTORY, nullptr);
	}

	if (!pInventoryGrid)
	{
		return nullptr;
	}

	struct D2Unit* pItem = pInventoryGrid->pItem;
	if (pCheckItem)
	{
		while (pItem)
		{
			if (pItem == pCheckItem)
			{
				break;
			}

			pItem = INVENTORY_GetUnknownItem(pItem);
		}
	}

	while (pItem)
	{
		if (ITEMS_AreStackablesEqual(pItem, pStackable) && STATLIST_UnitGetStatValue(pItem, STAT_QUANTITY, 0) < ITEMS_GetTotalMaxStack(pItem))
		{
			return pItem;
		}

		pItem = INVENTORY_GetUnknownItem(pItem);
	}

	return nullptr;
}

//D2Common.0x6FD90080 (#10264)
struct D2Unit* __cdecl INVENTORY_FindEquippedItemForStack(struct D2Inventory* pInventory, struct D2Unit* pStackable, struct D2Unit* pCheckItem)
{
	if (!INVENTORY_GetPtrIfValid(pInventory))
	{
		return nullptr;
	}

	struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);
	if (!pInventoryGrid)
	{
		return nullptr;
	}

	struct D2Unit* pItem = pInventoryGrid->pItem;
	if (pCheckItem)
	{
		while (pItem)
		{
			if (pItem == pCheckItem)
			{
				break;
			}

			pItem = INVENTORY_GetUnknownItem(pItem);
		}
	}

	while (pItem)
	{
		if (ITEMS_AreStackablesEqual(pItem, pStackable) && STATLIST_UnitGetStatValue(pItem, STAT_QUANTITY, 0) < ITEMS_GetTotalMaxStack(pItem))
		{
			return pItem;
		}

		pItem = INVENTORY_GetUnknownItem(pItem);
	}

	return nullptr;
}

//D2Common.0x6FD90130 (#10265)
struct D2Unit* __cdecl INVENTORY_FindFillableBook(struct D2Inventory* pInventory, struct D2Unit* pScrolls, struct D2Unit* pCheckItem)
{
	if (!INVENTORY_GetPtrIfValid(pInventory))
	{
		return nullptr;
	}

	struct D2InventoryGrid* pInventoryGrid = nullptr;
	if (pInventory->pOwner && pInventory->pOwner->dwUnitType == UNIT_PLAYER)
	{
		struct D2InventoryGridInfo pInventoryGridInfo = {};
		DATATBLS_GetInventoryGridInfo(UNITS_GetInventoryRecordId(pInventory->pOwner, INVPAGE_INVENTORY, TRUE), FALSE, &pInventoryGridInfo);
		pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_INVENTORY, &pInventoryGridInfo);
	}
	else
	{
		pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_INVENTORY, nullptr);
	}

	if (!pInventoryGrid)
	{
		return nullptr;
	}

	struct D2Unit* pItem = pInventoryGrid->pItem;
	if (pCheckItem)
	{
		while (pItem)
		{
			if (pItem == pCheckItem)
			{
				break;
			}

			pItem = INVENTORY_GetUnknownItem(pItem);
		}
	}

	while (pItem)
	{
		if (ITEMS_GetItemType(pItem) == ITEMTYPE_BOOK && ITEMS_GetSuffixId(pItem, 0) == ITEMS_GetSuffixId(pScrolls, 0) && STATLIST_UnitGetStatValue(pItem, STAT_QUANTITY, 0) < ITEMS_GetTotalMaxStack(pItem))
		{
			return pItem;
		}

		pItem = INVENTORY_GetUnknownItem(pItem);
	}

	return nullptr;
}

//D2Common.0x6FD90230 (#10266)
BOOL __cdecl INVENTORY_PlaceItemInBeltSlot(struct D2Inventory* pInventory, struct D2Unit* pItem, int nSlot)
{
	if (INVENTORY_UnitIsItem(pItem) && ITEMS_CheckIfBeltable(pItem))
	{
		uint8_t nHeight = 0;
		uint8_t nWidth = 0;

		ITEMS_GetDimensions(pItem, &nWidth, &nHeight, __FILE__, __LINE__);

		if (nWidth == 1 && nHeight == 1 && pInventory && nSlot >= 0 && nSlot < 16)
		{
			return INVENTORY_PlaceItemInGrid(pInventory, pItem, nSlot, 0, INVGRID_BELT, 0, 0);
		}
	}

	return FALSE;
}

//D2Common.0x6FD902B0 (#10268)
BOOL __cdecl INVENTORY_HasSimilarPotionInBelt(struct D2Inventory* pInventory, struct D2Unit* pPotion)
{
	if (INVENTORY_GetPtrIfValid(pInventory) && INVENTORY_UnitIsItem(pPotion))
	{
		struct D2ItemsTxt* pItemsTxtRecord = DATATBLS_GetItemsTxtRecord(pPotion->dwClassId);
		if (pItemsTxtRecord && pItemsTxtRecord->dwCode != ' csi' && pItemsTxtRecord->dwCode != ' cst')
		{
			struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BELT, &gBeltInventoryGridInfo);
			if (pInventoryGrid)
			{
				for (int i = 0; i < 4; ++i)
				{
					if (pInventoryGrid->ppItems[i] && ITEMS_ComparePotionTypes(pPotion, pInventoryGrid->ppItems[i]))
					{
						return TRUE;
					}
				}
			}
		}
	}
	
	return FALSE;
}

//D2Common.0x6FD90340 (#10269)
BOOL __cdecl INVENTORY_GetFreeBeltSlot(struct D2Inventory* pInventory, struct D2Unit* pItem, int* pFreeSlotId)
{
	if (!INVENTORY_GetPtrIfValid(pInventory) || !INVENTORY_UnitIsItem(pItem) || !ITEMS_CheckIfBeltable(pItem))
	{
		return FALSE;
	}

	uint8_t nHeight = 0;
	uint8_t nWidth = 0;
	ITEMS_GetDimensions(pItem, &nWidth, &nHeight, __FILE__, __LINE__);
	if (nWidth != 1 || nHeight != 1)
	{
		return FALSE;
	}

	struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);
	struct D2Unit* pBelt = nullptr;
	if (pInventoryGrid)
	{
		pBelt = pInventoryGrid->ppItems[BODYLOC_BELT];
	}

	int nBeltType = 2;
	if (pBelt)
	{
		nBeltType = UNITS_GetBeltType(pBelt);
	}

	struct D2BeltsTxt pBeltsTxtRecord = {};
	DATATBLS_GetBeltsTxtRecord(nBeltType, 0, &pBeltsTxtRecord);

	pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BELT, &gBeltInventoryGridInfo);
	if (pInventoryGrid)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (pInventoryGrid->ppItems[i] && ITEMS_ComparePotionTypes(pItem, pInventoryGrid->ppItems[i]))
			{
				for (int nId = i; nId < pBeltsTxtRecord.nBoxes; nId += 4)
				{
					if (!pInventoryGrid->ppItems[nId])
					{
						*pFreeSlotId = nId;
						return TRUE;
					}
				}
			}
		}

		struct D2ItemsTxt* pItemsTxtRecord = DATATBLS_GetItemsTxtRecord(pItem->dwClassId);
		if (!pItemsTxtRecord || !pItemsTxtRecord->nAutoBelt)
		{
			return FALSE;
		}

		for (int i = 0; i < 4; ++i)
		{
			if (!pInventoryGrid->ppItems[i])
			{
				*pFreeSlotId = i;
				return TRUE;
			}
		}
	}

	return FALSE;
}

//D2Common.0x6FD904F0 (#10270)
BOOL __cdecl INVENTORY_PlaceItemInFreeBeltSlot(struct D2Inventory* pInventory, struct D2Unit* pItem)
{
	int nFreeSlot = 0;
	if (INVENTORY_GetFreeBeltSlot(pInventory, pItem, &nFreeSlot) && pInventory && INVENTORY_UnitIsItem(pItem) && nFreeSlot >= 0 && nFreeSlot < 16)
	{
		return INVENTORY_PlaceItemInGrid(pInventory, pItem, nFreeSlot, 0, INVGRID_BELT, 0, 0);
	}

	return FALSE;
}

//D2Common.0x6FD90550 (#10271)
struct D2Unit* __cdecl INVENTORY_GetItemFromBeltSlot(struct D2Inventory* pInventory, int nSlotId)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BELT, &gBeltInventoryGridInfo);
		if (pInventoryGrid && nSlotId >= 0 && nSlotId < 16)
		{
			return pInventoryGrid->ppItems[nSlotId];
		}
	}

	return nullptr;
}

//D2Common.0x6FD90590 (#10272)
BOOL __cdecl INVENTORY_GetUseableItemFromBeltSlot(struct D2Inventory* pInventory, struct D2Unit* pItem, int nSlotId, struct D2Unit** ppItem)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BELT, &gBeltInventoryGridInfo);
		if (pInventoryGrid && INVENTORY_UnitIsItem(pItem) && ITEMS_CheckIfBeltable(pItem))
		{
			uint8_t nHeight = 0;
			uint8_t nWidth = 0;
			ITEMS_GetDimensions(pItem, &nWidth, &nHeight, __FILE__, __LINE__);

			if (nWidth == 1 && nHeight == 1)
			{
				struct D2ItemsTxt* pItemsTxtRecord = DATATBLS_GetItemsTxtRecord(pItem->dwClassId);
				if (pItemsTxtRecord && pItemsTxtRecord->nUseable == 1 && pItemsTxtRecord->nBelt == 1)
				{
					if (nSlotId >= 0 && nSlotId < 16)
					{
						*ppItem = pInventoryGrid->ppItems[nSlotId];
					}
					else
					{
						*ppItem = nullptr;
					}

					return TRUE;
				}
			}
		}
	}

	return FALSE;
}

//D2Common.0x6FD90690 (#10273)
BOOL __cdecl INVENTORY_GetEquippedShield(struct D2Inventory* pInventory, struct D2Unit** ppItem)
{
	if (!INVENTORY_GetPtrIfValid(pInventory))
	{
		return FALSE;
	}

	if (ppItem)
	{
		*ppItem = nullptr;
	}

	struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);
	struct D2Unit* pItem = nullptr;
	if (pInventoryGrid)
	{
		pItem = pInventoryGrid->ppItems[BODYLOC_RARM];
	}
	else
	{
		pItem = nullptr;
	}

	if (ITEMS_CanBeEquipped(pItem) && ITEMS_CheckItemTypeId(pItem, ITEMTYPE_ANY_SHIELD))
	{
		if (ppItem)
		{
			*ppItem = pItem;
		}
		return TRUE;
	}

	if (pInventoryGrid)
	{
		pItem = pInventoryGrid->ppItems[BODYLOC_LARM];
	}
	else
	{
		pItem = nullptr;
	}

	if (ITEMS_CanBeEquipped(pItem) && ITEMS_CheckItemTypeId(pItem, ITEMTYPE_ANY_SHIELD))
	{
		if (ppItem)
		{
			*ppItem = pItem;
		}
		return TRUE;
	}

	return FALSE;
}

//D2Common.0x6FD90760 (#10274)
BOOL __cdecl INVENTORY_GetEquippedWeapon(struct D2Inventory* pInventory, struct D2Unit** ppItem, int* pBodyLoc, BOOL* pIsLeftHandItem)
{
	if (!INVENTORY_GetPtrIfValid(pInventory))
	{
		*ppItem = nullptr;
		return FALSE;
	}

	*pIsLeftHandItem = FALSE;

	struct D2Unit* pLeftHandItem = INVENTORY_GetLeftHandWeapon(pInventory);

	struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);

	struct D2Unit* pItem = pInventoryGrid ? pInventoryGrid->ppItems[BODYLOC_RARM] : nullptr;

	if (ITEMS_CanBeEquipped(pItem) && ITEMS_CheckItemTypeId(pItem, ITEMTYPE_WEAPON))
	{
		*ppItem = pItem;
		*pBodyLoc = BODYLOC_RARM;

		if (pItem == pLeftHandItem)
		{
			*pIsLeftHandItem = TRUE;
		}

		return TRUE;
	}
	else
	{
		pItem = pInventoryGrid ? pInventoryGrid->ppItems[BODYLOC_LARM] : nullptr;

		if (ITEMS_CanBeEquipped(pItem) && ITEMS_CheckItemTypeId(pItem, ITEMTYPE_WEAPON))
		{
			*ppItem = pItem;
			*pBodyLoc = BODYLOC_LARM;

			if (pItem == pLeftHandItem)
			{
				*pIsLeftHandItem = TRUE;
			}

			return TRUE;
		}
	}

	*ppItem = nullptr;
	return FALSE;
}

//D2Common.0x6FD90850 (#10275)
BOOL __cdecl INVENTORY_HasBodyArmorEquipped(struct D2Inventory* pInventory)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);
		if (pInventoryGrid && pInventoryGrid->ppItems[BODYLOC_TORSO])
		{
			return ITEMS_CheckItemTypeId(pInventoryGrid->ppItems[BODYLOC_TORSO], ITEMTYPE_ARMOR) != 0;
		}
	}

	return FALSE;
}

//D2Common.0x6FD908A0 (#10276)
BOOL __cdecl INVENTORY_IsItemBodyLocFree(struct D2Inventory* pInventory, struct D2Unit* pItem, int nBodyLoc, int nInventoryRecordId)
{
	if (INVENTORY_GetPtrIfValid(pInventory) && INVENTORY_ValidateBodyLoc(nBodyLoc))
	{
		struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);

		if (pInventoryGrid && pInventoryGrid->ppItems[nBodyLoc] && pItem)
		{
			int nFreeX = 0;
			int nFreeY = 0;
			return INVENTORY_GetFreePosition(pInventory, pInventoryGrid->ppItems[nBodyLoc], nInventoryRecordId, &nFreeX, &nFreeY, 0) != 0;
		}
	}

	return FALSE;
}

//D2Common.0x6FD90910 (#10279)
void __cdecl INVENTORY_RemoveInventoryItems(struct D2Inventory* pInventory)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		for (struct D2Unit* pItem = pInventory->pFirstItem; pItem; pItem = pInventory->pFirstItem)
		{
			INVENTORY_RemoveItem(pItem);
		}
	}
}

//D2Common.0x6FD90940 (#10280)
struct D2InventoryNode* __cdecl INVENTORY_GetTradeInventory(struct D2Inventory* pInventory)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		return pInventory->pFirstNode;
	}

	return nullptr;
}

//D2Common.0x6FD90960 (#10281)
void __cdecl INVENTORY_FreeTradeInventory(struct D2Inventory* pInventory)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		struct D2InventoryNode* pNextNode = nullptr;
		for (struct D2InventoryNode* pNode = pInventory->pFirstNode; pNode; pNode = pNextNode)
		{
			pNextNode = pNode->pNext;
			D2_FREE_POOL(pInventory->pMemPool, pNode);
		}

		pInventory->pFirstNode = nullptr;
		pInventory->pLastNode = nullptr;
	}
}

//D2Common.0x6FD909B0 (#10282)
BOOL __cdecl INVENTORY_CheckForItemInTradeInventory(struct D2Inventory* pInventory, int nItemId)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		for (struct D2InventoryNode* pNode = pInventory->pFirstNode; pNode; pNode = pNode->pNext)
		{
			if (pNode->nItemId == nItemId)
			{
				return TRUE;
			}
		}
	}
	
	return FALSE;
}

//D2Common.0x6FD909F0 (#10283)
void __cdecl INVENTORY_AddItemToTradeInventory(struct D2Inventory* pInventory, struct D2Unit* pItem)
{
	if (INVENTORY_UnitIsItem(pItem))
	{
		if (INVENTORY_CheckForItemInTradeInventory(pInventory, pItem->dwUnitId))
		{
			return;
		}

		struct D2InventoryNode* pNode = D2_ALLOC_STRC_POOL(pInventory->pMemPool, struct D2InventoryNode);
		D2_ASSERT(pNode);

		pNode->pNext = nullptr;
		pNode->nItemId = pItem->dwUnitId;

		if (pInventory->pFirstNode)
		{
			pInventory->pLastNode->pNext = pNode;
		}
		else
		{
			pInventory->pFirstNode = pNode;
		}

		pInventory->pLastNode = pNode;
	}
}

//D2Common.0x6FD90AB0 (#10316)
//TODO: Find a name
int __cdecl D2Common_10316(struct D2Corpse* pCorpse)
{
	if (pCorpse)
	{
		return pCorpse->unk0x00;
	}

	REMOVE_LATER_Trace("D2Common_10316: nullptr pointer");
	return 0;
}

//D2Common.0x6FD90AC0 (#10284)
int __cdecl INVENTORY_GetItemCount(struct D2Inventory* pInventory)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		return pInventory->dwItemCount;
	}

	return 0;
}

//D2Common.0x6FD90AE0 (#10285)
struct D2Unit* __cdecl INVENTORY_GetBackPackItemByType(struct D2Inventory* pInventory, int nItemType, struct D2Unit* pCheckItem)
{
	if (!INVENTORY_GetPtrIfValid(pInventory))
	{
		return nullptr;
	}

	struct D2InventoryGrid* pInventoryGrid = nullptr;
	if (pInventory->pOwner && pInventory->pOwner->dwUnitType == UNIT_PLAYER)
	{
		struct D2InventoryGridInfo pInventoryGridInfo = {};
		DATATBLS_GetInventoryGridInfo(UNITS_GetInventoryRecordId(pInventory->pOwner, 0, 1), 0, &pInventoryGridInfo);
		pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_INVENTORY, &pInventoryGridInfo);
	}
	else
	{
		pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_INVENTORY, nullptr);
	}
	
	if (!pInventoryGrid)
	{
		return nullptr;
	}

	struct D2Unit* pItem = pInventoryGrid->pItem;
	if (pCheckItem)
	{
		while (pItem)
		{
			if (pItem == pCheckItem)
			{
				break;
			}

			pItem = INVENTORY_GetUnknownItem(pItem);
		}

		pItem = INVENTORY_GetUnknownItem(pItem);
	}

	while (pItem)
	{
		if (ITEMS_CheckItemTypeId(pItem, nItemType))
		{
			return pItem;
		}

		pItem = INVENTORY_GetUnknownItem(pItem);
	}

	return nullptr;
}

//D2Common.0x6FD90BC0 (#10286)
struct D2Unit* __cdecl INVENTORY_GetEquippedItemByType(struct D2Inventory* pInventory, int nItemType, struct D2Unit* pCheckItem)
{
	if (!INVENTORY_GetPtrIfValid(pInventory))
	{
		return nullptr;
	}

	struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);
	if (!pInventoryGrid)
	{
		return nullptr;
	}

	struct D2Unit* pItem = pInventoryGrid->pItem;
	if (pCheckItem)
	{
		while (pItem)
		{
			if (pItem == pCheckItem)
			{
				break;
			}

			pItem = INVENTORY_GetUnknownItem(pItem);
		}
	}

	while (pItem)
	{
		if (ITEMS_CheckItemTypeId(pItem, nItemType) && UNITS_GetXPosition(pItem) < 11)
		{
			return pItem;
		}

		pItem = INVENTORY_GetUnknownItem(pItem);
	}

	return nullptr;
}

//D2Common.0x6FD90C80 (#10287)
struct D2Unit* __cdecl INVENTORY_GetEquippedItemByCode(struct D2Inventory* pInventory, int nItemCode, struct D2Unit* pCheckItem)
{
	int nClassId = 0;
	if (!INVENTORY_GetPtrIfValid(pInventory) || !DATATBLS_GetItemRecordFromItemCode(nItemCode, &nClassId))
	{
		return nullptr;
	}

	struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);
	if (!pInventoryGrid)
	{
		return nullptr;
	}

	struct D2Unit* pItem = pInventoryGrid->pItem;
	if (pCheckItem)
	{
		while (pItem)
		{
			if (pItem == pCheckItem)
			{
				break;
			}

			pItem = INVENTORY_GetUnknownItem(pItem);
		}
	}

	while (pItem)
	{
		if (pItem->dwClassId == nClassId && UNITS_GetXPosition(pItem) < 11)
		{
			return pItem;
		}

		pItem = INVENTORY_GetUnknownItem(pItem);
	}

	return nullptr;
}

//D2Common.0x6FD90D50 (#11306)
struct D2Unit* __cdecl INVENTORY_GetBackPackItemByCode(struct D2Inventory* pInventory, int nItemCode, struct D2Unit* pCheckItem)
{
	int nClassId = 0;
	if (!INVENTORY_GetPtrIfValid(pInventory) || !DATATBLS_GetItemRecordFromItemCode(nItemCode, &nClassId))
	{
		return nullptr;
	}
	
	struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_INVENTORY, &gBodyLocInventoryGridInfo);
	if (!pInventoryGrid)
	{
		return nullptr;
	}

	struct D2Unit* pItem = pInventoryGrid->pItem;
	if (pCheckItem)
	{
		while (pItem)
		{
			if (pItem == pCheckItem)
			{
				break;
			}

			pItem = INVENTORY_GetUnknownItem(pItem);
		}
	}

	while (pItem)
	{
		if (pItem->dwClassId == nClassId && UNITS_GetXPosition(pItem) < 11)
		{
			return pItem;
		}

		pItem = INVENTORY_GetUnknownItem(pItem);
	}

	return nullptr;
}

//D2Common.0x6FD90E20 (#10288)
int __cdecl INVENTORY_GetSetItemEquipCountByFileIndex(struct D2Inventory* pInventory, int nItemFileIndex)
{
	if (!INVENTORY_GetPtrIfValid(pInventory))
	{
		return 0;
	}

	struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);
	if (pInventoryGrid)
	{
		int nCounter = 0;
		for (struct D2Unit* pItem = pInventoryGrid->pItem; ITEMS_GetItemData(pItem) != nullptr; pItem = pItem->pItemData->pExtraData.unk0x14)
		{
			if (ITEMS_GetItemQuality(pItem) == ITEMQUAL_SET && ITEMS_GetFileIndex(pItem) == nItemFileIndex)
			{
				if (pItem->pStaticPath->tGameCoords.nX < 11)
				{
					++nCounter;
				}
			}
		}

		return nCounter;
	}

	return 0;
}

//D2Common.0x6FD90ED0 (#10289)
void __cdecl INVENTORY_UpdateWeaponGUIDOnInsert(struct D2Inventory* pInventory, struct D2Unit* pItem)
{
	if (pInventory && INVENTORY_UnitIsItem(pItem) && ITEMS_CheckItemTypeId(pItem, ITEMTYPE_WEAPON))
	{
		if (ITEMS_GetBodyLocation(pItem) == BODYLOC_RARM || ITEMS_GetBodyLocation(pItem) == BODYLOC_LARM)
		{
			if (ITEMS_CanBeEquipped(pItem))
			{
				struct D2Unit* pWeapon = INVENTORY_GetLeftHandWeapon(pInventory);
				if (!pWeapon || !ITEMS_CheckItemTypeId(pWeapon, ITEMTYPE_WEAPON) || ITEMS_CheckItemTypeId(pWeapon, ITEMTYPE_MISSILE_POTION))
				{
					if (INVENTORY_CheckSignature(pInventory))
					{
						pInventory->dwLeftItemGUID = pItem->dwUnitId;
					}
					return;
				}
			}
			
			if (INVENTORY_CheckSignature(pInventory) && pInventory->dwLeftItemGUID == pItem->dwUnitId)
			{
				pInventory->dwLeftItemGUID = D2UnitInvalidGUID;
			}
		}
	}
}

//D2Common.0x6FD90F80 (#10290)
void __cdecl INVENTORY_UpdateWeaponGUIDOnRemoval(struct D2Inventory* pInventory, struct D2Unit* pItem)
{
	if (INVENTORY_GetPtrIfValid(pInventory) && INVENTORY_UnitIsItem(pItem) && ITEMS_CheckItemTypeId(pItem, ITEMTYPE_WEAPON))
	{
		if (pInventory->dwLeftItemGUID == pItem->dwUnitId)
		{
			pInventory->dwLeftItemGUID = D2UnitInvalidGUID;
		}

		struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);
		if (pInventoryGrid)
		{
			const int nBodyLoc = ITEMS_GetBodyLocation(pItem);
			struct D2Unit* pWeapon = nullptr;
			if (nBodyLoc == BODYLOC_RARM)
			{
				pWeapon = pInventoryGrid->ppItems[BODYLOC_LARM];
			}
			else if (nBodyLoc == BODYLOC_LARM)
			{
				pWeapon = pInventoryGrid->ppItems[BODYLOC_RARM];
			}
			else
			{
				return;
			}

			if (pWeapon && ITEMS_CanBeEquipped(pWeapon) && pWeapon->dwUnitType == UNIT_ITEM)
			{
				pInventory->dwLeftItemGUID = pWeapon->dwUnitId;
			}
		}
	}
}

//D2Common.0x6FD91050 (#10291)
int __cdecl INVENTORY_GetWieldType(struct D2Unit* pPlayer, struct D2Inventory* pInventory)
{
	if (pInventory)
	{
		struct D2Unit* pRightHandItem = nullptr;
		struct D2Unit* pLeftHandItem = nullptr;

		if (INVENTORY_CheckSignature(pInventory))
		{
			struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);
			if (pInventoryGrid)
			{
				pLeftHandItem = pInventoryGrid->ppItems[BODYLOC_LARM];
				pRightHandItem = pInventoryGrid->ppItems[BODYLOC_RARM];
			}
		}

		if (!pLeftHandItem)
		{
			if (!pRightHandItem)
			{
				return -1;
			}

			if (ITEMS_CheckWeaponIfTwoHanded(pRightHandItem))
			{
				return 2;
			}

			if (ITEMS_Is1Or2Handed(pPlayer, pRightHandItem))
			{
				return 2;
			}
			else
			{
				return -1;
			}
		}

		if (!pRightHandItem)
		{
			if (ITEMS_CheckWeaponIfTwoHanded(pLeftHandItem))
			{
				return 2;
			}

			if (ITEMS_Is1Or2Handed(pPlayer, pLeftHandItem))
			{
				return 2;
			}
			else
			{
				return -1;
			}
		}

		if (ITEMS_Is1Or2Handed(pPlayer, pLeftHandItem) || ITEMS_Is1Or2Handed(pPlayer, pRightHandItem))
		{
			return 1;
		}

		if (ITEMS_CheckWeaponIfTwoHanded(pLeftHandItem))
		{
			return 2;
		}

		if (ITEMS_CheckWeaponIfTwoHanded(pRightHandItem))
		{
			return 2;
		}
		else
		{
			return -1;
		}
	}

	return -1;
}

//D2Common.0x6FD91140 (#10292)
void __cdecl INVENTORY_SetOwnerId(struct D2Inventory* pInventory, D2UnitGUID nOwnerGuid)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		pInventory->dwOwnerGuid = nOwnerGuid;
	}
}

//D2Common.0x6FD91160 (#10293)
int __cdecl INVENTORY_GetOwnerId(struct D2Inventory* pInventory)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		return pInventory->dwOwnerGuid;
	}

	return -1;
}

//D2Common.0x6FD91190 (#10294)
void __cdecl INVENTORY_CreateCorpseForPlayer(struct D2Inventory* pInventory, int nUnitId, int a3, int a4)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		struct D2Corpse* pCorpse = D2_ALLOC_STRC_POOL(pInventory->pMemPool, struct D2Corpse);
		pCorpse->unk0x00 = a4;
		pCorpse->dwUnitId = nUnitId;
		pCorpse->unk0x08 = a3;
		pCorpse->pNextCorpse = nullptr;

		if (pInventory->pFirstCorpse)
		{
			pInventory->pLastCorpse->pNextCorpse = pCorpse;
		}
		else
		{
			pInventory->pFirstCorpse = pCorpse;
		}

		pInventory->pLastCorpse = pCorpse;

		if (pCorpse->unk0x00)
		{
			++pInventory->nCorpseCount;
		}
	}
}

//D2Common.0x6FD91210 (#10295)
BOOL __cdecl INVENTORY_FreeCorpse(struct D2Inventory* pInventory, int nUnitId, int a3)
{
	if (INVENTORY_GetPtrIfValid(pInventory) && pInventory->pFirstCorpse)
	{
		struct D2Corpse* pPreviousCorpse = nullptr;
		struct D2Corpse* pCorpse = pInventory->pFirstCorpse;
		while (pCorpse->dwUnitId != nUnitId || pCorpse->unk0x00 != a3)
		{
			pPreviousCorpse = pCorpse;

			pCorpse = pCorpse->pNextCorpse;
			if (!pCorpse)
			{
				return FALSE;
			}
		}

		if (pPreviousCorpse)
		{
			pPreviousCorpse->pNextCorpse = pCorpse->pNextCorpse;
			if (!pCorpse->pNextCorpse)
			{
				pInventory->pLastCorpse = pPreviousCorpse;
			}
		}
		else
		{
			pInventory->pFirstCorpse = pCorpse->pNextCorpse;
			if (!pCorpse->pNextCorpse)
			{
				pInventory->pLastCorpse = nullptr;
			}
		}

		if (pCorpse->unk0x00)
		{
			--pInventory->nCorpseCount;
		}

		D2_FREE_POOL(pInventory->pMemPool, pCorpse);
		return TRUE;
	}
	
	return FALSE;
}

//D2Common.0x6FD91290 (#10296)
struct D2Corpse* __cdecl INVENTORY_GetFirstCorpse(struct D2Inventory* pInventory)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		return pInventory->pFirstCorpse;
	}

	return nullptr;
}

//D2Common.0x6FD912B0 (#10297)
int __cdecl INVENTORY_GetCorpseCount(struct D2Inventory* pInventory)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		return pInventory->nCorpseCount;
	}

	return 0;
}

//D2Common.0x6FD912D0 (#10313)
struct D2Corpse* __cdecl INVENTORY_GetNextCorpse(struct D2Corpse* pCorpse)
{
	if (pCorpse)
	{
		return pCorpse->pNextCorpse;
	}

	REMOVE_LATER_Trace("INVENTORY_GetNextCorpse: nullptr pointer");
	return nullptr;
}

//D2Common.0x6FDAFEA0 (#10314)
D2UnitGUID __cdecl INVENTORY_GetUnitGUIDFromCorpse(struct D2Corpse* pCorpse)
{
	if (pCorpse)
	{
		return pCorpse->dwUnitId;
	}

	REMOVE_LATER_Trace("INVENTORY_GetUnitGUIDFromCorpse: nullptr pointer");
	return 0;
}

//D2Common.0x6FDB18D0 (#10315)
//TODO: Find a name
int __cdecl D2Common_10315(struct D2Corpse* pCorpse)
{
	if (pCorpse)
	{
		return pCorpse->unk0x08; // Used as merc name id?
	}

	return 0;
}

// Helper function
inline int INVENTORY_GetComponentArrayIndexFromItemsTxtRecord(struct D2ItemsTxt* pItemsTxtRecord)
{
	for (int nCounter = 1; nCounter < ARRAY_SIZE(gTxtComponentItemTypeMap); ++nCounter)
	{
		if (gTxtComponentItemTypeMap[nCounter].dwCode == pItemsTxtRecord->dwAlternateGfx || gTxtComponentItemTypeMap[nCounter].dwCode == pItemsTxtRecord->dwCode)
		{
			return nCounter;
		}
	}

	return ARRAY_SIZE(gTxtComponentItemTypeMap);
}

// Helper function
inline int INVENTORY_GetComponentArrayIndexFromArmTypeTxtRecord(struct D2ArmTypeTxt* pArmTypeTxtRecord)
{
	for (int nCounter = 1; nCounter < ARRAY_SIZE(gTxtComponentItemTypeMap); ++nCounter)
	{
		if (gTxtComponentItemTypeMap[nCounter].dwCode == *(uint32_t*)&pArmTypeTxtRecord->szToken[0])
		{
			return nCounter;
		}
	}

	return ARRAY_SIZE(gTxtComponentItemTypeMap);
}

//D2Common.0x6FD912F0 (#10298)
void __cdecl INVENTORY_GetItemSaveGfxInfo(struct D2Unit* pPlayer, uint8_t* pComponents, uint8_t* pColor)
{
	for (struct D2Unit* pItem = INVENTORY_GetFirstItem(pPlayer->pInventory); pItem; pItem = INVENTORY_GetNextItem(pItem))
	{
		if (pItem->dwUnitType == UNIT_ITEM && pItem->dwAnimMode == IMODE_EQUIP)
		{
			struct D2ItemsTxt* pItemsTxtRecord = DATATBLS_GetItemsTxtRecord(pItem->dwClassId);
			D2_ASSERT(pItemsTxtRecord);

			const uint8_t nBodyLoc = ITEMS_GetBodyLocation(pItem);
			if (nBodyLoc == BODYLOC_HEAD || nBodyLoc == BODYLOC_RARM || nBodyLoc == BODYLOC_LARM)
			{
				if (!ITEMS_CheckType(pItemsTxtRecord->wType[0], ITEMTYPE_CIRCLET) && pPlayer->pInventory)
				{
					struct D2Unit* pRightHandItem = INVENTORY_GetCompositItem(pPlayer->pInventory, COMPOSIT_RIGHTHAND);
					struct D2Unit* pLeftHandItem = INVENTORY_GetCompositItem(pPlayer->pInventory, COMPOSIT_LEFTHAND);

					uint8_t nComponent = ITEMS_GetComponent(pItem);

					INVENTORY_InitializeComponentArray();

					const int nIndex = INVENTORY_GetComponentArrayIndexFromItemsTxtRecord(pItemsTxtRecord);

					if (nIndex >= ARRAY_SIZE(gTxtComponentItemTypeMap))
					{
						if (nComponent < NUM_COMPONENTS)
						{
							pComponents[nComponent] = -1;
							pColor[nComponent] = -1;
						}
					}
					else
					{
						if (pItem == pRightHandItem)
						{
							nComponent = COMPOSIT_RIGHTHAND;
						}
						else if (pItem == pLeftHandItem)
						{
							nComponent = COMPOSIT_LEFTHAND;
						}
						if (nComponent < NUM_COMPONENTS)
						{
							pComponents[nComponent] = nIndex;

							sub_6FD917B0(pPlayer, pComponents, pColor, pItem);

							uint8_t* pComponentColor = &pColor[nComponent];
							if (ITEMS_GetColor(pPlayer, pItem, pComponentColor, 0))
							{
								++*pComponentColor;
							}
							else
							{
								*pComponentColor = -1;
							}
						}
					}
				}
			}
			else if (nBodyLoc == BODYLOC_TORSO)
			{
				uint8_t pArmorComponents[6] = {};
				for(int i = 0; i < 6; ++i)
				{
					pArmorComponents[i] = pItemsTxtRecord->nArmorComp[i];
				}

				for (int i = 0; i < NUM_COMPONENTS; ++i)
				{
					if (COMPOSIT_IsArmorComponent(i))
					{
						struct D2ArmTypeTxt* pArmTypeTxtRecord = DATATBLS_GetArmTypeTxtRecord(COMPOSIT_GetArmorTypeFromComponent(i, pArmorComponents));
						if (pItem->dwClassId > 0)
						{
							INVENTORY_InitializeComponentArray();

							const int nIndex = INVENTORY_GetComponentArrayIndexFromArmTypeTxtRecord(pArmTypeTxtRecord);

							if (nIndex < ARRAY_SIZE(gTxtComponentItemTypeMap))
							{
								pComponents[i] = nIndex;

								uint8_t* pComponentColor = &pColor[i];
								if (ITEMS_GetColor(pPlayer, pItem, pComponentColor, 0))
								{
									++*pComponentColor;
								}
								else
								{
									*pComponentColor = -1;
								}
							}
							else
							{
								pComponents[i] = -1;
								pColor[i] = -1;
							}
						}
						else
						{
							pComponents[i] = -1;
							pColor[i] = -1;
						}
					}
				}
			}
		}
	}
}

//D2Common.0x6FD915C0
void __cdecl INVENTORY_InitializeComponentArray()
{
	if (!gbComponentArrayInitialized)
	{
		gbComponentArrayInitialized = TRUE;

		memset(gTxtComponentItemTypeMap, 0x00, sizeof(gTxtComponentItemTypeMap));

		gTxtComponentItemTypeMap[1].dwCode = ' til';
		gTxtComponentItemTypeMap[1].nItemType = ITEMTYPE_ARMOR;
		gTxtComponentItemTypeMap[2].dwCode = ' dem';
		gTxtComponentItemTypeMap[2].nItemType = ITEMTYPE_ARMOR;
		gTxtComponentItemTypeMap[3].dwCode = ' yvh';
		gTxtComponentItemTypeMap[3].nItemType = ITEMTYPE_ARMOR;

		struct D2ItemDataTbl* pItemDataTbl = DATATBLS_GetItemDataTables();

		int nCurrentTableEntries = 4;

		for (int i = 0; i < pItemDataTbl->nItemsTxtRecordCount; ++i)
		{
			struct D2ItemsTxt* pItemsTxtRecord = &pItemDataTbl->pItemsTxt[i];

			int dwCode = 0;
			if (pItemsTxtRecord->dwAlternateGfx)
			{
				dwCode = pItemsTxtRecord->dwAlternateGfx;
			}
			else
			{
				dwCode = pItemsTxtRecord->dwCode;
			}

			BOOL bNeedsToBeAdded = FALSE;
			if (ITEMS_CheckType(pItemsTxtRecord->wType[0], ITEMTYPE_WEAPON)
				|| ITEMS_CheckType(pItemsTxtRecord->wType[0], ITEMTYPE_ARMOR)
				|| ITEMS_CheckType(pItemsTxtRecord->wType[0], ITEMTYPE_ANY_SHIELD)
				|| ITEMS_CheckType(pItemsTxtRecord->wType[0], ITEMTYPE_HELM) && !ITEMS_CheckType(pItemsTxtRecord->wType[0], ITEMTYPE_CIRCLET))
			{
				bNeedsToBeAdded = TRUE;
			}

			int nCounter = 0;
			while (nCounter < nCurrentTableEntries)
			{
				if (gTxtComponentItemTypeMap[nCounter].dwCode == dwCode)
				{
					break;
				}

				++nCounter;
			}

			if (nCounter >= nCurrentTableEntries && bNeedsToBeAdded == 1)
			{
				int nIndex = nCurrentTableEntries;

				while (ITEMS_CheckType(gComponentItemTypeMap[nIndex].nItemType, ITEMTYPE_WEAPON) && ITEMS_CheckType(pItemsTxtRecord->wType[0], ITEMTYPE_WEAPON)
					   || ITEMS_CheckType(gComponentItemTypeMap[nIndex].nItemType, ITEMTYPE_ANY_ARMOR) && ITEMS_CheckType(pItemsTxtRecord->wType[0], ITEMTYPE_ANY_ARMOR)
					   || gTxtComponentItemTypeMap[nIndex].dwCode)
				{
					++nIndex;
				}

				if (nIndex >= ARRAY_SIZE(gTxtComponentItemTypeMap))
				{
					nIndex = nCurrentTableEntries;
				}

				gTxtComponentItemTypeMap[nIndex].dwCode = dwCode;
				gTxtComponentItemTypeMap[nIndex].nItemType = pItemsTxtRecord->wType[0];

				if (nCurrentTableEntries == nIndex)
				{
					++nCurrentTableEntries;
				}
			}
		}

		gnComponentArrayRecordCount = ARRAY_SIZE(gTxtComponentItemTypeMap);
	}
}

//D2Common.0x6FD917B0
//TODO: Find a name
void __cdecl sub_6FD917B0(struct D2Unit* pUnit, uint8_t* a2, uint8_t* pColor, struct D2Unit* pItem)
{
	D2_ASSERT(pUnit);
	D2_ASSERT(pItem);

	const uint8_t nBodyLoc = ITEMS_GetBodyLocation(pItem);
	if (nBodyLoc == BODYLOC_RARM || nBodyLoc == BODYLOC_LARM)
	{
		int nWeaponClass = 0;
		const uint32_t dwWeaponClassCode = COMPOSIT_GetWeaponClassId(pUnit, pUnit->pInventory, &nWeaponClass, -1, 1);
		const uint8_t nComponent = ITEMS_GetComponent(pItem);

		if (dwWeaponClassCode == ' wbx')
		{
			if ((nComponent == COMPOSIT_RIGHTHAND || nComponent == COMPOSIT_LEFTHAND) && pUnit->pInventory)
			{
				struct D2Unit* pCompositItem = INVENTORY_GetCompositItem(pUnit->pInventory, COMPOSIT_RIGHTHAND);
				if (pCompositItem)
				{
					struct D2ItemsTxt* pItemsTxtRecord = DATATBLS_GetItemsTxtRecord(pCompositItem->dwClassId);
					D2_ASSERT(pItemsTxtRecord);

					INVENTORY_InitializeComponentArray();

					const int nIndex = INVENTORY_GetComponentArrayIndexFromItemsTxtRecord(pItemsTxtRecord);

					if (nIndex >= ARRAY_SIZE(gTxtComponentItemTypeMap))
					{
						a2[COMPOSIT_LEFTHAND] = -1;
						pColor[COMPOSIT_LEFTHAND] = -1;
					}
					else
					{
						a2[COMPOSIT_LEFTHAND] = nIndex;
					}
				}
			}
		}
		else if(dwWeaponClassCode == ' wob')
		{
			if (nComponent == COMPOSIT_LEFTHAND)
			{
				int nItemId = 0;
				struct D2ItemsTxt* pItemsTxtRecord = DATATBLS_GetItemRecordFromItemCode('til\0', &nItemId);
				if (pItemsTxtRecord)
				{
					INVENTORY_InitializeComponentArray();

					const int nIndex = INVENTORY_GetComponentArrayIndexFromItemsTxtRecord(pItemsTxtRecord);

					if (nIndex >= ARRAY_SIZE(gTxtComponentItemTypeMap))
					{
						a2[COMPOSIT_RIGHTHAND] = -1;
						pColor[COMPOSIT_RIGHTHAND] = -1;
					}
					else
					{
						a2[COMPOSIT_RIGHTHAND] = nIndex;
					}
				}
			}
		}
	}
}

//D2Common.0x6FD91B60 (#10299)
//TODO: Find a name
int __cdecl D2Common_10299(struct D2Unit* pUnit, int nBodyLoc, struct D2Unit* pItem, BOOL bDontCheckReqs)
{
	if (pUnit && pUnit->pInventory)
	{
		if (!pItem || ITEMS_CheckBodyLocation(pItem, nBodyLoc) && (bDontCheckReqs || ITEMS_CheckRequirements(pItem, pUnit, TRUE, nullptr, nullptr, nullptr)))
		{
			struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pUnit->pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);

			struct D2Unit* pItem1 = nullptr;
			struct D2Unit* pItem2 = nullptr;
			int nOtherBodyLoc = 0;

			switch (nBodyLoc)
			{
			case BODYLOC_NONE:
			{
				return 0;
			}
			case BODYLOC_RARM:
			case BODYLOC_LARM:
			{
				if (nBodyLoc != BODYLOC_LARM)
				{
					nOtherBodyLoc = BODYLOC_LARM;
				}
				else
				{
					nOtherBodyLoc = BODYLOC_RARM;
				}

				if (INVENTORY_CheckSignature(pUnit->pInventory) && INVENTORY_ValidateBodyLoc(nBodyLoc) && pInventoryGrid)
				{
					pItem1 = pInventoryGrid->ppItems[nBodyLoc];
				}

				if (INVENTORY_CheckSignature(pUnit->pInventory) && INVENTORY_ValidateBodyLoc(nOtherBodyLoc) && pInventoryGrid)
				{
					pItem2 = pInventoryGrid->ppItems[nOtherBodyLoc];
				}

				return sub_6FD91D50(pUnit, nBodyLoc, nOtherBodyLoc, pItem, pItem1, pItem2, bDontCheckReqs);
			}
			case BODYLOC_SWRARM:
			case BODYLOC_SWLARM:
			{
				if (nBodyLoc != BODYLOC_SWLARM)
				{
					nOtherBodyLoc = BODYLOC_SWLARM;
				}
				else
				{
					nOtherBodyLoc = BODYLOC_SWRARM;
				}

				if (INVENTORY_CheckSignature(pUnit->pInventory) && INVENTORY_ValidateBodyLoc(nBodyLoc) && pInventoryGrid)
				{
					pItem1 = pInventoryGrid->ppItems[nBodyLoc];
				}

				if (INVENTORY_CheckSignature(pUnit->pInventory) && INVENTORY_ValidateBodyLoc(nOtherBodyLoc) && pInventoryGrid)
				{
					pItem2 = pInventoryGrid->ppItems[nOtherBodyLoc];
				}

				return sub_6FD91D50(pUnit, nBodyLoc, nOtherBodyLoc, pItem, pItem1, pItem2, bDontCheckReqs);
			}
			default:
			{
				struct D2Unit* pInventoryItem = nullptr;
				if (INVENTORY_CheckSignature(pUnit->pInventory) && INVENTORY_ValidateBodyLoc(nBodyLoc) && pInventoryGrid)
				{
					pInventoryItem = pInventoryGrid->ppItems[nBodyLoc];
				}

				if (pItem)
				{
					return pInventoryItem != nullptr ? 5 : 1;
				}
				else
				{
					return pInventoryItem != nullptr ? 3 : 0;
				}
			}
			}
		}
	}

	return 0;
}

//D2Common.0x6FD91D50
//TODO: Find names for function and arguments
int __cdecl sub_6FD91D50(struct D2Unit* pPlayer, int a2, int nBodyLoc, struct D2Unit* a3, struct D2Unit* a4, struct D2Unit* pItem, int nUnused)
{
	D2_MAYBE_UNUSED(nUnused);
	if (!a3)
	{
		if (a4)
		{
			return 3;
		}

		if (pItem && ITEMS_CheckWeaponIfTwoHanded(pItem))
		{
			return 4;
		}

		return 0;
	}

	if (a4)
	{
		if (ITEMS_AreStackablesEqual(a4, a3))
		{
			return 6;
		}

		if (sub_6FD91E80(pPlayer, a3, pItem))
		{
			return 5;
		}

		const int nInventoryRecord = UNITS_GetInventoryRecordId(pPlayer, 0, 1);
		if (INVENTORY_GetPtrIfValid(pPlayer->pInventory) && INVENTORY_ValidateBodyLoc(nBodyLoc))
		{
			struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pPlayer->pInventory, INVGRID_BODYLOC, &gBodyLocInventoryGridInfo);
			if (pInventoryGrid && pInventoryGrid->ppItems[nBodyLoc] && INVENTORY_GetFreePosition(pPlayer->pInventory, pInventoryGrid->ppItems[nBodyLoc], nInventoryRecord, (int*)&a4, (int*)&pItem, 0))
			{
				return 7;
			}
		}

		return 0;
	}

	if (pItem)
	{
		return 2 - (sub_6FD91E80(pPlayer, a3, pItem) != 0);
	}
	else
	{
		return 1;
	}
}

//D2Common.0x6FD91E80
//TODO: Find a name
BOOL __cdecl sub_6FD91E80(struct D2Unit* pUnit, struct D2Unit* pItem1, struct D2Unit* pItem2)
{
	if (!pItem1 || !pItem2
		|| ITEMS_GetAmmoType(pItem1) && ITEMS_CheckItemTypeId(pItem2, ITEMS_GetAmmoType(pItem1))
		|| ITEMS_GetAmmoType(pItem2) && ITEMS_CheckItemTypeId(pItem1, ITEMS_GetAmmoType(pItem2)))
	{
		return TRUE;
	}

	if (ITEMS_GetQuiverType(pItem1) || ITEMS_GetQuiverType(pItem2))
	{
		return FALSE;
	}

	if (!ITEMS_CheckWeaponIfTwoHanded(pItem1) || ITEMS_Is1Or2Handed(pUnit, pItem1))
	{
		if (!ITEMS_CheckWeaponIfTwoHanded(pItem2) || ITEMS_Is1Or2Handed(pUnit, pItem2))
		{
			if (ITEMS_CheckItemTypeId(pItem1, ITEMTYPE_WEAPON) && ITEMS_CheckItemTypeId(pItem2, ITEMTYPE_WEAPON))
			{
				if (!pUnit)
				{
					return FALSE;
				}

				if (pUnit->dwUnitType == UNIT_MONSTER)
				{
					const int nUnitId = MONSTERS_ValidateMonsterId(pUnit->dwClassId);
					switch (nUnitId)
					{
					case MONSTER_SHADOWWARRIOR:
					case MONSTER_SHADOWMASTER:
						if (ITEMS_CheckItemTypeId(pItem1, ITEMTYPE_HAND_TO_HAND) && ITEMS_CheckItemTypeId(pItem2, ITEMTYPE_HAND_TO_HAND))
						{
							return TRUE;
						}
						return FALSE;

					case MONSTER_ANCIENTBARB1:
					case MONSTER_ANCIENTBARB2:
					case MONSTER_ANCIENTBARB3:
						return TRUE;

					default:
						return FALSE;
					}

					return FALSE;
				}

				if (pUnit->dwUnitType != UNIT_PLAYER)
				{
					return FALSE;
				}

				if (pUnit->dwClassId == PCLASS_BARBARIAN)
				{
					return TRUE;
				}

				if (pUnit->dwClassId != PCLASS_ASSASSIN || !ITEMS_CheckItemTypeId(pItem1, ITEMTYPE_HAND_TO_HAND))
				{
					return FALSE;
				}

				if (!ITEMS_CheckItemTypeId(pItem2, ITEMTYPE_HAND_TO_HAND))
				{
					return FALSE;
				}
			}
			else
			{
				if (ITEMS_CheckItemTypeId(pItem1, ITEMTYPE_WEAPON))
				{
					return TRUE;
				}

				if (!ITEMS_CheckItemTypeId(pItem2, ITEMTYPE_WEAPON))
				{
					return FALSE;
				}
			}

			return TRUE;
		}
	}

	return FALSE;
}

//D2Common.0x6FD92080 (#10304)
struct D2Unit* __cdecl INVENTORY_GetNextItem(struct D2Unit* pItem)
{
	struct D2ItemExtraData* pItemExtraData = INVENTORY_GetItemExtraDataFromItem(pItem);
	if (pItemExtraData)
	{
		return pItemExtraData->pNextItem;
	}

	return nullptr;
}

//Inlined at various places
struct D2Unit* __cdecl INVENTORY_GetUnknownItem(struct D2Unit* pItem)
{
	struct D2ItemExtraData* pItemExtraData = INVENTORY_GetItemExtraDataFromItem(pItem);
	if (pItemExtraData)
	{
		return pItemExtraData->unk0x14;
	}

	return nullptr;
}

//D2Common.0x6FD920C0 (#10305)
struct D2Unit* __cdecl INVENTORY_UnitIsItem(struct D2Unit* pItem)
{
	return pItem && pItem->dwUnitType == UNIT_ITEM ? pItem : nullptr;
}

//D2Common.0x6FD920E0 (#10306)
D2UnitGUID __cdecl INVENTORY_GetItemGUID(struct D2Unit* pItem)
{
	if (INVENTORY_UnitIsItem(pItem))
	{
		return pItem->dwUnitId;
	}

	return 0;
}

//D2Common.0x6FD92100 (#10307)
int __cdecl INVENTORY_GetItemNodePage(struct D2Unit* pItem)
{
	struct D2ItemExtraData* pItemExtraData = INVENTORY_GetItemExtraDataFromItem(pItem);
	if (pItemExtraData)
	{
		return pItemExtraData->nNodePosOther;
	}

	return 0;
}

//D2Common.0x6FD92140 (#10310)
struct D2Unit* __cdecl INVENTORY_IsItemInInventory(struct D2Inventory* pInventory, struct D2Unit* pItem)
{
	if (pInventory)
	{
		struct D2ItemExtraData* pItemExtraData = INVENTORY_GetItemExtraDataFromItem(pItem);
		if (pItemExtraData && pInventory == pItemExtraData->pParentInv)
		{
			return pItem;
		}
	}

	return nullptr;
}

//D2Common.0x6FDAFEA0 (#10311)
struct D2InventoryNode* __cdecl INVENTORY_GetNextNode(struct D2InventoryNode* pNode)
{
	if (pNode)
	{
		return pNode->pNext;
	}

	return nullptr;
}

//D2Common.0x6FD90AB0 (#10312)
D2UnitGUID __cdecl INVENTORY_GetItemGUIDFromNode(struct D2InventoryNode* pNode)
{
	if (pNode)
	{
		return pNode->nItemId;
	}

	return 0;
}

//D2Common.0x6FD92180 (#10300)
BOOL __cdecl INVENTORY_RemoveAllItems(struct D2Inventory* pInventory)
{
	if (!INVENTORY_GetPtrIfValid(pInventory))
	{
		return FALSE;
	}

	pInventory->pCursorItem = nullptr;
	pInventory->dwLeftItemGUID = D2UnitInvalidGUID;
	
	while (pInventory->pFirstItem)
	{
		if (!INVENTORY_RemoveItem(pInventory->pFirstItem))
		{
			return FALSE;
		}
	}

	return TRUE;
}

// Helper function
BOOL __cdecl INVENTORY_CanItemBePlacedInTradeInventory(struct D2Inventory* pTradeInventory, struct D2Unit* pPlayer1, struct D2Unit* pPlayer2)
{
	for (struct D2Unit* pItem = INVENTORY_GetFirstItem(pPlayer1->pInventory); pItem; pItem = INVENTORY_GetNextItem(pItem))
	{
		pItem = INVENTORY_UnitIsItem(pItem);
		if (ITEMS_GetInvPage(pItem) == INVPAGE_TRADE && !INVENTORY_CanItemBePlacedInInventory(pPlayer2, pItem, pTradeInventory))
		{
			return FALSE;
		}
	}

	return TRUE;
}

//D2Common.0x6FD921D0 (#10302)
BOOL __cdecl INVENTORY_CanItemsBeTraded(void* pMemPool, struct D2Unit* pPlayer1, struct D2Unit* pPlayer2, enum D2TradeStates* pTradeState)
{	
	struct D2Inventory* pTradeInventory1 = INVENTORY_AllocInventory(pMemPool, nullptr);
	struct D2Inventory* pTradeInventory2 = INVENTORY_AllocInventory(pMemPool, nullptr);

	if (pTradeInventory1 && pTradeInventory2 && INVENTORY_CopyUnitItemsToTradeInventory(pTradeInventory1, pPlayer1) && INVENTORY_CopyUnitItemsToTradeInventory(pTradeInventory2, pPlayer2))
	{
		if (!INVENTORY_CanItemBePlacedInTradeInventory(pTradeInventory2, pPlayer1, pPlayer2))
		{
			if (pTradeState)
			{
				*pTradeState = TRADESTATE_OTHERNOROOM;
			}
		}
		else if (!INVENTORY_CanItemBePlacedInTradeInventory(pTradeInventory1, pPlayer2, pPlayer1))
		{
			if (pTradeState)
			{
				*pTradeState = TRADESTATE_SELFNOROOM;
			}
		}
		else
		{
			INVENTORY_FreeInventory(pTradeInventory1);
			INVENTORY_FreeInventory(pTradeInventory2);
			return TRUE;
		}
	}

	INVENTORY_FreeInventory(pTradeInventory1);
	INVENTORY_FreeInventory(pTradeInventory2);
	return FALSE;
}

//D2Common.0x6FD923C0
BOOL __cdecl INVENTORY_CopyUnitItemsToTradeInventory(struct D2Inventory* pTradeInventory, struct D2Unit* pUnit)
{
	if (INVENTORY_GetPtrIfValid(pTradeInventory))
	{
		const int nInventoryRecordId = UNITS_GetInventoryRecordId(pUnit, INVPAGE_INVENTORY, TRUE);
		struct D2InventoryGridInfo pInventoryGridInfo = {};
		DATATBLS_GetInventoryGridInfo(nInventoryRecordId, 0, &pInventoryGridInfo);

		struct D2InventoryGrid* pTradeInventoryGrid = INVENTORY_GetGrid(pTradeInventory, INVGRID_INVENTORY, &pInventoryGridInfo);

		if (pTradeInventoryGrid && INVENTORY_GetPtrIfValid(pUnit->pInventory))
		{
			struct D2InventoryGrid* pUnitInventoryGrid = INVENTORY_GetGrid(pUnit->pInventory, INVGRID_INVENTORY, &pInventoryGridInfo);

			if (pUnitInventoryGrid && pUnitInventoryGrid->nGridWidth && pUnitInventoryGrid->nGridHeight
				&& pUnitInventoryGrid->nGridWidth == pTradeInventoryGrid->nGridWidth && pUnitInventoryGrid->nGridHeight == pTradeInventoryGrid->nGridHeight
				&& pUnitInventoryGrid->ppItems && pTradeInventoryGrid->ppItems)
			{
				memcpy(pTradeInventoryGrid->ppItems, pUnitInventoryGrid->ppItems, sizeof(struct D2Unit*) * pUnitInventoryGrid->nGridWidth * pUnitInventoryGrid->nGridHeight);

				return TRUE;
			}
		}
	}
	
	return FALSE;
}

//D2Common.0x6FD92490
BOOL __cdecl INVENTORY_CanItemBePlacedInInventory(struct D2Unit* pPlayer, struct D2Unit* pItem, struct D2Inventory* pInventory)
{
	if (INVENTORY_GetPtrIfValid(pInventory))
	{
		const int nInventoryRecordId = UNITS_GetInventoryRecordId(pPlayer, INVPAGE_INVENTORY, TRUE);
		struct D2InventoryGridInfo pInventoryGridInfo = {};
		DATATBLS_GetInventoryGridInfo(nInventoryRecordId, 0, &pInventoryGridInfo);

		struct D2InventoryGrid* pInventoryGrid = INVENTORY_GetGrid(pInventory, INVGRID_INVENTORY, &pInventoryGridInfo);

		int nX = 0;
		int nY = 0;
		if (pInventoryGrid && INVENTORY_GetFreePosition(pInventory, pItem, nInventoryRecordId, &nX, &nY, 0))
		{
			uint8_t nHeight = 0;
			uint8_t nWidth = 0;

			ITEMS_GetDimensions(pItem, &nWidth, &nHeight, __FILE__, __LINE__);

			if (nWidth && nHeight && nX >= 0 && nX + nWidth <= pInventoryGrid->nGridWidth && nY >= 0 && nY + nHeight <= pInventoryGrid->nGridHeight)
			{
				for (int y = nY; y < nY + nHeight; ++y)
				{
					for (int x = nX; x < nX + nWidth; ++x)
					{
						pInventoryGrid->ppItems[x + y * pInventoryGrid->nGridWidth] = (struct D2Unit*)0xFFFFFFFF;
					}
				}

				return TRUE;
			}
		}
	}

	return FALSE;
}

//D2Common.0x6FD925E0
int __cdecl UNITS_GetXPosition(struct D2Unit* pUnit)
{
	switch (pUnit->dwUnitType)
	{
	case UNIT_PLAYER:
	case UNIT_MONSTER:
	case UNIT_MISSILE:
		return pUnit->pDynamicPath ? pUnit->pDynamicPath->tGameCoords.wPosX : 0;

	case UNIT_OBJECT:
	case UNIT_ITEM:
	case UNIT_TILE:
		return pUnit->pStaticPath ? pUnit->pStaticPath->tGameCoords.nX : 0;
	default:
		return 0;
	}
}

//D2Common.0x6FD92610
int __cdecl UNITS_GetYPosition(struct D2Unit* pUnit)
{
	switch (pUnit->dwUnitType)
	{
	case UNIT_PLAYER:
	case UNIT_MONSTER:
	case UNIT_MISSILE:
		return pUnit->pDynamicPath ? pUnit->pDynamicPath->tGameCoords.wPosY : 0;

	case UNIT_OBJECT:
	case UNIT_ITEM:
	case UNIT_TILE:
		return pUnit->pStaticPath ? pUnit->pStaticPath->tGameCoords.nY : 0;
	default:
		return 0;
	}
}
