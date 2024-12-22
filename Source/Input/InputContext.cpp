/*
 * File: InputSystem.cpp
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#include "Input/InputSystem.h"
#include <glfw/glfw3.h>


namespace be {


bool InputSystem::Init(GLFWwindow* Window) noexcept {
    mWindow = Window;
    glfwSetKeyCallback(mWindow, []([[maybe_unused]] GLFWwindow* Window, int Key, [[maybe_unused]] int Scancode, int Action, [[maybe_unused]] int Mods) {
        InputSystem::Get().mInputEvents[Action][Key].Invoke();
    });

    return true;
}


void InputSystem::RegisterCallback(int Code, int Action, InputCallback const& Callback) noexcept {
    mInputEvents[Action][Code].RegisterCallback(Callback);
}


void InputSystem::UnregisterCallback(int Code, int Action, InputCallback const& Callback) noexcept {
    mInputEvents[Action][Code].UnregisterCallback(Callback);
}


void InputSystem::Process() noexcept {
    glfwPollEvents();
}


} // namespace be
