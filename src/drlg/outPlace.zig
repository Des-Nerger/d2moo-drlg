const assert = debug.assert;
const asArrayOf = @import("../zigUtils.zig").asArrayOf;
const consts = @import("../consts.zig");
const dataTbls = struct {
	usingnamespace @import("../dataTbls/level_ids.zig");
};
const debug = @import("std").debug;
const drlg = @import("../drlg.zig");

pub const DrlgExt = struct {
	const Self = drlg.Strc;

	pub fn createLevelConnections(pDrlg: *Self, nAct: consts.Act) void {
		assert(nAct == .I);
		pDrlg.sub_6FD823C0(
			LevelLinkData_Ext.act1WildernessDrlgLink,
			LevelLinkData_Ext.sub_6FD82050,
			LevelExt.sub_6FD82360,
		);
		pDrlg.sub_6FD82750(.rogueEncampment, .burialGrounds);
	}

	pub fn sub_6FD823C0(
		pDrlg: *Self,
		pDrlgLink: []const drlg.LinkStrc,
		a3: *const fn (*drlg.LevelLinkDataStrc, i32) bool,
		a4: *const fn (*drlg.LevelStrc, i32, *i32) void,
	) void {
		debug.print("pDrlgLink = {any}\n", .{pDrlgLink});
		_ = pDrlg;
		// _ = pDrlgLink;
		_ = a3;
		_ = a4;
	}

	pub fn sub_6FD82750(pDrlg: *Self, nStartId: dataTbls.LevelId, nEndId: dataTbls.LevelId) void {
		_ = pDrlg;
		_ = nStartId;
		_ = nEndId;
	}
};

pub const LevelExt = struct {
	const Self = drlg.LevelStrc;

	fn sub_6FD82360(pLevel: *Self, nIteration: i32, pRand: *i32) void {
		_ = pLevel;
		_ = nIteration;
		_ = pRand;
	}
};

pub const LevelLinkData_Ext = struct {
	const Self = drlg.LevelLinkDataStrc;

	fn sub_6FD82050(pLevelLinkData: *Self, nIteration: i32) bool {
		_ = pLevelLinkData;
		_ = nIteration;
		return undefined;
	}

	// zig fmt: off
	const act1WildernessDrlgLink = &asArrayOf(drlg.LinkStrc, .{
		.{ sub_6FD81330,      .stonyField, -1, -1 },
		.{ sub_6FD81380,      .coldPlains,  0, -1 },
		.{ sub_6FD81950,       .bloodMoor,  1, -1 },
		.{ sub_6FD81720, .rogueEncampment,  2, -1 },
		.{ sub_6FD81380,   .burialGrounds,  1, -1 },
	});
	// zig fmt: on

	fn sub_6FD81330(pLevelLinkData: *Self) bool {
		_ = pLevelLinkData;
		return undefined;
	}

	fn sub_6FD81380(pLevelLinkData: *Self) bool {
		_ = pLevelLinkData;
		return undefined;
	}

	fn sub_6FD81950(pLevelLinkData: *Self) bool {
		_ = pLevelLinkData;
		return undefined;
	}

	fn sub_6FD81720(pLevelLinkData: *Self) bool {
		_ = pLevelLinkData;
		return undefined;
	}
};
