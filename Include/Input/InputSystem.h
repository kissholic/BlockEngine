/*
 * File: InputSystem.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <SDL3/SDL_keycode.h>
#include <array>
// #include "Base/Event/Event.h"

#include "SDL3/SDL_events.h"

namespace be {


class InputSystem {
public:
    // using InputEvent = Event<>;
    // using InputCallback = EventCallback<>;

    static InputSystem& Get() noexcept {
        static InputSystem Instance;
        return Instance;
    }

    InputSystem(InputSystem const&) = delete;
    InputSystem& operator=(InputSystem const&) = delete;


    // void RegisterCallback(int Code, int Action, InputCallback const& Callback) noexcept;
    // void UnregisterCallback(int Code, int Action, InputCallback const& Callback) noexcept;

    void Process() noexcept {
        mUpdated = SDL_PollEvent(&mEvent);
    }

    bool Updated() const noexcept {
        return mUpdated;
    }

    bool Is(SDL_EventType type) const noexcept {
        return type == mEvent.type;
    }

    bool Press(SDL_Keycode code) const noexcept {
        return  code == mEvent.key.key;
    }

    bool Up(SDL_Keycode code) const noexcept {
        return code == mEvent.key.key;
    }

private:
    InputSystem() = default;

private:
    SDL_Event mEvent;
    bool mUpdated;
};

} // namespace be
