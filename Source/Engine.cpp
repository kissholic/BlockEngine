/*
 * File: Engine.cpp
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#include "Engine.h"
#include "Input/InputSystem.h"
#include "spdlog/spdlog.h"


namespace be {

std::unique_ptr<BlockEngine> BlockEngine::GEngine = nullptr;


bool BlockEngine::Init() noexcept {
    if (!PreInit()) {
        return false;
    }

    // Initialize engine systems
    {
        // Initialize graphics context
        mGraphicsContext = std::make_unique<GraphicsContext>(800, 600, "Block Engine");
        if (!mGraphicsContext || !mGraphicsContext->Init()) {
            return false;
        }
    }

    {
        // Initialize input context
        // if (!InputSystem::Get().Init(*mGraphicsContext)) {
        //     return false;
        // }
    }

    if (!PostInit()) {
        return false;
    }

    return true;
}

bool BlockEngine::PreInit() noexcept {
    return true;
}

bool BlockEngine::PostInit() noexcept {
    if (!InitInput())
        return false;

    return true;
}

bool BlockEngine::InitInput() noexcept {
    // auto& inputSystem = InputSystem::Get();
    // inputSystem.Init((GLFWwindow*)*mGraphicsContext.get());

    return true;
}


void BlockEngine::Step(float DeltaTime) noexcept {
    InputSystem::Get().Process();
    
    mGraphicsContext->Step(DeltaTime);
}

bool BlockEngine::ShouldExit() const noexcept {
    return mGraphicsContext->ShouldExit();
}

} // namespace be
