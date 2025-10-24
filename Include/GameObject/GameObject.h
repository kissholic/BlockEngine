/*
 * File: GameObject.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include "Object/Object.h"
#include "Component/Component.h"

namespace be {

class Camera;
class Component;

class GameObject : public Object {
public:

    virtual void Step([[maybe_unused]] double DeltaTime) noexcept {}

private:
    ComponentRef mRoot;
};


template<typename T>
concept IsGameObject = std::is_base_of_v<GameObject, T>;


using GameObjectRef = ObjectRefT<GameObject>;



} // namespace be
