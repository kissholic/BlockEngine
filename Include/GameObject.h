/*
 * File: GameObject.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include "Object.h"

namespace be {

struct GameObjectPosition {
    float X;
    float Y;
    float Z;
};

struct GameObjectScale {
    float X;
    float Y;
};

class GameObject : public Object {
public:

    virtual void Step([[maybe_unused]] double DeltaTime) noexcept {}

    GameObjectPosition mPosition;
    GameObjectScale mScale;
    float mRotation;
};


template<typename T>
concept IsGameObject = std::is_base_of<GameObject, T>::value;


using GameObjectRef = ObjectRefT<GameObject>;



} // namespace be
