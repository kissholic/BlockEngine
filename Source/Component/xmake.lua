

target("Component")
    set_kind("static")
    add_files("*.cpp")
    add_packages("glm", "glfw", "glad")
