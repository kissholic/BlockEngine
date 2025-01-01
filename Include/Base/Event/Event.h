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


template<typename ObjType, typename ObjType::FuncType>
class ObjectEvent {
public:
    void RegisterCallback(ObjType* Obj, ObjType::FuncType Func) noexcept {
        auto node = std::make_unique<EventNode>(Obj, Func);
        mCallbacks.push_back(std::move(node));
    }

    void UnregisterCallback(ObjType* Obj, ObjType::FuncType Func) noexcept {
        for (auto& Callback : mCallbacks) {
            if (Callback->mObj == Obj && Callback->mFunc == Func) {
                mCallbacks.erase(Callback);
                break;
            }
        }
    }

    void Invoke(auto&&... args) noexcept {
        for (auto& Callback : mCallbacks) {
            (Callback->mObj->*Callback->mFunc)(std::forward<decltype(args)>(args)...);
        }
    }


private:
    struct EventNode {
        ObjType* mObj;
        ObjType::FuncType mFunc;
    };

    std::vector<std::unique_ptr<EventNode>> mCallbacks;
};


} // namespace be
