/*
 * File: ImageLoader.cpp
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#include "Graphics/ImageLoader.h"
#include "spdlog/spdlog.h"

// #include "stb_image.h"

namespace be {


ImageWrapper::~ImageWrapper()
{
    stbi_image_free(Data);
}

ImageWrapper LoadImage(std::filesystem::path const& ImagePath) {
    ImageWrapper image;

    image.Data = stbi_load(ImagePath.c_str(), &image.Width, &image.Height, &image.Channels, 0);
    if (image.Data == nullptr) {
        spdlog::error("Failed to load image: {}", ImagePath.c_str());
    }

    return image;
}


} // namespace be
