/*
 * File: GraphicsContext.cpp
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */


#include "spdlog/spdlog.h"
// #include "bgfx/bgfx.h"
// #include "bgfx/platform.h"
#include "SDL3/SDL.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_main.h"
#include "imgui.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include "Input/InputSystem.h"

#include "Graphics/GraphicsContext.h"
#include "Graphics/Texture.h"


namespace be {


GraphicsContext::GraphicsContext(int Width, int Height, const std::string& Title)
        : mTitle(Title)
        , mWindow(nullptr)
        , mWidth(Width)
        , mHeight(Height)
{ 
}


GraphicsContext::~GraphicsContext() {
    // ImGuiTerminate();
    SDLTerm();
}


bool GraphicsContext::Init() noexcept {
    if (!SDLInit()) return false;
    // if (!ImGuiInit()) return false;

    return true;
}

static bool quit = false;
Texture gHello;

void load(SDL_Renderer* renderer) {
    std::string path{"/home/kisuhorikka/Source/BlockEngine/Image/hello.png"};
    if (gHello.Load(renderer, path.c_str()); !gHello) {
        spdlog::error("Failed to open");
        return;
    }
}

void GraphicsContext::Step(double) noexcept {
    if (InputSystem::Get().Updated()) {
        if (InputSystem::Get().Is(SDL_EVENT_QUIT)) {
            spdlog::info("quit event");
            quit = true;
            return;
        }
        if (InputSystem::Get().Press(SDLK_ESCAPE)) {
            spdlog::info("Press escape");
            quit = true;
            return;
        }
    }

    // SDL_LockTexture(mTexture, nullptr, (void**)&pix, &pitch);
    // SDL_FillSurfaceRect(mSurface, nullptr, SDL_MapSurfaceRGB(mSurface, 0xFF, 0XFF, 0xFF));
    // SDL_BlitSurface(gHello, nullptr, mSurface, nullptr);
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderClear(mRenderer);
    // SDL_UpdateWindowSurface(mWindow);
    gHello.Render(mRenderer, nullptr, mWidth / 2, mHeight / 2);
    SDL_RenderPresent(mRenderer);

    // SDL_UnlockTexture(mTexture);
    // SDL_RenderTexture(mRenderer, mTexture, nullptr, nullptr);
    // SDL_RenderPresent(mRenderer);
    SDL_Delay(10);



    // ImGuiStepPrev();
    // ImGuiStep(DeltaTime);
    // ImGuiStepPost();
}


bool GraphicsContext::ShouldExit() noexcept {
    return quit;

}

bool GraphicsContext::SDLInit() noexcept {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        spdlog::error("Failed to initialize SDL, error: {}", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(mTitle.c_str(), mWidth, mHeight, 0);
    if (!mWindow) {
        spdlog::error("Failed to create SDL window, error: {}", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, nullptr);
    if (!mRenderer) {
        spdlog::error("Failed to create SDL renderer, error: {}", SDL_GetError());
        return false;
    }

    mSurface = SDL_GetWindowSurface(mWindow);

    // mTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, mWidth, mHeight);
    // if (!mTexture) {
    //     spdlog::error("Failed to create SDL texture, error: {}", SDL_GetError());
    //     return false;
    // }

    load(mRenderer);

    return true;
}


void GraphicsContext::SDLTerm() noexcept {
    // SDL_DestroyTexture(mTexture);
    // SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

bool GraphicsContext::ImGuiInit() noexcept {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

	return true;
}


void GraphicsContext::ImGuiTerminate() noexcept {
	ImGui::DestroyContext();
}


void GraphicsContext::ImGuiStepPrev() noexcept {
	ImGui::NewFrame();
}


void GraphicsContext::ImGuiStep(double) noexcept {
	ImGui::Begin("Config Menu");

    ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
    static float f;
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::Spacing();

    ImGui::End();
}


void GraphicsContext::ImGuiStepPost() noexcept {
	ImGui::Render();
	// ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


} // namespace be
