const consts = @import("consts.zig");
const dataTbls = struct {
	usingnamespace @import("dataTbls/level_ids.zig");
};
const enumCount = zigUtils.enumCount;
const game = @import("game.zig");
const mem = std.mem;
const std = @import("std");
const zigUtils = @import("zigUtils.zig");
const FormatOptions = std.fmt.FormatOptions;

pub const Flags = packed struct(u32) {
	onClient: bool,
	__: u3 = 0,
	refresh: bool,
	_: u27 = 0,
};

// Note: Lower value has priority over others
pub const RoomStatus = enum(u8) {
	clientInRoom,
	clientInSight,
	clientOutOfSight,
	untile,
};

// Used to be called D2RoomExStrc
const RoomStrc = struct {
	nRoomStatus: RoomStatus,
	pStatusNext: *Self,
	pStatusPrev: *Self,

	const Self = @This();

	pub fn format(pRoom: *const Self, comptime _: []const u8, _: FormatOptions, writer: anytype) !void {
		try writer.print(@typeName(Self) ++
			\\{{
			\\    nRoomStatus = {},
			\\    pStatusNext = {*},
			\\    pStatusPrev = {*},
			\\}}
		, pRoom.*);
	}
};

pub const Strc = struct {
	npLevel: ?*LevelStrc, // Latest added level
	allocator: mem.Allocator,
	pAct: *ActStrc,
	nAct: consts.Act,
	dwFlags: Flags,
	tStatusRoomsLists: [enumCount(RoomStatus)]RoomStrc,
	pGame: *game.Strc,
	nDifficulty: consts.Difficulty,

	pub usingnamespace @import("drlg/activate.zig").DrlgExt;
	pub usingnamespace @import("drlg/outPlace.zig").DrlgExt;

	const Self = @This();

	fn getLevel(pDrlg: *Self, nLevelId: dataTbls.LevelId) !*LevelStrc {
		var npLevel = pDrlg.npLevel;
		while (npLevel) |pLevel| : (npLevel = pLevel.npNextLevel)
			if (pLevel.nLevelId == nLevelId)
				return pLevel;
		return pDrlg.allocLevel(nLevelId);
	}

	fn allocLevel(pDrlg: *Self, nLevelId: dataTbls.LevelId) !*LevelStrc {
		const pLevel = try pDrlg.allocator.create(LevelStrc);
		pLevel.* = .{
			.nLevelId = nLevelId,
			.npNextLevel = pDrlg.npLevel,
		};
		pDrlg.npLevel = pLevel;
		return pLevel;
	}
};

pub const ActStrc = struct {
	allocator: mem.Allocator,
	nAct: consts.Act,
	dwInitSeed: u32,
	nTownId: dataTbls.LevelId,

	const Self = @This();

	pub fn initDrlg(
		pAct: *Self,
		dwFlags: Flags,
		pGame: *game.Strc,
		nDifficulty: consts.Difficulty,
	) !Strc {
		var tDrlg = Strc{
			.npLevel = null,
			.pAct = pAct,
			.allocator = pAct.allocator,
			.nAct = pAct.nAct,
			.dwFlags = dwFlags,
			.pGame = pGame,
			.nDifficulty = nDifficulty,
			.tStatusRoomsLists = undefined,
		};
		tDrlg.initializeRoomExStatusLists();
		tDrlg.createLevelConnections();
		if (pAct.nTownId != .none)
			(try tDrlg.getLevel(pAct.nTownId)).init();
		return tDrlg;
	}
};

const LevelStrc = struct {
	nLevelId: dataTbls.LevelId,
	npNextLevel: ?*Self,

	const Self = @This();

	fn init(pLevel: *Self) void {
		_ = pLevel;
	}
};
