/*
 * File: Component.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include "Object.h"


namespace be {

class Component {
public:
    Component() = default;
    virtual ~Component() = default;

};


using ComponentRef = ObjectRefT<Component>;

} // namespace be
