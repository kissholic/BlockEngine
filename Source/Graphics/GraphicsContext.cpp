/*
 * File: GraphicsContext.cpp
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */


#include "GLFW/glfw3.h"

#ifdef __APPLE__
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include "GLFW/glfw3native.h"

#include "bgfx/bgfx.h"
#include "bgfx/platform.h"
#include <spdlog/spdlog.h>

#include "Graphics/GraphicsContext.h"


namespace be {


GraphicsContext::GraphicsContext(int Width, int Height, const std::string& Title)
        : mTitle(Title)
        , mWindow(nullptr)
        , mWidth(Width)
        , mHeight(Height)
{ 
}


GraphicsContext::~GraphicsContext() {
    BGFXTerminate();
    GLFWTerminate();
}


bool GraphicsContext::Init() noexcept {
    if (!GLFWInit()) {
        return false;
    }

    if (!BGFXInit()) {
        return false;
    }

    return true;
}


void GraphicsContext::Step(double DeltaTime) noexcept {
    glfwPollEvents();
    HandleResizeWindow();
    bgfx::touch(0);
    bgfx::setViewRect(0, 0, 0, mWidth, mHeight);
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);

    // ImGuiStep(DeltaTime);
    bgfx::frame();
}


bool GraphicsContext::ShouldExit() noexcept {
    return glfwWindowShouldClose(mWindow);
}


void GraphicsContext::HandleResizeWindow() noexcept {
    int OldWidth = mWidth, OldHeight = mHeight;
    glfwGetWindowSize(mWindow, &mWidth, &mHeight);
    if (OldWidth!= mWidth || OldHeight!= mHeight) {
        bgfx::reset(mWidth, mHeight, BGFX_RESET_VSYNC);
        bgfx::setViewRect(0, 0, 0, mWidth, mHeight);
    }
}


bool GraphicsContext::GLFWInit() noexcept {
    if (!glfwInit()) {
        spdlog::error("Failed to initialize GLFW");
        return false;
    }

    // glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);
    if (!mWindow) {
        spdlog::error("Failed to create GLFW window");
        return false;
    }

    glfwMakeContextCurrent(mWindow);
    glfwSetWindowUserPointer(mWindow, this);

    // Set error callback
    glfwSetErrorCallback([](int Error, const char* Description) {
        spdlog::error("GLFW Error {}: {}", Error, Description);
    });

    // Set keyboard input callback
    glfwSetKeyCallback(mWindow, [](GLFWwindow* Window, int Key, [[maybe_unused]] int Scancode, int Action, [[maybe_unused]] int Mods) {
        if (Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS) {
            glfwSetWindowShouldClose(Window, GLFW_TRUE);
        }
    });

    glfwSetFramebufferSizeCallback(mWindow, [](GLFWwindow* Window, int Width, int Height) {
        auto* Context = reinterpret_cast<GraphicsContext*>(glfwGetWindowUserPointer(Window));
        Context->mWidth = Width;
        Context->mHeight = Height;
    });

    return true;
}


void GraphicsContext::GLFWTerminate() noexcept {
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}


bool GraphicsContext::BGFXInit() noexcept {
    bgfx::renderFrame();
    bgfx::Init BGFX_Init;
    BGFX_Init.type = bgfx::RendererType::OpenGL;
    BGFX_Init.resolution.width = mWidth;
    BGFX_Init.resolution.height = mHeight;
    BGFX_Init.resolution.reset = BGFX_RESET_VSYNC;

    bgfx::PlatformData pd;
    pd.backBuffer = nullptr;
    pd.context = nullptr;
    pd.ndt = nullptr;
    pd.nwh = glfwGetCocoaWindow(mWindow);
    pd.type = bgfx::NativeWindowHandleType::Count;
    BGFX_Init.platformData = pd;

    if (!bgfx::init(BGFX_Init)) {
        spdlog::error("Failed to initialize BGFX");
        return false;
    }

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, mWidth, mHeight);

    return true;
}


void GraphicsContext::BGFXTerminate() noexcept {
    bgfx::shutdown();
}




} // namespace be
