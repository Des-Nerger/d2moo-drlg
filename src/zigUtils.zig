const fields = @import("std").meta.fields;

pub fn arrayOfStructs(
	comptime Struct: type,
	comptime structFieldNames: [fields(Struct).len][]const u8,
	comptime tuples: anytype,
) [tuples.len]Struct {
	var structs: [tuples.len]Struct = undefined;
	for (&structs, tuples) |*@"struct", tuple| {
		inline for (structFieldNames, fields(@TypeOf(tuple))) |structFieldName, tupleField|
			@field(@"struct", structFieldName) = @field(tuple, tupleField.name);
	}
	return structs;
}
