

target("Graphics")
    set_kind("static")
    add_files("*.cpp")
    add_packages("spdlog", "glfw", "glad")
    
