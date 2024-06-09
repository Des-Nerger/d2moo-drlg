const consts = @import("consts.zig");
const debug = std.debug;
const drlg = @import("drlg.zig");
const game = @import("game.zig");
const heap = std.heap;
const std = @import("std");

pub fn main() !void {
	var gpa = heap.GeneralPurposeAllocator(.{}){};
	defer _ = gpa.deinit();
	var arena = heap.ArenaAllocator.init(gpa.allocator());
	defer arena.deinit();
	const allocator = arena.allocator();

	const pAct = try allocator.create(drlg.ActStrc);
	pAct.* = blk: {
		const nAct = consts.Act.I;
		break :blk .{
			.allocator = allocator,
			.dwInitSeed = 0,
			.nAct = nAct,
			.nTownId = consts.townIds[@intFromEnum(nAct)],
		};
	};

	const pGame = try allocator.create(game.Strc);
	pGame.* = .{
		.allocator = allocator,
		.dwInitSeed = pAct.dwInitSeed,
		.bExpansion = true,
	};

	const pDrlg = try allocator.create(drlg.Strc);
	pDrlg.* = try pAct.initDrlg(
		drlg.Flags{
			.onClient = false,
			.refresh = false,
		},
		pGame,
		consts.Difficulty.normal,
	);

	debug.print("{any}\n", .{pDrlg.tStatusRoomsLists});
}
