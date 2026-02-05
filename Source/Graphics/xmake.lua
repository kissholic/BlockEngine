

target("Graphics")
    set_kind("static")
    add_files("GraphicsContext.cpp", "Texture.cpp")
    add_packages("spdlog", "imgui", "libsdl3", "libsdl3_image")
    
