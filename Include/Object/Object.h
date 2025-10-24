/*
 * File: Object.h
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */

#pragma once

#include <cstddef>
#include <type_traits>
#include <utility>


namespace be {


class Object;

template<typename T>
concept IsObject = std::is_base_of_v<Object, T>;

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

    ObjectRef(ObjectRef&& Ref) noexcept : mObj(Ref.mObj) {
        Ref.mObj = nullptr;
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
class ObjectRefT : public ObjectRef {
public:
    ObjectRefT() noexcept : ObjectRef(nullptr) {}
    ObjectRefT(std::nullptr_t) noexcept : ObjectRef(nullptr) {}

    ObjectRefT(T* Obj) noexcept : ObjectRef(Obj) {
    }

    ObjectRefT(const ObjectRefT& Ref) noexcept : ObjectRef(Ref) {}

    template<typename U>
    ObjectRefT(const ObjectRefT<U>& Ref) noexcept : ObjectRef(Ref) {
    }

    template<typename U>
    ObjectRefT(ObjectRefT<U>&& Ref) noexcept : ObjectRef(std::move(Ref)) {
    }

    ~ObjectRefT() noexcept = default;

    ObjectRefT& operator=(const ObjectRefT& Ref) noexcept {
        ObjectRef::operator=(Ref);
        return *this;
    }

    ObjectRefT& operator=(T* Obj) noexcept {
        ObjectRef::operator=(Obj);
        return *this;
    }

    ObjectRefT& operator=(ObjectRefT&& Ref) noexcept {
        ObjectRef::operator=(std::move(Ref));
        return *this;
    }

    T* Get() const noexcept {
        auto* ref = ObjectRef::Get();
        return static_cast<T*>(ref);
    }

    T* operator->() const noexcept { return Get(); }
    T* operator->() noexcept { return Get(); }

    T& operator*() const noexcept { return *Get(); }
    T& operator*() noexcept { return *Get(); }
};


template<IsObject T>
ObjectRefT<T> MakeObject(auto&&... Args) noexcept {
    return ObjectRefT(new T(std::forward<decltype(Args)>(Args)...));
}

} // namespace be

