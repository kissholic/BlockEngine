/*
 * File: ShaderLoader.cpp
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#include <filesystem>
#include <fstream>

#include "Graphics/ShaderLoader.h"
#include "spdlog/spdlog.h"


namespace be {


ShaderWrapper::ShaderWrapper(unsigned int ShaderHandle)
        : mShaderHandle(ShaderHandle)
{}


ShaderWrapper::~ShaderWrapper() {
    glDeleteShader(mShaderHandle);
}


ShaderWrapper ShaderLoader::LoadCompiledShader(std::filesystem::path ShaderPath, GLenum ShaderType) {
    return {0};
}


ShaderWrapper ShaderLoader::LoadRawShader(std::filesystem::path ShaderPath, GLenum ShaderType) {
    // Check if the file exists
    if (!std::filesystem::exists(ShaderPath)) {
        spdlog::error("Shader file not found: {}", ShaderPath.string());
        return {0};
    }

    // Read the shader file
    std::ifstream file(ShaderPath);
    std::string shaderSource((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    ShaderWrapper shader = CompileShader(shaderSource.c_str(), ShaderType);
    if (!shader.IsValid()) {
        spdlog::error("Failed to compile shader: {}", ShaderPath.string());
    }

    return shader;
}


ShaderWrapper ShaderLoader::CompileShader(const char* ShaderSource, GLenum ShaderType) {
    assert(ShaderSource != nullptr);

    unsigned int shader = glCreateShader(ShaderType);
    glShaderSource(shader, 1, &ShaderSource, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        // TODO: infoLog may be too big to fit in stack.
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        spdlog::error("Shader compilation failed: {}", infoLog);
        glDeleteShader(shader);
        return {0};
    }

    return {shader};
}


ShaderProgramWrapper::ShaderProgramWrapper(unsigned int ShaderProgramHandle)
    : mShaderProgramHandle(ShaderProgramHandle)
{}


ShaderProgramWrapper::~ShaderProgramWrapper() {
    glDeleteProgram(mShaderProgramHandle);
}


void ShaderProgramWrapper::Use() const noexcept{
    glUseProgram(mShaderProgramHandle);
}


ShaderProgramWrapper CreateShaderProgram(const std::filesystem::path& VertexShaderPath, const std::filesystem::path& FragShaderPath) {
    ShaderWrapper VertexShader = ShaderLoader::LoadRawShader(VertexShaderPath, GL_VERTEX_SHADER);
    ShaderWrapper FragShader = ShaderLoader::LoadRawShader(FragShaderPath, GL_FRAGMENT_SHADER);

    return CreateShaderProgram(VertexShader, FragShader);
}


ShaderProgramWrapper CreateShaderProgram(const ShaderWrapper& VertexShader, const ShaderWrapper& FragShader) {
    unsigned int shaderProgram = glCreateProgram();
    
    // TODO: Support more shader types.
    glAttachShader(shaderProgram, VertexShader.GetShaderHandle());
    glAttachShader(shaderProgram, FragShader.GetShaderHandle());

    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        // TODO: infoLog may be too big to fit in stack.
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    }

    return {shaderProgram};
}



} // namespace be
