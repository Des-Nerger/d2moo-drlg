const Build = std.Build;
const builtin = @import("builtin");
const std = @import("std");

pub fn build(b: *Build) void {
    const exe = b.addExecutable(.{
        .name = "d2moo-drlg",
        .root_module = b.createModule(.{
            .root_source_file = b.path("src/main.zig"),
            .target = b.resolveTargetQuery(.{ .cpu_arch = .x86, .os_tag = .windows }),
            .optimize = b.standardOptimizeOption(.{ .preferred_optimize_mode = .ReleaseSafe }),
        }),
    });
    exe.linkLibC();
    exe.addIncludePath(b.path("include"));
    for ([_]struct { []const u8, []const u8 }{
        .{ "FOG_DLL_DECL", "" },
        .{ "D2COMMON_DLL_DECL", "" },
        .{ "D2LANG_DLL_DECL", "" },
        .{ "D2CMP_DLL_DECL", "" },
    }) |key_value|
        @call(.auto, Build.Module.addCMacro, .{exe.root_module} ++ key_value);
    exe.addCSourceFiles(.{
        .flags = &.{ "-O", "-std=c23" },
        .root = b.path("src"),
        .files = &.{
            "D2Seed.c",
            "Drlg/DrlgDrlg.c",
            // "Drlg/DrlgDrlgGrid.c",
            // "Drlg/DrlgDrlgRoom.c",
            // "Drlg/DrlgDrlgVer.c",
            // "Drlg/DrlgOutRoom.c",
            // "Drlg/DrlgPreset.c",
            // "Drlg/DrlgRoomTile.c",
        },
    });
    b.installArtifact(exe);

    const run_cmd = if (builtin.os.tag != .windows and builtin.cpu.arch == .x86_64)
        b.addSystemCommand(&.{ "wine", "zig-out/bin/d2moo-drlg.exe" })
    else
        b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    b.step("run", "Run the app").dependOn(&run_cmd.step);
}
