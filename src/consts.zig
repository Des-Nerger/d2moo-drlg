const fields = @import("std").meta.fields;
const LevelId = @import("dataTbls/level_ids.zig").LevelId;

pub const townIds = [fields(Act).len]LevelId{
	.rogueEncampment,
	.lutGholein,
	.kurastDockTown,
	.thePandemoniumFortress,
	.harrogath,
};

pub const Act = enum(u8) {
	I,
	II,
	III,
	IV,
	V,
};

pub const Difficulty = enum(u8) {
	normal,
	nightmare,
	hell,
};
