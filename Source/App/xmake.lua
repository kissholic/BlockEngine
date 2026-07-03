target("BlockEngine")
    set_kind("binary")
    add_deps("Engine", "Platform")
    add_files("Main.cpp")
