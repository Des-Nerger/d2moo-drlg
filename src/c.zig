pub usingnamespace @cImport({
    @cInclude("Drlg/D2DrlgDrlg.h");
});

comptime {
    for (.{
        @import("d2cmp.zig"),
        @import("fog.zig"),
    }) |Struct|
        for (@typeInfo(Struct).@"struct".decls) |decl| {
            const field = @field(Struct, decl.name);
            if (@TypeOf(field) != @TypeOf(@field(@This(), decl.name)))
                @compileError("decl type mismatch: " ++ decl.name);
            @export(&field, .{ .name = decl.name, .linkage = .strong });
        };
}
