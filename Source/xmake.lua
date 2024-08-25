

add_requires("glfw", "glad")
add_requires("glm")
add_requires("spdlog")

includes("Graphics")


target("Main")
    set_kind("binary")
    add_files("*.cpp")
    add_deps("Graphics")
    add_packages("spdlog", "glad", "glfw")
    add_cxxflags("-g")
    

