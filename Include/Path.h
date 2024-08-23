/*
 * File: Path.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <filesystem>


namespace be {

class Path {
public:
    static std::filesystem::path ProjectPath() noexcept;
    static std::filesystem::path EnginePath() noexcept;

    static std::filesystem::path ShaderPath() noexcept;
};


} // namespace be

