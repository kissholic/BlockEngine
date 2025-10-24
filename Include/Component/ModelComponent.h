/*
 * File: ModelComponent.h
 * Author: kissholic
 * Copyright (c) 2025 kissholic. All wrongs reserved.
 */

#pragma once

#include <vector>
#include "Camera/Camera.h"
#include "Component/Component.h"

namespace be {


class ModelComponent : public Component {
public:
	ModelComponent(std::vector<char>&& data, std::vector<char>)
		: mData(std::move(data))
	{}

	void InitGL() noexcept;

	void Draw(Camera* camera) noexcept;

private:
	std::vector<char> mData;
	unsigned int mVAO;
	unsigned int mVBO;
};


} // namespace be
