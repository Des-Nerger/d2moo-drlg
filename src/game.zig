const std = @import("std");
const mem = std.mem;

pub const Strc = struct {
	allocator: mem.Allocator,
	bExpansion: bool,
	dwInitSeed: u32,
};
