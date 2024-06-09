pub fn asOptional(a: anytype) ?@TypeOf(a) {
	return a;
}

pub fn enumCount(comptime E: type) comptime_int {
	return @typeInfo(E).Enum.fields.len;
}
