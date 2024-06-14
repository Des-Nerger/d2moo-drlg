const fields = @import("std").meta.fields;

pub fn asArrayOf(comptime T: type, comptime tuples: anytype) [tuples.len]T {
	var structs: [tuples.len]T = undefined;
	for (&structs, tuples) |*@"struct", tuple| {
		inline for (fields(T), fields(@TypeOf(tuple))) |structField, tupleField| {
			@field(@"struct", structField.name) = @field(tuple, tupleField.name);
		}
	}
	return structs;
}
