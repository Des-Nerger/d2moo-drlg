#pragma once

#include "D2CommonDefinitions.h"

struct D2ActiveRoom;
struct D2Unit;

#pragma pack(1)

enum D2PathConstants {
	PATH_NB_DIRECTIONS = 64,
	PATH_DIR_NULL = 255,
	PATH_MAX_STEPNUM = 20,
	PATH_MAXDESTSHIFT = 8, // Used in DRLG_OutFlr.cpp
};

enum D2PathTypes
{
	PATHTYPE_IDASTAR = 0,
	PATHTYPE_ASTAR = 1,
	PATHTYPE_TOWARD = 2,
	PATHTYPE_UNKNOWN_3 = 3,			// Same as PATHTYPE_TOWARD, unused ?
	PATHTYPE_MISSILE = 4,			// Requires PATH_MISSILE_MASK
	PATHTYPE_MON_CIRCLE_CW = 5,		// Clock-wise
	PATHTYPE_MON_CIRCLE_CCW = 6,	// Counter-clock-wise
	PATHTYPE_STRAIGHT = 7,			// Goes in a straight line except once close enough, will try to use AStar
	PATHTYPE_KNOCKBACK_SERVER = 8,
	PATHTYPE_LEAP = 9,
	PATHTYPE_CHARGEDBOLT = 10,		// Requires PATH_MISSILE_MASK
	PATHTYPE_KNOCKBACK_CLIENT = 11,
	PATHTYPE_BACKUP_TURN = 12,		// Turns when colliding before reaching destination.
	PATHTYPE_TOWARD_FINISH = 13,
	PATHTYPE_BLESSEDHAMMER = 14,	// Requires PATH_MISSILE_MASK
	PATHTYPE_WALL_FOLLOW = 15,		// PATH_WF
	PATHTYPE_MISSILE_STREAM = 16,	// Missile streams seems to be unused in the game even though the code exists?
	PATHTYPE_UNKNOWN_17 = 17,		// Unused, stubbed?

	PATHTYPE_COUNT = 18
};

enum D2PathFlags : uint32_t {
	PATH_UNKNOWN_FLAG_0x00001 = 0x00001, // Set when rider and mount were in different rooms
	PATH_CURRENT_ROOM_INVALID = 0x00002,
	PATH_UNUSED_FLAG_0x00004  = 0x00004, // This is unused
	PATH_UNKNOWN_FLAG_0x00008 = 0x00008, // Set when rider and mount have the same position
	PATH_UNKNOWN_FLAG_0x00010 = 0x00010,
	PATH_UNKNOWN_FLAG_0x00020 = 0x00020, // Only set on the client side
	PATH_UNKNOWN_FLAG_0x00040 = 0x00040,
	PATH_UNKNOWN_FLAG_0x00200 = 0x00200,
	PATH_UNKNOWN_FLAG_0x00800 = 0x00800,
	PATH_UNKNOWN_FLAG_0x01000 = 0x01000,
	PATH_UNKNOWN_FLAG_0x02000 = 0x02000,
	PATH_UNKNOWN_FLAG_0x04000 = 0x04000,
	PATH_WITH_PREVIOUS_VELOCITY = 0x08000,
	PATH_UNKNOWN_FLAG_0x10000 = 0x10000,
	PATH_SAVE_STEPS_MASK      = 0x20000,
	PATH_MISSILE_MASK         = 0x40000,
};

struct D2PathPoint
{
	uint16_t X;
	uint16_t Y;
};

inline int D2PathPoint_SquaredDistance(struct D2PathPoint self, struct D2PathPoint other) {
	const int nDiffX = other.X - self.X;
	const int nDiffY = other.Y - self.Y;
	return nDiffX * nDiffX + nDiffY * nDiffY;
}

// Represents a position with 16bit fixed point precision
union D2FP32_16
{
	struct
	{
		uint16_t wOffsetX;					//0x00
		uint16_t wPosX;						//0x02
		uint16_t wOffsetY;					//0x04
		uint16_t wPosY;						//0x06
	};

	struct
	{
		uint32_t dwPrecisionX;				//0x00
		uint32_t dwPrecisionY;				//0x04
	};
};

inline struct D2PathPoint D2FP32_16_ToPathPoint(union D2FP32_16 self) {
	return (struct D2PathPoint){ self.wPosX, self.wPosY };
}

enum : size_t {
	D2DynamicPath_MAXPATHLEN = 78,
	D2DynamicPath_PATH_MAX_STEP_LEN = 10,
};

struct D2DynamicPath
{
	union D2FP32_16 tGameCoords;						//0x00
	int32_t dwClientCoordX;						//0x08
	int32_t dwClientCoordY;						//0x0C
	struct D2PathPoint tTargetCoord;				//0x10
	struct D2PathPoint tPrevTargetCoord;			//0x14
	struct D2PathPoint tFinalTargetCoord;			//0x18
	struct D2ActiveRoom* pRoom;					//0x1C
	struct D2ActiveRoom* pPreviousRoom;			//0x20
	int32_t dwCurrentPointIdx;					//0x24
	int32_t dwPathPoints;						//0x28
	void* unk0x2C;								//0x2C
	struct D2Unit* pUnit;							//0x30
	uint32_t dwFlags;							//0x34 D2PathFlags
	uint32_t unk0x38;							//0x38
	uint32_t dwPathType;						//0x3C
	uint32_t dwPrevPathType;					//0x40
	uint32_t dwUnitSize;						//0x44
	uint32_t dwCollisionPattern;				//0x48
	uint32_t nFootprintCollisionMask;			//0x4C
	uint32_t nMoveTestCollisionMask;			//0x50
	uint16_t nCollidedWithMask;					//0x54
	uint16_t padding0x56;						//0x56
	struct D2Unit* pTargetUnit;					//0x58
	uint32_t dwTargetType;						//0x5C
	uint32_t dwTargetId;						//0x60
	uint8_t nDirection;							//0x64
	uint8_t nNewDirection;						//0x65
	uint8_t nDiffDirection;						//0x66
	uint8_t unk0x67;							//0x67
	uint8_t dwSpeed;							//0x68
	uint8_t unk0x69;							//0x69
	struct D2Coord tDirectionVector;				//0x6A
	struct D2Coord tVelocityVector;				//0x72
	char padding0x7A[2];						//0x7A
	int32_t dwVelocity;							//0x7C
	uint32_t nPreviousVelocity;					//0x80
	int32_t dwMaxVelocity;						//0x84
	int32_t dwAcceleration;						//0x88
	int32_t dwAccelerationsCounter;				//0x8C Incremented each time we want to accelerate. Used to accelerate only 1 out 5 times
	uint8_t nDist;								//0x90
	uint8_t nDistMax;							//0x91
	uint8_t nIDAStarInitFScore;					//0x92 // Used only with PATHTYPE_IDASTAR
	uint8_t nStepNum;							//0x93
	uint8_t nDistance;							//0x94
	char padding0x95[3];						//0x95
	int32_t nDirOffset;							//0x98 See gaOffsetForPathType
	struct D2PathPoint PathPoints[D2DynamicPath_MAXPATHLEN];		//0x9C
	int32_t nSavedStepsCount;					//0x1D4
	struct D2PathPoint SavedSteps[D2DynamicPath_PATH_MAX_STEP_LEN];//0x1D8
};

struct D2PathInfo
{
	struct D2PathPoint tStartCoord;				//0x00
	struct D2PathPoint tTargetCoord;				//0x04
	struct D2ActiveRoom* pStartRoom;				//0x08
	struct D2ActiveRoom* pTargetRoom;				//0x0C
	int32_t field_10;							//0x10
	uint8_t field_14;							//0x14
	uint8_t field_15;							//0x15
	uint16_t field_16;							//0x16
	int32_t nDistMax;							//0x18
	uint8_t nMinimumFScoreToEvaluate;			//0x1C for IDAStar: max heuristic value or max FScore?
	uint8_t field_1D;							//0x1D
	uint16_t field_1E;							//0x1E
	int32_t nPathType;							//0x20
	int32_t nUnitSize;							//0x24
	int32_t nCollisionPattern;					//0x28
	int32_t nCollisionMask;						//0x2C
	union
	{
		struct D2DynamicPath* pDynamicPath;	//0x30 - not sure yet
		struct D2PathInfo* pNext;				//0x30
	};
};

struct D2StaticPath
{
	struct D2ActiveRoom* pRoom;				//0x00
	int32_t dwClientCoordX;					//0x04
	int32_t dwClientCoordY;					//0x08
	struct D2Coord tGameCoords;				//0x0C
	uint32_t unk0x14[2];					//0x14
	uint8_t nDirection;						//0x1C
	uint8_t bRoomNeedsUpdate;				//0x1D
	uint8_t unk0x1E[2];						//0x1E
};

struct D2MapAIPathPosition
{
	int32_t nMapAIAction;					//0x00
	int32_t nX;								//0x04
	int32_t nY;								//0x08
};

struct D2MapAI
{
	int32_t nPathNodes;						//0x00
	struct D2MapAIPathPosition* pPosition;		//0x04
};

#pragma pack()

// Path "precise" positions are encoded using 16bits fixed point
inline uint32_t PATH_ToFP16Corner(uint16_t value) {
	return (value << 16);
}
inline uint32_t PATH_ToFP16Center(uint16_t value) {
	return (value << 16) + (1 << 15);
}
// Called FRACTIONAL_TO_GAMESQUARE in the original game
inline uint16_t PATH_FromFP16(uint32_t value) {
	return (value >> 16) & 0xFFFF;
}
inline uint32_t PATH_FP16FitToCenter(uint32_t value)
{
	return (value & 0xFFFF0000) + (1 << 15);
}

// Helper functions
inline uint8_t PATH_NormalizeDirection(uint8_t nDirection) { return nDirection % PATH_NB_DIRECTIONS; }
void PATH_UpdateClientCoords(struct D2DynamicPath* pDynamicPath);

//D2Common.0x6FDA8220
void __cdecl sub_6FDA8220(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA82A0 (#10141)
D2COMMON_DLL_DECL void __cdecl PATH_GetClientCoordsVelocity(struct D2Unit* pUnit, int* pX, int* pY);
//D2Common.0x6FDA8320 (#10222)
D2COMMON_DLL_DECL void __cdecl PATH_AddCollisionFootprintForUnit(struct D2Unit* pUnit);
//D2Common.0x6FDA8450 (#10223)
D2COMMON_DLL_DECL BOOL __cdecl PATH_RemoveCollisionFootprintForUnit(struct D2Unit* pUnit, BOOL bForce);
//1.00:  D2Common.0x10059110 (#10141)
//1.10f: D2Common.0x6FDA8600 (#10142)
//1.13c: D2Common.0x6FD86230 (#10334)
D2COMMON_DLL_DECL int __cdecl D2Common_10142(struct D2DynamicPath* pPath, struct D2Unit* pUnit, int bAllowInTown);
//D2Common.0x6FDA8E30
int __cdecl PATH_ComputePathClassicMissile(struct D2DynamicPath* pDynamicPath, struct D2Unit* pUnit);
//D2Common.0x6FDA8FE0
void __cdecl PATH_FindValidTargetCoordsByMovingOrthogonally(struct D2PathInfo* pPathInfo);
//D2Common.0x6FDA90C0
uint8_t __cdecl PATH_AdvanceToDoor(struct D2PathInfo* pPathInfo);
//D2Common.0x6FDA9190 (#10156)
D2COMMON_DLL_DECL void __cdecl PATH_FreeDynamicPath(void* pMemPool, struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA91B0 (#11282)
D2COMMON_DLL_DECL int __cdecl PATH_GetCollisionPatternFromMonStats2Txt(int nMonsterId);
//D2Common.0x6FDA9250 (#11281)
D2COMMON_DLL_DECL int __cdecl D2Common_11281_CollisionPatternFromSize(struct D2Unit* pUnit, int nSize);
//D2Common.0x6FDA92F0 (#10214)
D2COMMON_DLL_DECL void __cdecl D2Common_10214(struct D2Unit* pUnit);
//D2Common.0x6FDA9480 (#10152)
D2COMMON_DLL_DECL void __cdecl PATH_AllocDynamicPath(void* pMemPool, struct D2ActiveRoom* pRoom, int nX, int nY, struct D2Unit* pUnit, BOOL bSetFlag);
//D2Common.0x6FDA9720
void __cdecl sub_6FDA9720(struct D2DynamicPath* pDynamicPath, uint8_t nDirection);
//D2Common.0x6FDA9770 (#10193)
D2COMMON_DLL_DECL void __cdecl D2COMMON_10193_PATH_AdjustDirection(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA97C0 (#10216)
D2COMMON_DLL_DECL void __cdecl D2Common_10216(struct D2DynamicPath* pDynamicPath, int nX, int nY, int a4);
//D2Common.0x6FDA9850 (#10228)
D2COMMON_DLL_DECL void __cdecl D2Common_10228(struct D2Unit* pUnit);
//D2Common.0x6FDA9870 (#10143)
D2COMMON_DLL_DECL void __cdecl PATH_SetUnitDeadCollision(struct D2Unit* pUnit, BOOL bForGameLogic);
//D2Common.0x6FDA98F0 (#10144)
D2COMMON_DLL_DECL void __cdecl PATH_SetUnitAliveCollision(struct D2Unit* pUnit, BOOL bForGameLogic);
//D2Common.0x6FDA9A70 (#10146)
D2COMMON_DLL_DECL void __cdecl PATH_SetVelocity(struct D2DynamicPath* pDynamicPath, int nVelocity, const char* szFile, int nLine);
//D2Common.0x6FDA9AB0 (#10147)
D2COMMON_DLL_DECL int __cdecl PATH_GetVelocity(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9AC0 (#10148)
D2COMMON_DLL_DECL void __cdecl PATH_SetMaxVelocity(struct D2DynamicPath* pDynamicPath, int nMaxVelocity);
//D2Common.0x6FDA9AE0 (#10149)
D2COMMON_DLL_DECL int __cdecl PATH_GetMaxVelocity(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9AF0 (#10150)
D2COMMON_DLL_DECL void __cdecl PATH_SetAcceleration(struct D2DynamicPath* pDynamicPath, int nAcceleration);
//D2Common.0x6FDA9B10 (#10151)
D2COMMON_DLL_DECL int __cdecl PATH_GetAcceleration(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9B20 (#10153)
D2COMMON_DLL_DECL void __cdecl D2Common_10153(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9B40 (#10208)
D2COMMON_DLL_DECL void __cdecl D2COMMON_10208_PathSetPathingFlag(struct D2DynamicPath* pDynamicPath, BOOL bSet);
//D2Common.0x6FDA9B70 (#10209)
D2COMMON_DLL_DECL BOOL __cdecl D2COMMON_10209_PathCheckPathingFlag(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9B80 (#10154)
D2COMMON_DLL_DECL int __cdecl PATH_GetNumberOfPathPoints(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9B90 (#11291)
D2COMMON_DLL_DECL void __cdecl PATH_SetNumberOfPathPoints(struct D2DynamicPath* pDynamicPath, int a2);
//D2Common.0x6FDA9BC0 (#10155)
D2COMMON_DLL_DECL int __cdecl D2Common_10155(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9BD0 (#10157)
D2COMMON_DLL_DECL int __cdecl PATH_GetPathPoints(struct D2DynamicPath* pDynamicPath, struct D2PathPoint** ppPathPoints);
//D2Common.0x6FDA9BF0 (#10158)
D2COMMON_DLL_DECL uint8_t __cdecl PATH_GetDirection(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9C10 (#10159)
D2COMMON_DLL_DECL uint8_t __cdecl PATH_GetNewDirection(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9C20 (#10160)
D2COMMON_DLL_DECL void __cdecl D2COMMON_10160_PathUpdateDirection(struct D2DynamicPath* pDynamicPath, uint8_t nDirection);
//D2Common.0x6FDA9C90 (#10161)
D2COMMON_DLL_DECL void __cdecl PATH_SetDirection(struct D2DynamicPath* pDynamicPath, uint8_t nDirection);
//D2Common.0x6FDA9CB0 (#10162)
D2COMMON_DLL_DECL int __cdecl PATH_GetXPosition(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9CF0 (#10163)
D2COMMON_DLL_DECL int __cdecl PATH_GetYPosition(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9D30 (#10194)
D2COMMON_DLL_DECL int __cdecl PATH_GetPrecisionX(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9D60 (#10195)
D2COMMON_DLL_DECL int __cdecl PATH_GetPrecisionY(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9D90 (#10196)
D2COMMON_DLL_DECL void __cdecl PATH_SetPrecisionX(struct D2DynamicPath* pDynamicPath, int nPrecisionX);
//D2Common.0x6FDA9DA0 (#10197)
D2COMMON_DLL_DECL void __cdecl PATH_SetPrecisionY(struct D2DynamicPath* pDynamicPath, int nPrecisionY);
//D2Common.0x6FDA9DB0 (#10164)
D2COMMON_DLL_DECL int __cdecl PATH_GetClientCoordX(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDC3CE0 (#10165)
D2COMMON_DLL_DECL int __cdecl PATH_GetClientCoordY(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9DC0
void __cdecl PATH_SetClientCoordX(struct D2DynamicPath* pDynamicPath, int nTargetX);
//D2Common.0x6FDA9DD0
void __cdecl PATH_SetClientCoordY(struct D2DynamicPath* pDynamicPath, int nTargetY);
//D2Common.0x6FDA9DE0 (#10175)
D2COMMON_DLL_DECL int __cdecl D2COMMON_10175_PathGetFirstPointX(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9DF0 (#10176)
D2COMMON_DLL_DECL int __cdecl D2COMMON_10176_PathGetFirstPointY(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9E00 (#10224)
D2COMMON_DLL_DECL int __cdecl D2Common_10224(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9E10 (#10225)
D2COMMON_DLL_DECL int __cdecl D2Common_10225(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9E20 (#10177)
D2COMMON_DLL_DECL int __cdecl D2COMMON_10177_PATH_GetLastPointX(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9E40 (#10178)
D2COMMON_DLL_DECL int __cdecl D2COMMON_10178_PATH_GetLastPointY(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDB9C10 (#10166)
D2COMMON_DLL_DECL struct D2ActiveRoom* __cdecl PATH_GetRoom(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9E60 (#10167)
D2COMMON_DLL_DECL void __cdecl PATH_SetRoom(struct D2DynamicPath* pDynamicPath, struct D2ActiveRoom* pRoom);
//D2Common.0x6FDA9E70 (#10168)
D2COMMON_DLL_DECL struct D2ActiveRoom* __cdecl PATH_GetNextRoom(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9E80 (#10169)
D2COMMON_DLL_DECL void __cdecl PATH_ClearNextRoom(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9E90 (#10170)
D2COMMON_DLL_DECL void __cdecl D2COMMON_10170_PathSetTargetPos(struct D2DynamicPath* pDynamicPath, int nX, int nY);
//D2Common.0x6FDA9EC0 (#10172)
D2COMMON_DLL_DECL BOOL __cdecl PATH_IsCurrentRoomInvalid(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9ED0 (#10173)
D2COMMON_DLL_DECL void __cdecl PATH_SetCurrentRoomInvalid(struct D2DynamicPath* pDynamicPath, BOOL bSet);
//D2Common.0x6FDA9F00 (#10145)
D2COMMON_DLL_DECL void __cdecl PATH_SetUnusedFlag_0x00004(struct D2DynamicPath* pDynamicPath, BOOL bSet);
//D2Common.0x6FDA9F30 (#10174)
D2COMMON_DLL_DECL BOOL __cdecl PATH_GetUnusedFlag_0x00004(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9F40 (#10179)
D2COMMON_DLL_DECL void __cdecl PATH_SetTargetUnit(struct D2DynamicPath* pDynamicPath, struct D2Unit* pUnit);
//D2Common.0x6FDA9F60 (#10171)
D2COMMON_DLL_DECL void __cdecl PATH_GetTargetTypeAndGUID(struct D2DynamicPath* pDynamicPath, int* pTargetType, D2UnitGUID* pTargetGUID);
//D2Common.0x6FDA9FA0 (#10180)
D2COMMON_DLL_DECL struct D2Unit* __cdecl PATH_GetTargetUnit(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9FC0 (#10181)
D2COMMON_DLL_DECL int __cdecl PATH_GetFootprintCollisionMask(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDA9FE0 (#10182)
D2COMMON_DLL_DECL void __cdecl PATH_SetFootprintCollisionMask(struct D2DynamicPath* pDynamicPath, int nCollisionMask);
//D2Common.0x6FDAA0C0 (#10183)
D2COMMON_DLL_DECL int __cdecl PATH_GetMoveTestCollisionMask(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDAA0D0 (#10184)
D2COMMON_DLL_DECL void __cdecl PATH_SetMoveTestCollisionMask(struct D2DynamicPath* pDynamicPath, int nCollisionMask);
//D2Common.0x6FDAA0E0 (#10185)
D2COMMON_DLL_DECL void __cdecl PATH_SetType(struct D2DynamicPath* pDynamicPath, int nPathType);
//D2Common.0x6FDAA1E0 (#10186)
D2COMMON_DLL_DECL void __cdecl PATH_ResetToPreviousType(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDAA240 (#10187)
D2COMMON_DLL_DECL int __cdecl PATH_GetType(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDAA250 (#10190)
D2COMMON_DLL_DECL void __cdecl D2COMMON_10190_PATH_SetDistance(struct D2DynamicPath* pDynamicPath, uint8_t nDistance);
//D2Common.0x6FDAA270 (#10191)
D2COMMON_DLL_DECL uint8_t __cdecl D2COMMON_10191_PATH_GetDistance(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDAA280 (#10188)
D2COMMON_DLL_DECL void __cdecl PATH_SetNewDistance(struct D2DynamicPath* pDynamicPath, uint8_t nNewDistance);
//D2Common.0x6FDAA2B0 (#10189)
D2COMMON_DLL_DECL uint8_t __cdecl PATH_GetMaxDistance(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDAA2C0 (#10201)
D2COMMON_DLL_DECL uint16_t __cdecl D2Common_10201(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDAA300 (#10202)
D2COMMON_DLL_DECL uint16_t __cdecl D2Common_10202(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDAA310 (#10192)
D2COMMON_DLL_DECL void __cdecl PATH_SetIDAStarInitFScore(struct D2DynamicPath* pDynamicPath, int nIDAStarInitFScore);
//D2Common.0x6FDAA350 (#10198)
D2COMMON_DLL_DECL int __cdecl D2COMMON_10198_PathGetSaveStep(struct D2DynamicPath* pDynamicPath, struct D2PathPoint** ppPathPoints);
//D2Common.0x6FDAA390 (#10199)
D2COMMON_DLL_DECL int __cdecl D2COMMON_10199_PathGetSaveX(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDAA3E0 (#10200)
D2COMMON_DLL_DECL int __cdecl D2COMMON_10200_PathGetSaveY(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDAA430 (#10203)
D2COMMON_DLL_DECL void __cdecl D2COMMON_10203_PATH_SetRotateFlag(struct D2DynamicPath* pDynamicPath, BOOL bReset);
//D2Common.0x6FDAA460 (#10204)
D2COMMON_DLL_DECL void __cdecl D2COMMON_10204_PATH_ClearPoint2(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDAA480 (#10205)
D2COMMON_DLL_DECL void __cdecl PATH_SetStepNum(struct D2DynamicPath* pDynamicPath, uint8_t nSteps);
//D2Common.0x6FDAA4B0 (#10206)
D2COMMON_DLL_DECL int __cdecl PATH_GetStepNum(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDAA4C0 (#10207)
D2COMMON_DLL_DECL void __cdecl D2Common_10207(struct D2DynamicPath* pDynamicPath, char a2, char a3);
//D2Common.0x6FDAA4E0 (#10217)
D2COMMON_DLL_DECL void __cdecl PATH_SetDistance(struct D2DynamicPath* pDynamicPath, int nDist);
//D2Common.0x6FDAA520 (#10218)
D2COMMON_DLL_DECL int __cdecl PATH_GetDistance(struct D2DynamicPath* pDynamicPath);
//D2Common.0x6FDAA530 (#10219)
D2COMMON_DLL_DECL void __cdecl PATH_AddToDistance(struct D2DynamicPath* pDynamicPath, int nAddition);
//D2Common.0x6FDAA570 (#10210)
D2COMMON_DLL_DECL int __cdecl PATH_GetUnitCollisionPattern(struct D2Unit* pUnit);
//D2Common.0x6FDAA580 (#10211)
D2COMMON_DLL_DECL void __cdecl PATH_SetUnitCollisionPattern(struct D2Unit* pUnit, int nCollisionPattern);
//D2Common.0x6FDAA5A0 (#10212)
D2COMMON_DLL_DECL void __cdecl D2COMMON_10212_PATH_SetMoveFlags(struct D2Unit* pUnit, BOOL bSet);
//D2Common.0x6FDAA600 (#10213)
D2COMMON_DLL_DECL void __cdecl D2Common_10213(struct D2Unit* pUnit);
//D2Common.0x6FDAA6A0 (#10220)
D2COMMON_DLL_DECL int __cdecl PATH_ComputeSquaredDistance(int nX1, int nY1, int nX2, int nY2);
//D2Common.0x6FDAA6D0 (#10221)
D2COMMON_DLL_DECL void __cdecl PATH_AddCollisionFootprintForOptionalUnit(struct D2Unit* pUnit);
//D2Common.0x6FDAA6F0 (#10237)
D2COMMON_DLL_DECL BOOL __cdecl D2Common_10237(struct D2Unit* pUnit);
