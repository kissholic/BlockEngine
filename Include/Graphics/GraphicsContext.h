/*
 * File: GraphicsContext.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once


#include <string>

namespace be {


class GraphicsContext {
public:
    GraphicsContext(int Width, int Height, const std::string& Title);
    ~GraphicsContext();

    bool Init() noexcept;
    void Step(double DeltaTime) noexcept;
    bool ShouldExit() noexcept;
    void HandleResizeWindow() noexcept;

private:
    bool GLFWInit() noexcept;
    void GLFWTerminate() noexcept;

    bool BGFXInit() noexcept;
    void BGFXTerminate() noexcept;

private:
    std::string mTitle;
    class GLFWwindow* mWindow;
    int mWidth;
    int mHeight;
};


} // namespace be