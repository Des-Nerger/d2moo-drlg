const mem = std.mem;
const std = @import("std");

pub const Strc = struct {
	allocator: mem.Allocator,
	bExpansion: bool,
	dwInitSeed: u32,
};
