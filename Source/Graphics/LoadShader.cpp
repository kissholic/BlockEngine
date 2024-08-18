/*
 * File: LoadShader.cpp
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#include <filesystem>
#include <fstream>

#include "Graphics/LoadShader.h"
#include "spdlog/spdlog.h"


namespace be {

namespace detail {

[[nodiscard]] static bgfx::ShaderHandle LoadShaderFromFile(const std::string& Path) noexcept {
    std::ifstream File(Path, std::ios::ate | std::ios::binary);
    if (!File.is_open()) {
        spdlog::error("Failed to open file: {}", Path);
        return {};
    }

    size_t FileSize = static_cast<size_t>(File.tellg());

    bgfx::Memory const* ShaderMemory = bgfx::alloc(FileSize + 1);
    if (!ShaderMemory) {
        spdlog::error("Failed to allocate memory for shader: {}", Path);
        return {};
    }

    File.seekg(0);
    File.read(reinterpret_cast<char*>(ShaderMemory->data), FileSize);
    File.close();
    ShaderMemory->data[FileSize] = '\0';

    return bgfx::createShader(ShaderMemory);
}


} // namespace detail

bgfx::ProgramHandle LoadShaderProgram(const std::string& VertexShader, const std::string& FragmentShader) noexcept {
    std::filesystem::path ShaderPath = "shaders/glsl/";
    std::filesystem::path VertexShaderPath = ShaderPath / VertexShader;
    std::filesystem::path FragmentShaderPath = ShaderPath / FragmentShader;

    bgfx::ShaderHandle VertexShaderHandle = detail::LoadShaderFromFile(VertexShaderPath.string());
    if (!isValid(VertexShaderHandle)) {
        return {};
    }

    bgfx::ShaderHandle FragmentShaderHandle = detail::LoadShaderFromFile(FragmentShaderPath.string());
    if (!isValid(FragmentShaderHandle)) {
        return {};
    }

    return bgfx::createProgram(VertexShaderHandle, FragmentShaderHandle, true);
}


} // namespace be
