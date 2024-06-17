const consts = @import("consts.zig");
const dataTbls = struct {
	usingnamespace @import("dataTbls/level_ids.zig");
};
const fields = std.meta.fields;
const fmt = std.fmt;
const game = @import("game.zig");
const mem = std.mem;
const outPlace = @import("drlg/outPlace.zig");
const seed = @import("seed.zig");
const std = @import("std");
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

	pub fn format(pRoom: *const Self, comptime _: []const u8, options: FormatOptions, writer: anytype) !void {
		try writer.writeAll(@typeName(Self));
		try writer.writeAll("{");
		inline for (@typeInfo(Self).Struct.fields, 0..) |field, i| {
			try writer.writeAll(",\n    ."[@intFromBool(i == 0)..]);
			try writer.writeAll(field.name);
			try writer.writeAll(" = ");
			try fmt.formatType(
				@field(pRoom, field.name),
				if (@typeInfo(field.type) == .Pointer) "*" else "any",
				options,
				writer,
				std.options.fmt_max_depth - 1,
			);
		}
		try writer.writeAll("\n}");
	}
};

pub const Strc = struct {
	allocator: mem.Allocator,
	dwFlags: Flags,
	dwGameLowSeed: u32,
	dwStartSeed: u32,
	nAct: consts.Act,
	nDifficulty: consts.Difficulty,
	pAct: *ActStrc,
	pGame: *game.Strc,
	pLevel: ?*LevelStrc, // Latest added level
	tSeed: seed.Strc,
	tStatusRoomsLists: [fields(RoomStatus).len]RoomStrc,

	pub usingnamespace @import("drlg/activate.zig").DrlgExt;
	pub usingnamespace outPlace.DrlgExt;

	const Self = @This();

	fn getLevel(pDrlg: *Self, nLevelId: dataTbls.LevelId) !*LevelStrc {
		var pNextLevel = pDrlg.pLevel;
		while (pNextLevel) |pLevel| : (pNextLevel = pLevel.pNextLevel)
			if (pLevel.nLevelId == nLevelId)
				return pLevel;
		return pDrlg.allocLevel(nLevelId);
	}

	fn allocLevel(pDrlg: *Self, nLevelId: dataTbls.LevelId) !*LevelStrc {
		const pLevel = try pDrlg.allocator.create(LevelStrc);
		pLevel.* = .{
			.nLevelId = nLevelId,
			.pNextLevel = pDrlg.pLevel,
		};
		pDrlg.pLevel = pLevel;
		return pLevel;
	}
};

pub const ActStrc = struct {
	allocator: mem.Allocator,
	dwInitSeed: u32,
	nAct: consts.Act,
	nTownId: dataTbls.LevelId,

	const Self = @This();

	pub fn allocDrlg(
		pAct: *Self,
		dwFlags: Flags,
		pGame: *game.Strc,
		nDifficulty: consts.Difficulty,
	) !*Strc {
		var pDrlg = try pAct.allocator.create(Strc);
		pDrlg.* = .{
			.pAct = pAct,
			.allocator = pAct.allocator,
			.nAct = pAct.nAct,
			.tSeed = seed.Strc.initLowSeed(pAct.dwInitSeed),
			.dwStartSeed = @truncate(pDrlg.tSeed.rollRandomNumber()),
			.dwFlags = dwFlags,
			.pGame = pGame,
			.dwGameLowSeed = pAct.dwInitSeed,
			.nDifficulty = nDifficulty,
			.pLevel = null,
			.tStatusRoomsLists = undefined,
		};
		pDrlg.initializeRoomExStatusLists();
		pDrlg.createLevelConnections(pAct.nAct);
		if (pAct.nTownId != .none)
			(try pDrlg.getLevel(pAct.nTownId)).init();
		return pDrlg;
	}
};

pub const LevelStrc = struct {
	nLevelId: dataTbls.LevelId,
	pNextLevel: ?*Self,

	pub usingnamespace outPlace.LevelExt;

	const Self = @This();

	fn init(pLevel: *Self) void {
		_ = pLevel;
	}
};

pub const LinkStrc = struct {
	fnLinker: *const fn (*LevelLinkDataStrc) bool,
	nLevel: dataTbls.LevelId,
	nLevelLink: i32,
	nLevelLinkEx: i32,
};

pub const LevelLinkDataStrc = struct {
	pub usingnamespace outPlace.LevelLinkData_Ext;
};
