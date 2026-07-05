target("BlockEngine")
    set_kind("binary")
    add_deps("Engine", "Platform", "Scene")
    add_files("Main.cpp")
