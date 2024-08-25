/*
 * File: ImageLoader.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <filesystem>

namespace be {


struct ImageWrapper {
    ImageWrapper() = default;
    ImageWrapper(unsigned char* Data, int Width, int Height, int Channels)
        : Data(Data), Width(Width), Height(Height), Channels(Channels)
    {}

    ~ImageWrapper();
    
    unsigned char* Data;
    int Width;
    int Height;
    int Channels;
};


ImageWrapper LoadImage(std::filesystem::path const& ImagePath);


} // namespace be
