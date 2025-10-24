/*
 * File: ShaderLoader.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <glad/glad.h>
#include "spdlog/spdlog.h"
#include <filesystem>
#include <string>


namespace be {


class ShaderWrapper {
public:
    ShaderWrapper(unsigned int ShaderHandle);
    ~ShaderWrapper();

    unsigned int GetShaderHandle() const noexcept { return mShaderHandle; }

    bool IsValid() const noexcept { return mShaderHandle!= 0; }

private:
    unsigned int mShaderHandle;
};


class ShaderLoader {
public:
    static ShaderWrapper LoadCompiledShader(std::filesystem::path ShaderPath, GLenum ShaderType);
    static ShaderWrapper LoadRawShader(std::filesystem::path ShaderPath, GLenum ShaderType);

    static ShaderWrapper CompileShader(const char* ShaderSource, GLenum ShaderType);
};


class ShaderProgramWrapper {
public:
    ShaderProgramWrapper(unsigned int ShaderProgramHandle);
    ~ShaderProgramWrapper();

    unsigned int GetShaderProgramHandle() const noexcept { return mShaderProgramHandle; }

    bool IsValid() const noexcept { return mShaderProgramHandle!= 0; }

    void Use() const noexcept;

    void SetUniform1(const std::string& Name, bool Value) const noexcept;
    void SetUniform1(const std::string& Name, int Value) const noexcept;
    void SetUniform1(const std::string& Name, float Value) const noexcept;
    void SetUniformM2(const std::string& Name, bool Transpose, GLfloat* Data);
    void SetUniformM3(const std::string& Name, bool Transpose, GLfloat* Data);
    void SetUniformM4(const std::string& Name, bool Transpose, GLfloat* Data);

private:
    unsigned int mShaderProgramHandle;
};

ShaderProgramWrapper CreateShaderProgram(const std::filesystem::path& VertexShaderPath, const std::filesystem::path& FragShaderPath);
ShaderProgramWrapper CreateShaderProgram(const ShaderWrapper& VertexShader, const ShaderWrapper& FragShader);


} // namespace be