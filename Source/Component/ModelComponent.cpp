/*
 * File: ModelComponent.cpp
 * Author: kissholic
 * Copyright (c) 2025 kissholic. All wrongs reserved.
 */

#include "Component/ModelComponent.h"

#include "glad/glad.h"
#define GLFW_INCLUDE_OPENGL
#include "GLFW/glfw3.h"



namespace be {


void ModelComponent::InitGL() noexcept {
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mData.size(), mData.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}


void ModelComponent::Draw(Camera* camera) noexcept {

}


} // namespace be
