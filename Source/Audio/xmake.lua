target("Audio")
    set_kind("static")
    add_deps("Core")
    add_packages("spdlog")
    add_files("Audio.mpp", {public = true})
    add_files("$(projectdir)/external/soloud/src/core/*.cpp")
    add_files("$(projectdir)/external/soloud/src/audiosource/wav/*.cpp")
    add_files("$(projectdir)/external/soloud/src/audiosource/wav/*.c")
    if is_plat("macosx") then
        add_frameworks("AudioToolbox", "CoreAudio", "CoreFoundation")
        add_defines("WITH_COREAUDIO")
        add_files("$(projectdir)/external/soloud/src/backend/coreaudio/*.cpp")
    elseif is_plat("windows") then
        add_defines("WITH_WASAPI")
    elseif is_plat("linux") then
        add_defines("WITH_MINIAUDIO")
    end
