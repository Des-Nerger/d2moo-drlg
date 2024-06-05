const constants = @import("consts.zig");
const drlg = @import("drlg/drlg.zig");
const game = @import("game.zig");
const std = @import("std");

const debug = std.debug;
const heap = std.heap;
const Act = constants.Act;
const Difficulty = constants.Difficulty;
const TownId = constants.TownId;

pub fn main() !void {
	var gpa = heap.GeneralPurposeAllocator(.{}){};
	defer _ = gpa.deinit();
	var arena = heap.ArenaAllocator.init(gpa.allocator());
	defer arena.deinit();
	const allocator = arena.allocator();

	const dwInitSeed: u32 = 0;
	const nDifficulty = Difficulty.normal;
	const nAct = Act.I;
	const nTownId: TownId =
		@enumFromInt(@typeInfo(@typeInfo(TownId).Optional.child).Enum.fields[@intFromEnum(nAct)].value);
	debug.print("{} {} {} {?}\n", .{ dwInitSeed, nDifficulty, nAct, nTownId });

	const pAct = try allocator.create(drlg.ActStrc);
	pAct.* = .{
		.allocator = allocator,
		.nAct = nAct,
		.dwInitSeed = dwInitSeed,
		.nTownId = nTownId,
	};

	const pGame = try allocator.create(game.Strc);
	pGame.* = .{
		.allocator = allocator,
		.dwInitSeed = dwInitSeed,
		.bExpansion = true,
	};

	const pDrlg = try allocator.create(drlg.Strc);
	pDrlg.* = drlg.Strc.init(
		pAct,
		nAct,
		dwInitSeed,
		nTownId,
		drlg.Flags{
			.onClient = false,
			.refresh = false,
		},
		pGame,
		nDifficulty,
	);

	debug.print("{}\n", .{pDrlg});
}
