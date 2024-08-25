/*
 * File: Texture.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <string>
#include "ImageLoader.h"

namespace be {


class Texture {
public:
    Texture(ImageWrapper& Source);
    ~Texture();

    unsigned int GetTextureHandle() const noexcept { return mTextureHandle; }
    int GetWidth() const noexcept { return mWidth; }
    int GetHeight() const noexcept { return mHeight; }
    int GetChannels() const noexcept { return mChannels; }

private:
    unsigned int mTextureHandle;
    int mWidth;
    int mHeight;
    int mChannels;
};


} // namespace be
