/*
 * File: Scene.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <memory>
#include <vector>

#include "Level.h"


namespace be {


class Scene : public GameObject {
public:

    virtual void Step(double DeltaTime) noexcept override {
        for (auto& Level : mLevels) {
            Level->Step(DeltaTime);
        }
    }

private:
    std::vector<LevelRef> mLevels;
};

using SceneRef = ObjectRefT<Scene>;


} // namespace be
