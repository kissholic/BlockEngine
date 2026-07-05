rule("sokol.shdc")
    set_extensions(".glsl")
    on_buildcmd_file(function(target, batchcmds, sourcefile, opt)
        local tool = "sokol-shdc"
        local args = {
            "--input", sourcefile,
            "--output", sourcefile .. ".h",
            "--slang", "metal_macos:glsl430:hlsl5",
            "--format", "sokol_impl",
        }
        batchcmds:add_depfiles(sourcefile)
        batchcmds:mkdir(path.directory(sourcefile .. ".h"))
        batchcmds:show_progress(opt.progress, "${color.build.object}compiling.shader %s", sourcefile)
        batchcmds:execv(tool, args)
    end)

target("shaders")
    set_kind("object")
    add_rules("sokol.shdc")
    add_files("$(projectdir)/Assets/Shaders/*.glsl")
