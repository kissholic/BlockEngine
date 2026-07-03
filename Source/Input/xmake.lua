target("Input")
    set_kind("static")
    add_deps("Core", "Platform")
    add_files("Input.mpp", {public = true})
