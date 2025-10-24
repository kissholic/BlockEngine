/*
 * File: InputSystem.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <array>
#include <glfw/glfw3.h>
#include "Base/Event/Event.h"

namespace be {


class InputSystem {
public:
    using InputEvent = Event<>;
    using InputCallback = EventCallback<>;

    static InputSystem& Get() noexcept {
        static InputSystem Instance;
        return Instance;
    }

    InputSystem(InputSystem const&) = delete;
    InputSystem& operator=(InputSystem const&) = delete;

    bool Init(GLFWwindow* Window) noexcept;

    void RegisterCallback(int Code, int Action, InputCallback const& Callback) noexcept;
    void UnregisterCallback(int Code, int Action, InputCallback const& Callback) noexcept;

    void Process() noexcept;

private:
    InputSystem() = default;

private:
    GLFWwindow* mWindow;
    std::array<InputEvent, GLFW_KEY_LAST> mInputEvents[2];
};

} // namespace be
