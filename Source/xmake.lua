

add_requires("bgfx")
add_requires("box2d")
add_requires("glfw", "glad")
add_requires("glm")
add_requires("spdlog")

includes("Graphics")


target("Main")
    set_kind("binary")
    add_files("*.cpp")
    add_deps("Graphics")
    add_packages("spdlog")
    add_cxxflags("-g")

