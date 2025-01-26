#pragma once

#include "D2CommonDefinitions.h"
#include <Drlg/D2DrlgDrlg.h>
// TODO: Reimport from .cpp

#pragma pack(1)

struct D2BoundingBox
{
	int32_t nLeft;								//0x00
	int32_t nBottom;							//0x04
	int32_t nRight;								//0x08
	int32_t nTop;								//0x0C
};

// Size of the unit in subtiles
enum D2C_CollisionUnitSize
{
	COLLISION_UNIT_SIZE_NONE  = 0,
	COLLISION_UNIT_SIZE_POINT = 1, // Occupies 1 subtile in width
	COLLISION_UNIT_SIZE_SMALL = 2, // Occupies 2 subtiles in width
	COLLISION_UNIT_SIZE_BIG   = 3, // Occupies 3 subtiles in width
	COLLISION_UNIT_SIZE_COUNT
};

enum D2C_CollisionPattern
{
	COLLISION_PATTERN_NONE = 0,
	COLLISION_PATTERN_SMALL_UNIT_PRESENCE = 1,
	COLLISION_PATTERN_BIG_UNIT_PRESENCE = 2,
	// Actually linked to whether a monster may be attacked?
	COLLISION_PATTERN_SMALL_PET_PRESENCE  = 3,
	COLLISION_PATTERN_BIG_PET_PRESENCE    = 4,
	COLLISION_PATTERN_SMALL_NO_PRESENCE   = 5,
};

enum D2C_CollisionMaskFlags : uint16_t
{
	COLLIDE_NONE = 0x0000,
	COLLIDE_WALL = 0x0001,					// 'black space' in arcane sanctuary, cliff walls etc. Effectively blocks player.
	COLLIDE_VISIBLE = 0x0002,				// tile based obstacles you can't shoot over
	COLLIDE_MISSILE_BARRIER = 0x0004,		// again used inconsistantly -.- Can guard against Missile / Flying ?
	COLLIDE_NOPLAYER = 0x0008,
	COLLIDE_PRESET = 0x0010,				// some floors have this set, others don't
	COLLIDE_BLANK = 0x0020,					// returned if the subtile is invalid
	COLLIDE_MISSILE = 0x0040,
	COLLIDE_PLAYER = 0x0080,
	COLLIDE_WATER = 0x00C0,
	COLLIDE_MONSTER = 0x0100,
	COLLIDE_ITEM = 0x0200,
	COLLIDE_OBJECT = 0x0400,
	COLLIDE_DOOR = 0x0800,
	COLLIDE_NO_PATH = 0x1000,				// set for units sometimes, but not always
	COLLIDE_PET = 0x2000,					// linked to whether a monster that may be attacked is present
	COLLIDE_4000 = 0x4000,
	COLLIDE_CORPSE = 0x8000,				// also used by portals, but dead monsters are mask 0x8000
	COLLIDE_ALL_MASK = 0xFFFF,
	COLLIDE_MASK_INVALID = (COLLIDE_BLANK | COLLIDE_MISSILE_BARRIER | COLLIDE_VISIBLE | COLLIDE_WALL),
		
	COLLIDE_MASK_PLAYER_PATH = COLLIDE_WALL | COLLIDE_NOPLAYER | COLLIDE_OBJECT | COLLIDE_DOOR | COLLIDE_NO_PATH,
	COLLIDE_MASK_PLAYER_FLYING = COLLIDE_DOOR | COLLIDE_MISSILE_BARRIER,
	COLLIDE_MASK_PLAYER_WW = COLLIDE_WALL | COLLIDE_OBJECT | COLLIDE_DOOR,
	COLLIDE_MASK_RADIAL_BARRIER = COLLIDE_DOOR | COLLIDE_MISSILE_BARRIER | COLLIDE_WALL,

	COLLIDE_MASK_FLYING_UNIT = COLLIDE_MISSILE_BARRIER | COLLIDE_DOOR | COLLIDE_NO_PATH,
	COLLIDE_MASK_MONSTER_THAT_CAN_OPEN_DOORS = COLLIDE_WALL | COLLIDE_OBJECT | COLLIDE_NO_PATH | COLLIDE_PET,

	COLLIDE_MASK_MONSTER_MISSILE = COLLIDE_MONSTER | COLLIDE_WALL,
	COLLIDE_MASK_MONSTER_PATH = COLLIDE_MASK_MONSTER_THAT_CAN_OPEN_DOORS | COLLIDE_DOOR,
	COLLIDE_MASK_DOOR_BLOCK_VIS = COLLIDE_DOOR | COLLIDE_MISSILE_BARRIER | COLLIDE_VISIBLE,
	
	COLLIDE_MASK_BLOCKS_DOOR = COLLIDE_PLAYER | COLLIDE_MONSTER | COLLIDE_CORPSE,
	COLLIDE_MASK_SPAWN = COLLIDE_WALL | COLLIDE_ITEM | COLLIDE_OBJECT | COLLIDE_DOOR | COLLIDE_NO_PATH | COLLIDE_PET,
	COLLIDE_MASK_PLACEMENT = COLLIDE_MASK_SPAWN | COLLIDE_PRESET | COLLIDE_MONSTER,

};

struct D2RoomCollisionGrid
{
	struct D2DrlgCoords pRoomCoords;			//0x00
	uint16_t* pCollisionMask;					//0x20
};
#pragma pack()

//D2Common.0x6FD41000
void __cdecl D2Common_COLLISION_FirstFn_6FD41000(struct D2ActiveRoom* pRoom, struct D2DrlgTileData* pTileData, struct D2TileLibraryEntry* pTileLibraryEntry);
//D2Common.0x6FD411F0
void __cdecl sub_6FD411F0(struct D2RoomCollisionGrid* pCollisionGrid, struct D2TileLibraryEntry* pTileLibraryEntry, int nX, int nY);
//D2Common.0x6FD412B0 (#10018)
D2COMMON_DLL_DECL int __cdecl D2COMMON_10018_Return0();
//D2Common.0x6FD412C0
void __cdecl COLLISION_AllocRoomCollisionGrid(void* pMemPool, struct D2ActiveRoom* pRoom);
//D2Common.0x6FD413E0
void __cdecl sub_6FD413E0(struct D2RoomCollisionGrid* pCollisionGrid, struct D2RoomCollisionGrid* pAdjacentCollisionGrid, struct D2DrlgTileData* pTiles, int nTiles, BOOL bRemoveOldFlags);
//D2Common.0x6FD41610
void __cdecl COLLISION_FreeRoomCollisionGrid(void* pMemPool, struct D2ActiveRoom* pRoom);
//D2Common.0x6FD41650 (#10118)
D2COMMON_DLL_DECL uint16_t __cdecl COLLISION_CheckMask(struct D2ActiveRoom* pRoom, int nX, int nY, uint16_t nMask);
//D2Common.0x6FD41720 (#10127)
D2COMMON_DLL_DECL void __cdecl COLLISION_SetMask(struct D2ActiveRoom* pRoom, int nX, int nY, uint16_t nMask);
//D2Common.0x6FD417F0 (#10123)
D2COMMON_DLL_DECL void __cdecl COLLISION_ResetMask(struct D2ActiveRoom* pRoom, int nX, int nY, uint16_t nMask);
//D2Common.0x6FD418C0 (#10120)
D2COMMON_DLL_DECL uint16_t __cdecl COLLISION_CheckMaskWithSizeXY(struct D2ActiveRoom* pRoom, int nX, int nY, unsigned int nSizeX, unsigned int nSizeY, uint16_t nMask);
//D2Common.0x6FD41B40
uint16_t __cdecl COLLISION_CheckCollisionMaskForBoundingBox(struct D2RoomCollisionGrid* pCollisionGrid, struct D2BoundingBox* pBoundingBox, uint16_t nMask);
//D2Common.0x6FD41BE0
int __cdecl COLLISION_AdaptBoundingBoxToGrid(struct D2ActiveRoom* pRoom, struct D2BoundingBox* pBoundingBox, struct D2BoundingBox* pBoundingBoxes);
//D2Common.0x6FD41CA0
uint16_t __cdecl COLLISION_CheckCollisionMaskForBoundingBoxRecursively(struct D2ActiveRoom* pRoom, struct D2BoundingBox* pBoundingBox, uint16_t nMask);
//D2Common.0x6FD41DE0 (#10121)
D2COMMON_DLL_DECL uint16_t __cdecl COLLISION_CheckMaskWithPattern(struct D2ActiveRoom* pRoom, int nX, int nY, int nCollisionPattern, uint16_t nMask);
//D2Common.0x6FD42000
uint16_t __cdecl COLLISION_CheckCollisionMaskWithAdjacentCells(struct D2ActiveRoom* pRoom, int nX, int nY, uint16_t nMask);
//D2Common.0x6FD42670
uint16_t __cdecl COLLISION_CheckCollisionMask(struct D2ActiveRoom* pRoom, int nX, int nY, uint16_t nMask);
//D2Common.0x6FD42740 (#10122)
D2COMMON_DLL_DECL int __cdecl COLLISION_CheckAnyCollisionWithPattern(struct D2ActiveRoom* pRoom, int nX, int nY, int nCollisionPattern, uint16_t nMask);
//D2Common.0x6FD428D0
// Faster than COLLISION_CheckCollisionMaskForBoundingBoxRecursively since can stop as soon as a collision is found.
BOOL __cdecl COLLISION_CheckAnyCollisionForBoundingBoxRecursively(struct D2ActiveRoom* pRoom, struct D2BoundingBox* pBoundingBox, uint16_t nMask);
//D2Common.0x6FD42A30
BOOL __cdecl COLLISION_CheckAnyCollisionWithAdjacentCells(struct D2ActiveRoom* pRoom, int nX, int nY, uint16_t nMask);
//D2Common.0x6FD43080 (#10119)
D2COMMON_DLL_DECL uint16_t __cdecl COLLISION_CheckMaskWithSize(struct D2ActiveRoom* pRoom, int nX, int nY, int nUnitSize, uint16_t nMask);
//D2Common.0x6FD432A0 (#10128)
D2COMMON_DLL_DECL void __cdecl COLLISION_SetMaskWithSize(struct D2ActiveRoom* pRoom, int nX, int nY, int nUnitSize, uint16_t nMask);
//D2Common.0x6FD434B0
void __cdecl COLLISION_SetCollisionMask(struct D2ActiveRoom* pRoom, int nX, int nY, uint16_t nMask);
//D2Common.0x6FD43580
void __cdecl COLLISION_SetCollisionMaskForBoundingBoxRecursively(struct D2ActiveRoom* pRoom, struct D2BoundingBox* pBoundingBox, uint16_t nMask);
//D2Common.0x6FD436F0 (#10130)
D2COMMON_DLL_DECL void __cdecl COLLISION_SetMaskWithPattern(struct D2ActiveRoom* pRoom, int nX, int nY, int nCollisionPattern, uint16_t nMask);
//D2Common.0x6FD439D0 (#10124)
D2COMMON_DLL_DECL void __cdecl COLLISION_ResetMaskWithSize(struct D2ActiveRoom* pRoom, int nX, int nY, int nUnitSize, uint16_t nMask);
//D2Common.0x6FD43C10
void __cdecl COLLISION_ResetCollisionMask(struct D2ActiveRoom* pRoom, int nX, int nY, uint16_t nMask);
//D2Common.0x6FD43CE0
void __cdecl COLLISION_ResetCollisionMaskForBoundingBoxRecursively(struct D2ActiveRoom* pRoom, struct D2BoundingBox* pBoundingBox, uint16_t nMask);
//D2Common.0x6FD43E60 (#10126)
D2COMMON_DLL_DECL void __cdecl COLLISION_ResetMaskWithPattern(struct D2ActiveRoom* pRoom, int nX, int nY, int nCollisionPattern, uint16_t nMask);
//D2Common.0x6FD44140 (#10125)
D2COMMON_DLL_DECL void __cdecl COLLISION_ResetMaskWithSizeXY(struct D2ActiveRoom* pRoom, int nX, int nY, unsigned int nSizeX, unsigned int nSizeY, uint16_t nMask);
//D2Common.0x6FD44370
void __cdecl COLLISION_ResetCollisionMaskForBoundingBox(struct D2RoomCollisionGrid* pCollisionGrid, struct D2BoundingBox* pBoundingBox, uint16_t nMask);
//D2Common.0x6FD443E0 (#10129)
D2COMMON_DLL_DECL void __cdecl COLLISION_SetMaskWithSizeXY(struct D2ActiveRoom* pRoom, int nX, int nY, unsigned int nSizeX, unsigned int nSizeY, uint16_t nMask);
//D2Common.0x6FD44600
void __cdecl COLLISION_SetCollisionMaskForBoundingBox(struct D2RoomCollisionGrid* pCollisionGrid, struct D2BoundingBox* pBoundingBox, uint16_t nMask);
//D2Common.0x6FD44660 (#10131)
D2COMMON_DLL_DECL uint16_t __cdecl COLLISION_TryMoveUnitCollisionMask(struct D2ActiveRoom* pRoom, int nX1, int nY1, int nX2, int nY2, int nUnitSize, uint16_t nCollisionMask, uint16_t nMoveConditionMask);
//D2Common.0x6FD44910
void __cdecl COLLISION_CreateBoundingBox(struct D2BoundingBox* pBoundingBox, int nCenterX, int nCenterY, unsigned int nSizeX, unsigned int nSizeY);
//D2Common.0x6FD44950 (#10132)
D2COMMON_DLL_DECL uint16_t __cdecl COLLISION_TryTeleportUnitCollisionMask(struct D2ActiveRoom* pRoom, int nX1, int nY1, int nX2, int nY2, int nCollisionPattern, uint16_t nFootprintCollisionMask, uint16_t nMoveConditionMask);
//D2Common.0x6FD44BB0
uint16_t __cdecl COLLISION_ForceTeleportUnitCollisionMaskAndGetCollision(struct D2ActiveRoom* pRoom1, int nX1, int nY1, struct D2ActiveRoom* pRoom2, int nX2, int nY2, int nUnitSize, uint16_t nFootprintCollisionMask, uint16_t nMoveConditionMask);
//D2Common.0x6FD44E00
uint16_t __cdecl COLLISION_TeleportUnitCollisionMask(struct D2ActiveRoom* pRoom1, int nX1, int nY1, struct D2ActiveRoom* pRoom2, int nX2, int nY2, int nUnitSize, uint16_t nMask);
//D2Common.0x6FD44FF0
int __cdecl COLLISION_TrySetUnitCollisionMask(struct D2ActiveRoom* pRoom1, int nX1, int nY1, struct D2ActiveRoom* pRoom2, int nX2, int nY2, int nCollisionPattern, uint16_t nFootprintCollisionMask, uint16_t nMoveConditionMask);
//D2Common.0x6FD451D0 (#10133)
D2COMMON_DLL_DECL void __cdecl COLLISION_SetUnitCollisionMask(struct D2ActiveRoom* pRoom1, int nX1, int nY1, struct D2ActiveRoom* pRoom2, int nX2, int nY2, int nCollisionPattern, uint16_t nCollisionMask);
//D2Common.0x6FD45210 (#11263)
//Returns true if a collision with mask was found. pEndCoord will be set to the collision location.
D2COMMON_DLL_DECL BOOL __cdecl COLLISION_RayTrace(struct D2ActiveRoom* pRoom, struct D2Coord* pBeginCoord, struct D2Coord* pEndCoord, uint16_t nCollisionMask);
//D2Common.0x6FD459D0 (#10135)
D2COMMON_DLL_DECL struct D2ActiveRoom* __cdecl COLLISION_GetFreeCoordinatesWithMaxDistance(struct D2ActiveRoom* pRoom, struct D2Coord* pSpawnPoint, int nUnitSize, unsigned int nMask, BOOL bAllowNeighborRooms, int nMaxDistance);
//D2Common.0x6FD45A00
struct D2ActiveRoom* __cdecl COLLISION_GetFreeCoordinatesImpl(struct D2ActiveRoom* pRoom, struct D2Coord* ptSpawnPoint, struct D2Coord* pFieldCoord, int nUnitSize, unsigned int nMask, unsigned int nFieldMask, BOOL bAllowNeighborRooms, int nMaxDistance, int nPosIncrementValue);
//D2Common.0x6FD46280 (#10134)
D2COMMON_DLL_DECL struct D2ActiveRoom* __cdecl COLLISION_GetFreeCoordinates(struct D2ActiveRoom* pRoom, struct D2Coord* pSpawnPoint, int nUnitSize, unsigned int nMask, BOOL bAllowNeighborRooms);
//D2Common.0x6FD462B0 (#10137)
D2COMMON_DLL_DECL struct D2ActiveRoom* __cdecl COLLISION_GetFreeCoordinatesEx(struct D2ActiveRoom* pRoom, struct D2Coord* pSpawnPoint, int nUnitSize, unsigned int nMask, int nPosIncrementValue);
//D2Common.0x6FD462E0 (#10138)
D2COMMON_DLL_DECL struct D2ActiveRoom* __cdecl COLLISION_GetFreeCoordinatesWithField(struct D2ActiveRoom* pRoom, struct D2Coord* pSpawnPoint, struct D2Coord* pFieldCoord, int nUnitSize, unsigned int nMask, unsigned int nFieldMask, BOOL bAllowNeighborRooms);
//D2Common.0x6FD46310 (#10136)
D2COMMON_DLL_DECL void __cdecl D2Common_10136(struct D2ActiveRoom* pRoom, struct D2Coord* pCoord, int a3, uint16_t nMask, struct D2ActiveRoom** ppRoom);
//D2Common.0x6FD46620
struct D2ActiveRoom* __cdecl COLLISION_GetRoomBySubTileCoordinates(struct D2ActiveRoom* pRoom, int nX, int nY);
