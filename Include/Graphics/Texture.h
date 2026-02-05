/*
 * File: Texture.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <string>


namespace be {


class Texture {
public:
    Texture();
    ~Texture();

    operator bool() const noexcept { return !!mTexture; }

    bool Load(SDL_Renderer* renderer, std::string const& path) noexcept;

    void Render(SDL_Renderer* renderer, SDL_FRect* rect, float x, float y) const noexcept;

    int GetWidth() const noexcept { return mWidth; }
    int GetHeight() const noexcept { return mHeight; }

private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};


} // namespace be
