const consts = @import("../consts.zig");
const game = @import("../game.zig");
const std = @import("std");
const mem = std.mem;

const Act = consts.Act;
const Difficulty = consts.Difficulty;
const TownId = consts.TownId;

pub const Flags = packed struct(u32) {
	onClient: bool,
	__: u3 = 0,
	refresh: bool,
	_: u27 = 0,
};

pub const ActStrc = struct {
	allocator: mem.Allocator,
	nAct: Act,
	dwInitSeed: u32,
	nTownId: TownId,
};

const ActiveRoomStrc = struct {};

pub const Strc = struct {
	allocator: mem.Allocator,

	pub fn init(
		pAct: *ActStrc,
		nAct: Act,
		nInitSeed: u32,
		nTownId: TownId,
		nFlags: Flags,
		pGame: *game.Strc,
		nDifficulty: Difficulty,
	) @This() {
		_ = nAct;
		_ = nInitSeed;
		_ = nTownId;
		_ = nFlags;
		_ = pGame;
		_ = nDifficulty;
		return .{
			.allocator = pAct.allocator,
		};
	}
};
