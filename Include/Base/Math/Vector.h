/*
 * File: Vector.h
 * Author: kissholic
 * Copyright (c) 2025 kissholic. All wrongs reserved.
 */

#pragma once




namespace be {


template <typename T>
struct Vector2 {
	T X;
	T Y;

	T& operator[](int idx) {
		return (&X)[idx];
	}

	T const& operator[](int idx) const {
		return (&X)[idx];
	}
};


using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;


template <typename T>
struct Vector3 {
	T X;
	T Y;
	T Z;

	T& operator[](int idx) {
		return (&X)[idx];
	}

	T const& operator[](int idx) const {
		return (&X)[idx];
	}
};


using Vector3i = Vector3<int>;
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;


template <typename T>
inline Vector3<T> MakeVectorOnes() {
	return Vector3<T>(1, 1, 1);
}


template <typename T>
inline Vector3<T> MakeVectorZeros() {
	return Vector3<T>(0, 0, 0);
}



} // namespace be
