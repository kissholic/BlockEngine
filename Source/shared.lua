add_rules("mode.debug", "mode.release")
add_requires("imgui v1.92.5-docking")
add_requires("stb")
add_requires("spdlog")
add_requires("glm")

set_warnings("all", "extra")
set_policy("build.warning", true)

if is_mode("debug") then
    add_defines("BE_DEBUG")
    set_optimize("none")
else
    set_optimize("fastest")
end
