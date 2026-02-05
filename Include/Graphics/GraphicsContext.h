/*
 * File: GraphicsContext.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <memory>
#include <string>

struct SDL_Window;

namespace be {


class GraphicsContext {
public:
    GraphicsContext(int Width, int Height, const std::string& Title);
    ~GraphicsContext();

    bool Init() noexcept;
    void Step(double DeltaTime) noexcept;
    bool ShouldExit() noexcept;

private:
    bool SDLInit() noexcept;
    void SDLTerm() noexcept;

    bool ImGuiInit() noexcept;
    void ImGuiTerminate() noexcept;
    void ImGuiStepPrev() noexcept;
    void ImGuiStep(double DeltaTime) noexcept;
    void ImGuiStepPost() noexcept;

private:
    std::string mTitle;
    struct SDL_Window* mWindow;
    int mWidth;
    int mHeight;

    struct SDL_Renderer* mRenderer;
    struct SDL_Surface* mSurface;
    struct SDL_Texture* mTexture;
};


} // namespace be