/*
 * File: Camera.cpp
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#include "Camera/Camera.h"
#include "Component/TransformComponent.h"
#include "Input/InputSystem.h"
#include <glm/gtc/matrix_transform.hpp>

namespace be {


Camera::Camera(glm::vec3 const& position, glm::vec3 const& face, glm::vec3 up)
{
	ComponentRef transform = MakeObject<TransformComponent>();
	
	transform->SetRoot(this);
}


Camera::~Camera() {}


void Camera::UpdateCamera() noexcept {
	mView = glm::lookAt(mPosition, mFace, mUp);
	mProjection = glm::perspective(glm::radians(60.f), mWidth / mHeight, mNear, mFar);

	mVP = mProjection * mView;
}

} // namespace be
