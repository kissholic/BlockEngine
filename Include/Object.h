/*
 * File: Object.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <cstddef>
#include <type_traits>


namespace be {


class Object;

template<typename T>
concept IsObject = std::is_base_of<Object, T>::value;

class Object {
    template<IsObject T>
    friend class ObjectRefT;

public:
    Object() {}
    virtual ~Object() {}

    uint32_t GetRefCount() const noexcept { return mRefCount; }

private:
    friend class ObjectRef;

    void IncRefCount() noexcept { ++mRefCount;}
    void DecRefCount() noexcept { --mRefCount; }

private:
    uint32_t mRefCount;
};


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


template <IsObject T>
class ObjectRefT {
public:
    ObjectRefT() noexcept : mObj(nullptr) {}
    ObjectRefT(std::nullptr_t) noexcept : mObj(nullptr) {}

    ObjectRefT(T* Obj) noexcept : mObj(Obj) {
        if (mObj) {
            mObj->IncRefCount();
        }
    }

    ObjectRefT(const ObjectRefT& Ref) noexcept : mObj(Ref.mObj) {
        if (mObj) {
            mObj->IncRefCount();
        }
    }

    ~ObjectRefT() noexcept {
        if (mObj) {
            mObj->DecRefCount();
        }
    }

    ObjectRefT& operator=(const ObjectRefT& Ref) noexcept {
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

    ObjectRefT& operator=(T* Obj) noexcept {
        if (mObj) {
            mObj->DecRefCount();
        }
        mObj = Obj;
        if (mObj) {
            mObj->IncRefCount();
        }
        return *this;
    }

    ObjectRefT& operator=(ObjectRefT&& Ref) noexcept {
        if (this!= &Ref) {
            if (mObj) {
                mObj->DecRefCount();
            }
            mObj = Ref.mObj;
            Ref.mObj = nullptr;
        }
        return *this;
    }

    bool operator==(const ObjectRefT& Ref) const noexcept { return mObj == Ref.mObj; }
    bool operator!=(const ObjectRefT& Ref) const noexcept { return mObj != Ref.mObj; }

    T* Get() const noexcept { return mObj; }

    T* operator->() const noexcept { return mObj; }
    T* operator->() noexcept { return mObj; }

    T& operator*() const noexcept { return *mObj; }
    T& operator*() noexcept { return *mObj; }

private:
    T* mObj;
};


template<IsObject T>
ObjectRef MakeObject(auto&&... Args) noexcept {
    return ObjectRef(new T(std::forward<decltype(Args)>(Args)...));
}

} // namespace be

