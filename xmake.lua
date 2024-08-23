set_project("BlockEngine")


set_languages("c++20")
set_warnings("all", "extra", "pedantic")

add_rules("mode.debug", "mode.release")


set_configvar("SHADER_PATH", "$(projectdir)/Shader")

set_configdir("$(buildir)/Config")
add_configfiles("BEConfig.h.in")
add_includedirs("$(buildir)/Config")

add_includedirs("Include")
includes("Source")
