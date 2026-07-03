set_project("BlockEngine")
set_version("0.2.0")
set_languages("c++23")

add_includedirs("$(projectdir)/Source")
add_includedirs("$(projectdir)/external/sokol")
add_includedirs("$(projectdir)/external/sokol/util")
add_includedirs("$(projectdir)/external/soloud/include")

includes("Source")
