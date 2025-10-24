/*
 * File: TransformComponent.h
 * Author: kissholic
 * Copyright (c) 2025 kissholic. All wrongs reserved.
 */

#pragma once

#include <vector>
#include "Component.h"
#include <glm/glm.hpp>


namespace be {


class TransformComponent : public Component {
public:
	TransformComponent();
	TransformComponent(glm::vec3 pos, glm::vec3 rotate = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1,1,1));

	void Update() noexcept;

	// Position
	void SetPosition(glm::vec3 pos) noexcept;
	void SetPositionX(float x) noexcept;
	void SetPositionY(float y) noexcept;
	void SetPositionZ(float z) noexcept;
	void AddPosition(glm::vec3 delta) noexcept;
	void AddPositionX(float x) noexcept;
	void AddPositionY(float y) noexcept;
	void AddPositionZ(float z) noexcept;
	glm::vec3& Position() noexcept;
	glm::vec3 const& Position() const noexcept;

	// Rotate
	void SetRotate(glm::vec3 rotate) noexcept;
	void SetRotateX(float x) noexcept;
	void SetRotateY(float y) noexcept;
	void SetRotateZ(float z) noexcept;
	void AddRotate(glm::vec3 rotate) noexcept;
	void AddRotateX(float x) noexcept;
	void AddRotateY(float y) noexcept;
	void AddRotateZ(float z) noexcept;
	glm::vec3& Rotate() noexcept;
	glm::vec3 const& Rotate() const noexcept;

	// Scale
	void SetScale(glm::vec3 scale) noexcept;
	void SetScaleX(float x) noexcept;
	void SetScaleY(float y) noexcept;
	void SetScaleZ(float z) noexcept;
	glm::vec3& Scale() noexcept;
	glm::vec3 const& Scale() const noexcept;

	void AttachTo(class TransformComponent*);

private:
	std::vector<TransformComponent*> mSubTransforms;

	glm::vec3 mPosition;
	glm::vec3 mRotate;
	glm::vec3 mScale;
};


} // namespace be
