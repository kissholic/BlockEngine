

add_requires("glfw", "glad")
add_requires("glm")
add_requires("spdlog")
add_requires("concurrencpp")
add_requires("imgui", {configs = {glfw=true, opengl3=true}})
add_requires("box2d")


includes("Camera")
includes("Graphics")
includes("Input")


target("Main")
    set_kind("binary")
    add_files("*.cpp")
    add_deps("Graphics", "Input")
    add_packages("spdlog", "glad", "glfw", "concurrencpp")
    add_cxxflags("-g")
    

