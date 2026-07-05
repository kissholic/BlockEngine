target("Shader")
    set_kind("static")
    add_deps("Core", "Platform")
    add_files("Shader.mpp", {public = true})
