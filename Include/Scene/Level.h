/*
 * File: Level.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "GameObject.h"

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
        std::ranges::remove(mGameObjects, Obj);
    }

private:
    std::string mName;
    std::vector<GameObjectRef> mGameObjects;
};

using LevelRef = ObjectRefT<Level>;

} // namespace be
