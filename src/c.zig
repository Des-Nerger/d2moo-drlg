pub usingnamespace @cImport({
    @cInclude("D2Lang.h");
    @cInclude("Drlg/D2DrlgDrlg.h");
    @cInclude("Storm.h");
});

comptime {
    for (.{
        @import("d2CMP.zig"),
        @import("d2Lang.zig"),
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
