const enumCount = @import("zigUtils.zig").enumCount;
const LevelId = @import("dataTbls/level_ids.zig").LevelId;

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

pub const townIds = [enumCount(Act)]LevelId{
	.rogueEncampment,
	.lutGholein,
	.kurastDockTown,
	.thePandemoniumFortress,
	.harrogath,
};
