/*
 * File: Camera.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once


#include "GameObject/GameObject.h"


namespace be {

class Camera : public GameObject {
public:
    Camera(glm::vec3 const& position, glm::vec3 const& face, glm::vec3 up);
    ~Camera();

    void UpdateCamera() noexcept;

private:
    glm::vec3 mPosition;
    glm::vec3 mFace;
    glm::vec3 mUp;

    glm::mat4 mView;

    float mFov;
    float mWidth;
    float mHeight;

    float mNear;
    float mFar;

    glm::mat4 mProjection;

    glm::mat4 mVP; // not MVP
};


} // namespace be
