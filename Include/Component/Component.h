/*
 * File: Component.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <vector>

#include "Object/Object.h"


namespace be {

class Component : public Object {
public:
    Component() = default;
    virtual ~Component() = default;

    void SetRoot(class GameObject* obj);

private:
    Object* mParent;
    std::vector<ObjectRef> mSubComponents;
};


using ComponentRef = ObjectRefT<Component>;

} // namespace be
