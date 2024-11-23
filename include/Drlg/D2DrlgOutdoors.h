#pragma once

#include "CommonDefinitions.h"
#include "D2DrlgDrlg.h"
#include "D2DrlgDrlgGrid.h"


#pragma pack(1)

enum D2C_OutDoorInfoFlags 
{
	OUTDOOR_FLAG1 = 0x00000001,
	OUTDOOR_BRIDGE = 0x00000004,
	OUTDOOR_RIVER_OTHER = 0x00000008,
	OUTDOOR_RIVER = 0x00000010,
	OUTDOOR_CLIFFS = 0x00000020,
	OUTDOOR_OUT_CAVES = 0x00000040,
	OUTDOOR_SOUTHWEST = 0x00000080,
	OUTDOOR_NORTHWEST = 0x00000100,
	OUTDOOR_SOUTHEAST = 0x00000200,
	OUTDOOR_NORTHEAST = 0x00000400,
};

struct D2DrlgOutdoorGrid
{
	int32_t dwFlags;						//0x00
	struct D2DrlgGrid* pSectors;				//0x04
	int32_t nWidth;							//0x08
	int32_t nHeight;						//0x0C
	BOOL bInit;								//0x10
};

union D2DrlgOutdoorPackedGrid2Info // TODO: rename
{
	uint32_t nPackedValue;
	struct {
		uint32_t nUnkb00 : 1;		 // Mask 0x00000001
		uint32_t bHasDirection : 1;  // Mask 0x00000002
		uint32_t nUnkb02 : 5;        // Mask 0x0000007C
		uint32_t nUnkb07 : 1;        // Mask 0x00000080 spawn preset level here ?
		uint32_t nUnkb08 : 1;        // Mask 0x00000100 related to being a blank grid cell?
		uint32_t bHasPickedFile : 1; // Mask 0x00000200
		uint32_t bLvlLink : 1;		 // Mask 0x00000400
		uint32_t nUnkb11 : 1;		 // Mask 0x00000800
		uint32_t nUnkb12 : 1;		 // Mask 0x00001000
		uint32_t nUnkb13 : 3;		 // Mask 0x0000E000
		uint32_t nPickedFile : 4;    // Mask 0x000F0000
		uint32_t nUnkb20 : 12;       // Mask 0xFFF00000
	};
};

struct D2DrlgOutdoorInfo
{
	uint32_t dwFlags;						//0x00 D2C_OutDoorInfoFlags
	struct D2DrlgGrid pGrid[4];				//0x04 0: LevelPrestId 1: ? 2: union D2DrlgOutdoorPackedGrid2Info
	union
	{
		struct
		{
			int32_t nWidth;					//0x54
			int32_t nHeight;				//0x58
			int32_t nGridWidth;				//0x5C
			int32_t nGridHeight;			//0x60
		};
		struct D2DrlgCoord pCoord;
	};
	struct D2DrlgVertex* pVertex;				//0x64
	struct D2DrlgVertex* pPathStarts[6];			//0x68
	struct D2DrlgVertex pVertices[24];			//0x80
	int32_t nVertices;						//0x260 Maybe nPathStarts instead?
	struct D2DrlgOrth* pRoomData;				//0x264
};

#pragma pack()

//Helper function
union D2DrlgOutdoorPackedGrid2Info DRLGOUTDOORS_GetPackedGrid2Info(struct D2DrlgOutdoorInfo* pOutdoors, int nX, int nY)
{
	uint32_t nPackedValue = DRLGGRID_GetGridEntry(&pOutdoors->pGrid[2], nX, nY);
	return (union D2DrlgOutdoorPackedGrid2Info){ nPackedValue };
}

//D2Common.0x6FD7DC20
int DRLGOUTDOORS_GetOutLinkVisFlag(struct D2DrlgLevel* pLevel, struct D2DrlgVertex* pDrlgVertex);
//D2Common.0x6FD7DD00
int DRLGOUTDOORS_GetPresetIndexFromGridCell(struct D2DrlgLevel* pLevel, int nX, int nY);
//D2Common.0x6FD7DD40
void DRLGOUTDOORS_AlterAdjacentPresetGridCells(struct D2DrlgLevel* pLevel, int nX, int nY);
//D2Common.0x6FD7DD70
void DRLGOUTDOORS_SetBlankGridCell(struct D2DrlgLevel* pLevel, int nX, int nY);
//D2Common.0x6FD7DDB0
unsigned int DRLGOUTDOORS_TestGridCellNonLvlLink(struct D2DrlgLevel* pLevel, int nX, int nY);
//D2Common.0x6FD7DDD0
BOOL DRLGOUTDOORS_TestGridCellSpawnValid(struct D2DrlgLevel* pLevel, int nX, int nY);
//D2Common.0x6FD7DDF0
BOOL DRLGOUTDOORS_TestOutdoorLevelPreset(struct D2DrlgLevel* pLevel, int nX, int nY, int nLevelPrestId, int nOffset, char nFlags);
//D2Common.0x6FD7DEF0
void DRLGOUTDOORS_SpawnOutdoorLevelPresetEx(struct D2DrlgLevel* pLevel, int nX, int nY, int nLevelPrestId, int nPickedFile, BOOL bBorder);
//D2Common.0x6FD7E0F0
BOOL DRLGOUTDOORS_SpawnPresetFarAway(struct D2DrlgLevel* pLevel, struct D2DrlgCoord* pDrlgCoord, int nLvlPrestId, int nRand, int nOffset, char nFlags);
//D2Common.0x6FD7E330
BOOL DRLGOUTDOORS_SpawnOutdoorLevelPreset(struct D2DrlgLevel* pLevel, int nLevelPrestId, int nRand, int nOffset, char nFlags);
//D2Common.0x6FD7E4D0
BOOL DRLGOUTDOORS_SpawnRandomOutdoorDS1(struct D2DrlgLevel* pLevel, int nLvlPrestId, int nRand);
//D2Common.0x6FD7E6D0
void DRLGOUTDOORS_SpawnAct12Waypoint(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7E940
void DRLGOUTDOORS_SpawnAct12Shrines(struct D2DrlgLevel* pLevel, int nShrines);
//D2Common.0x6FD7EB20
void DRLGOUTDOORS_AddAct124SecondaryBorder(struct D2DrlgLevel* pLevel, int nLvlSubId, int nLevelPrestId);
//D2Common.0x6FD7EBA0
void DRLGOUTDOORS_AllocOutdoorInfo(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7EBD0
void DRLGOUTDOORS_GenerateLevel(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7EEE0
void DRLGOUTDOORS_FreeOutdoorInfo(struct D2DrlgLevel* pLevel, BOOL bKeepRoomData);
//D2Common.0x6FD7EFE0
void DRLG_OUTDOORS_GenerateDirtPath(struct D2DrlgLevel* pLevel, struct D2DrlgRoom* pDrlgRoom);
//D2Common.0x6FD7F250
void DRLGOUTDOORS_SpawnAct1DirtPaths(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7F500
void DRLGOUTDOORS_CalculatePathCoordinates(struct D2DrlgLevel* pLevel, struct D2DrlgVertex* pVertex1, struct D2DrlgVertex* pVertex2);
//D2Common.0x6FD7F5B0
void sub_6FD7F5B0(struct D2DrlgLevel* pLevel);
//D2Common.0x6FD7F810
void sub_6FD7F810(struct D2DrlgLevel* pLevel, int nVertexId);
//D2Common.0x6FD7F9B0
void DRLGOUTDOORS_InitAct4OutdoorLevel(struct D2DrlgLevel* pLevel);
