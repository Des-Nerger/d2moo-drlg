pub usingnamespace @cImport({
    @cInclude("c.h");
});

comptime {
    for (.{
        @import("d2cmp.zig"),
        @import("d2lang.zig"),
        @import("fog.zig"),
        @import("storm.zig"),
    }) |Struct|
        for (@typeInfo(Struct).@"struct".decls) |decl| {
            const field = @field(Struct, decl.name);
            if (@TypeOf(field) != @TypeOf(@field(@This(), decl.name)))
                @compileError("decl type mismatch: " ++ decl.name);
            @export(&field, .{ .name = decl.name, .linkage = .strong });
        };
}
