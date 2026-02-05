

-- add_requires("glfw", "glad")
-- add_requires("glm")
add_requires("libsdl3")
add_requires("libsdl3_image")
add_requires("spdlog")
-- add_requires("concurrencpp")
add_requires("imgui", {configs = {libsdl3=true}})
add_requires("box2d")
-- add_requires("bgfx")

add_includedirs("$(projectdir)/Include")


-- includes("Component")
-- includes("Camera")
-- includes("GameObject")
includes("Graphics")
-- includes("Input")


target("Main")
    set_kind("binary")
    add_files("*.cpp")
    add_deps("Graphics")
    add_packages("spdlog", "libsdl3")
    add_cxxflags("-g")
    

