/*
 * File: Object.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <cstddef>
#include <type_traits>


namespace be {

class Object {
public:
    Object() {}
    virtual ~Object() {}

    virtual void Step([[maybe_unused]] double DeltaTime) noexcept {}

    uint32_t GetRefCount() const noexcept { return mRefCount; }

private:
    friend class ObjectRef;

    void IncRefCount() noexcept { ++mRefCount;}
    void DecRefCount() noexcept { --mRefCount; }

private:
    uint32_t mRefCount;
};


template<typename T>
concept IsObject = std::is_base_of<Object, T>::value;


class ObjectRef {
public:
    ObjectRef(std::nullptr_t) noexcept : mObj(nullptr) {}

    ObjectRef(Object* Obj) noexcept : mObj(Obj) {
        if (mObj) {
            mObj->IncRefCount();
        }
    }

    ObjectRef(const ObjectRef& Ref) noexcept : mObj(Ref.mObj) {
        if (mObj) {
            mObj->IncRefCount();
        }
    }

    ~ObjectRef() noexcept {
        if (mObj) {
            mObj->DecRefCount();
        }
    }

    ObjectRef& operator=(const ObjectRef& Ref) noexcept {
        if (this!= &Ref) {
            if (mObj) {
                mObj->DecRefCount();
            }
            mObj = Ref.mObj;
            if (mObj) {
                mObj->IncRefCount();
            }
        }
        return *this;
    }

    ObjectRef& opeartor(Object* Obj) noexcept {
        if (mObj) {
            mObj->DecRefCount();
        }
        mObj = Obj;
        if (mObj) {
            mObj->IncRefCount();
        }
        return *this;
    }

    ObjectRef& operator=(ObjectRef&& Ref) noexcept {
        if (this!= &Ref) {
            if (mObj) {
                mObj->DecRefCount();
            }
            mObj = Ref.mObj;
            Ref.mObj = nullptr;
        }
        return *this;
    }

    Object* Get() const noexcept { return mObj; }

    Object* operator->() const noexcept { return mObj; }
    Object* operator->() noexcept { return mObj; }

    Object& operator*() const noexcept { return *mObj; }
    Object& operator*() noexcept { return *mObj; }

private:
    Object* mObj;
};


template<IsObject T>
ObjectRef MakeObjectRef(auto&&... Args) noexcept {
    return ObjectRef(new T(std::forward<decltype(Args)>(Args)...));
}

} // namespace be

