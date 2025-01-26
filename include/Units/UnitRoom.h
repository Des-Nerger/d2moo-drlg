#pragma once

#include "D2CommonDefinitions.h"

struct D2ActiveRoom;
struct D2Unit;

#pragma pack(1)



#pragma pack()

//D2Common.0x6FDBCF10 (#11279)
D2COMMON_DLL_DECL int __cdecl UNITROOM_AddUnitToRoomEx(struct D2Unit* pUnit, struct D2ActiveRoom* pRoom, int nUnused);
//D2Common.0x6FDBD100 (#10384)
D2COMMON_DLL_DECL int __cdecl UNITROOM_AddUnitToRoom(struct D2Unit* pUnit, struct D2ActiveRoom* pRoom);
//D2Common.0x6FDBD120 (#10385)
D2COMMON_DLL_DECL void __cdecl UNITROOM_RefreshUnit(struct D2Unit* pUnit);
//D2Common.0x6FDBD1B0 (#10388)
D2COMMON_DLL_DECL void __cdecl UNITROOM_SortUnitListByTargetY(struct D2ActiveRoom* pRoom);
//D2Common.0x6FDBD250 (#10390)
D2COMMON_DLL_DECL void __cdecl UNITROOM_UpdatePath(struct D2Unit* pUnit);
//D2Common.0x6FDBD2B0 (#10391)
D2COMMON_DLL_DECL void __cdecl UNITROOM_ClearUpdateQueue(struct D2ActiveRoom* pRoom);
//D2Common.0x6FDBD300 (#10386)
D2COMMON_DLL_DECL void __cdecl UNITROOM_RemoveUnitFromRoom(struct D2Unit* pUnit);
//D2Common.0x6FDBD400 (#10387)
D2COMMON_DLL_DECL void __cdecl UNITROOM_RemoveUnitFromUpdateQueue(struct D2Unit* pUnit);
//D2Common.0x6FDBD4C0 (#10389)
D2COMMON_DLL_DECL BOOL __cdecl UNITROOM_IsUnitInRoom(struct D2ActiveRoom* pRoom, struct D2Unit* pUnit);
