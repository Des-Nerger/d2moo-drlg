pub const Strc = packed struct(u64) {
	nLowSeed: u32,
	nHighSeed: u32,

	const Self = @This();

	pub fn initLowSeed(nLowSeed: u32) Self {
		return .{
			.nLowSeed = nLowSeed,
			.nHighSeed = 666,
		};
	}

	pub fn rollRandomNumber(pSeed: *Self) u64 {
		const lSeed: u64 = pSeed.nHighSeed + 0x6AC690C5 * pSeed.nLowSeed;
		pSeed.* = @bitCast(lSeed);
		return lSeed;
	}
};
