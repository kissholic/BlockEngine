/*
 * File: Texture.cpp
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#include "Graphics/Texture.h"
#include "Graphics/ImageLoader.h"
#include "glad/glad.h"



namespace be {


Texture::Texture(ImageWrapper& Source)
        : mTextureHandle(0), mWidth(Source.Width), mHeight(Source.Height), mChannels(Source.Channels) {
    glGenTextures(1, &mTextureHandle);
    glBindTexture(GL_TEXTURE_2D, mTextureHandle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, Source.Data);
    glGenerateMipmap(GL_TEXTURE_2D);
}


Texture::~Texture() {
    glDeleteTextures(1, &mTextureHandle);
}


} // namespace be
