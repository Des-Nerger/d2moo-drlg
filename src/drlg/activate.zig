const drlg = @import("../drlg.zig");
const enums = std.enums;
const std = @import("std");

pub const DrlgExt = struct {
	const Self = drlg.Strc;

	pub fn initializeRoomExStatusLists(pDrlg: *Self) void {
		for (enums.values(drlg.RoomStatus), &pDrlg.tStatusRoomsLists) |nRoomStatus, *pDrlgRoomStatusList| {
			pDrlgRoomStatusList.nRoomStatus = nRoomStatus;
			pDrlgRoomStatusList.pStatusNext = pDrlgRoomStatusList;
			pDrlgRoomStatusList.pStatusPrev = pDrlgRoomStatusList;
		}
	}
};
