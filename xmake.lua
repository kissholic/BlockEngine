set_project("BlockEngine")


set_languages("c++20")
set_warnings("all", "extra", "pedantic")

add_rules("mode.debug", "mode.release")


add_includedirs("Include")
includes("Source")
