/*
 * File: Level.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

#include "GameObject/GameObject.h"

namespace be {


class Level : public GameObject {
public:
    Level(const std::string& Name) : mName(Name) {}

    virtual void Step(double DeltaTime) noexcept override {
        for (auto& Obj : mGameObjects) {
            Obj->Step(DeltaTime);
        }
    }

    void AddGameObject(GameObjectRef Obj) noexcept {
        mGameObjects.push_back(Obj);
    }

    void RemoveGameObject(GameObjectRef Obj) noexcept {
        assert(0 && "Not implemented");
    }

private:
    std::string mName;
    std::vector<GameObjectRef> mGameObjects;
};

using LevelRef = ObjectRefT<Level>;

} // namespace be
