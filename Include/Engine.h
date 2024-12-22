/*
 * File: Engine.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <memory>
#include "Input/InputSystem.h"
#include "Graphics/GraphicsContext.h"

namespace be {


class BlockEngine final {
public:
    static std::unique_ptr<BlockEngine> GEngine;

    BlockEngine() = default;
    ~BlockEngine() = default;

    void Run() noexcept;

    bool Init() noexcept;

    void Step(float DeltaTime) noexcept;

    bool ShouldExit() const noexcept;

private:
    // Initialize underlying systems
    bool PreInit() noexcept;
    // Initialize game systems
    bool PostInit() noexcept;

private:
    std::unique_ptr<GraphicsContext> mGraphicsContext;
};


} // namespace be
