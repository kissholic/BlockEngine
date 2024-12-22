/*
 * File: Camera.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <glm/glm.hpp>


namespace be {

class Camera {

public:
    glm::vec3 mPosition;
    glm::vec3 mUp;
    glm::vec3 mRight;
};


} // namespace be
