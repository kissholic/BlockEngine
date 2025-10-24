/*
 * File: TransformComponent.cpp
 * Author: kissholic
 * Copyright (c) 2025 kissholic. All wrongs reserved.
 */

#include "Component/TransformComponent.h"


namespace be {


TransformComponent::TransformComponent()
	: mPosition(.0f, .0f, 0.f)
	, mRotate(.0f, .0f, .0f)
	, mScale(1.f, 1.f, 1.f)
{
}


TransformComponent::TransformComponent(glm::vec3 pos, glm::vec3 rotate, glm::vec3 scale)
	: mPosition(pos)
	, mRotate(rotate)
	, mScale(scale)
{
}


void TransformComponent::Update() noexcept {
	for (auto* sub : mSubTransforms) {
		sub->AddPosition(mPosition);
		sub->AddRotate(mRotate);
	}
}


void TransformComponent::SetPosition(glm::vec3 pos) noexcept {
	mPosition = pos;
}


void TransformComponent::SetPositionX(float x) noexcept {
	mPosition.x = x;
}


void TransformComponent::SetPositionY(float y) noexcept {
	mPosition.y = y;
}


void TransformComponent::SetPositionZ(float z) noexcept {
	mPosition.z = z;
}


void TransformComponent::AddPosition(glm::vec3 delta) noexcept {
	mPosition += delta;
}


void TransformComponent::AddPositionX(float x) noexcept {
	mPosition.x += x;
}


void TransformComponent::AddPositionY(float y) noexcept {
	mPosition.y += y;
}


void TransformComponent::AddPositionZ(float z) noexcept {
	mPosition.z += z;
}


glm::vec3& TransformComponent::Position() noexcept {
	return mPosition;
}


glm::vec3 const& TransformComponent::Position() const noexcept {
	return mPosition;
}


void TransformComponent::SetRotate(glm::vec3 rotate) noexcept {
	mRotate = rotate;
}


void TransformComponent::SetRotateX(float x) noexcept {
	mRotate.x = x;
}


void TransformComponent::SetRotateY(float y) noexcept {
	mRotate.y = y;
}


void TransformComponent::SetRotateZ(float z) noexcept {
	mRotate.z = z;
}


void TransformComponent::AddRotate(glm::vec3 rotate) noexcept {
	mRotate += rotate;
}


void TransformComponent::AddRotateX(float x) noexcept {
	mRotate.x += x;
}


void TransformComponent::AddRotateY(float y) noexcept {
	mRotate.y += y;
}


void TransformComponent::AddRotateZ(float z) noexcept {
	mRotate.z += z;
}


glm::vec3& TransformComponent::Rotate() noexcept {
	return mRotate;
}


glm::vec3 const& TransformComponent::Rotate() const noexcept {
	return mRotate;
}


void TransformComponent::SetScale(glm::vec3 scale) noexcept {
	mScale = scale;
}


void TransformComponent::SetScaleX(float x) noexcept {
	mScale.x = x;
}


void TransformComponent::SetScaleY(float y) noexcept {
	mScale.y = y;
}


void TransformComponent::SetScaleZ(float z) noexcept {
	mScale.z = z;
}


glm::vec3& TransformComponent::Scale() noexcept {
	return mScale;
}


glm::vec3 const& TransformComponent::Scale() const noexcept {
	return mScale;
}


} // namespace be
