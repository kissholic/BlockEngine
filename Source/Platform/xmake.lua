target("Platform")
    set_kind("static")
    add_deps("Core")
    add_packages("stb", "imgui")
    add_files("Platform.mpp", {public = true})
    add_files("SokolApp.cpp")
    add_files("SokolImpl.mm")
    if is_plat("macosx") then
        add_frameworks("Metal", "MetalKit", "QuartzCore", "Cocoa")
        add_defines("SOKOL_METAL")
    elseif is_plat("windows") then
        add_defines("SOKOL_D3D11")
    elseif is_plat("linux") then
        add_defines("SOKOL_GLCORE33")
    end
