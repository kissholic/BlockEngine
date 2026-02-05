/*
 * File: Texture.cpp
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#include "Graphics/Texture.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include "spdlog/spdlog.h"



namespace be {


Texture::Texture()
    : mTexture(nullptr)
    , mWidth(0)
    , mHeight(0)
{}


Texture::~Texture() {
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
}

bool Texture::Load(SDL_Renderer* renderer, std::string const& path) noexcept {
    if (mTexture) {
        spdlog::error("Texture has been loaded, path: {}", path);
        return false;
    }

    if (SDL_Surface* surface = IMG_Load(path.c_str()); !surface)
        spdlog::error("Failed to open texture {}, error: {}", path, SDL_GetError());
    else {
        if (mTexture = SDL_CreateTextureFromSurface(renderer, surface); !mTexture)
            spdlog::error("Failed to create texture from surface: {}", SDL_GetError());
        else {
            mWidth = surface->w;
            mHeight = surface->h;
        }

        SDL_DestroySurface(surface);
    }

    return !!mTexture;
}

void Texture::Render(SDL_Renderer* renderer, SDL_FRect* rect, float x, float y) const noexcept {
    SDL_FRect dst{x, y, static_cast<float>(mWidth), static_cast<float>(mHeight)};

    if (!!rect) {
        dst.w = rect->w;
        dst.h = rect->h;
    }

    SDL_RenderTexture(renderer, mTexture, rect, &dst);
}


} // namespace be
