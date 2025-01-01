/*
 * File: GraphicsContext.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <string>

struct GLFWwindow;

namespace be {


class GraphicsContext {
public:
    GraphicsContext(int Width, int Height, const std::string& Title);
    ~GraphicsContext();

    bool Init() noexcept;
    void Step(double DeltaTime) noexcept;
    bool ShouldExit() noexcept;

    operator GLFWwindow*() const noexcept {
        return mWindow;
    }

private:
    bool GLFWInit() noexcept;
    void GLFWTerminate() noexcept;

    bool GLInit() noexcept;
    void GLTerminate() noexcept;

    bool ImGuiInit() noexcept;
    void ImGuiTerminate() noexcept;
    void ImGuiStepPrev() noexcept;
    void ImGuiStep(double DeltaTime) noexcept;
    void ImGuiStepPost() noexcept;

private:
    std::string mTitle;
    GLFWwindow* mWindow;
    int mWidth;
    int mHeight;

};


} // namespace be