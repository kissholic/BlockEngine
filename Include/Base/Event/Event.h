/*
 * File: Event.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <functional>
#include <vector>

namespace be {


template<typename... Args>
using EventCallback = std::function<void(Args&&...)>;

template<typename... Args>
class Event {
public:
    using Callback = EventCallback<Args&&...>;
    void RegisterCallback(Callback const& Callback) noexcept {
        mCallbacks.push_back(Callback);
    }

    void UnregisterCallback(Callback const& Callback) noexcept {
        //mCallbacks.erase(Callback);
    }
    
    void Invoke(auto&&... args) noexcept {
        for (auto& Callback : mCallbacks) {
            Callback(std::forward<decltype(args)>(args)...);
        }
    }

private:
    std::vector<Callback> mCallbacks;
};


} // namespace be
