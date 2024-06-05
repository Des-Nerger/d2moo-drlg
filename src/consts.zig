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

pub const TownId = ?enum(i31) {
	rogueCamp = 1,
	lutGhol = 40,
	kurast = 75,
	pandFort = 103,
	harro = 109,
};
