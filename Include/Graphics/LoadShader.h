/*
 * File: LoadShader.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <string>
#include "bgfx/bgfx.h"


namespace be {


bgfx::ProgramHandle LoadShaderProgram(const std::string& VertexShader, const std::string& FragmentShader) noexcept;


} // namespace be