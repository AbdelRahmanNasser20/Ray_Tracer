#pragma once
// Inline functions for Vec3 class

#include "Vec3.hpp"
#include <math.h>

/////////
// access as an array vec[i] rather than vec.data[i]
inline float Vec3::operator[](int i) const { return data[i]; }
inline float &Vec3::operator[](int i) { return data[i]; }

//////////
// component-wise operations: -v, v1+v2, v1-v2, v1*v2, v1/v2
// operations with a scalar: s*v, v*s, v/s
// vector operations: cross(v1,v2), dot(v1,v2), length(v), normalize(v)

// negate v
inline Vec3 operator-(const Vec3 v) {
    return Vec3(-v[0], -v[1], -v[2]);
}

// vector addition, v1+v2
inline Vec3 operator+(const Vec3 v1, const Vec3 v2) {
    return Vec3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

// vector subtraction, v1-v2
inline Vec3 operator-(const Vec3 v1, const Vec3 v2) {
    return Vec3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

// vector component-wise multiplication, v1*v2
inline Vec3 operator*(const Vec3 v1, const Vec3 v2) {
    return Vec3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

// vector component-wise division, v1/v2
inline Vec3 operator/(const Vec3 v1, const Vec3 v2) {
    return Vec3(v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]);
}

// scalar multiplication, s*v
inline Vec3 operator*(float s, const Vec3 v) {
    return Vec3(s*v[0], s*v[1], s*v[2]);
}

// scalar multiplication, v*s
inline Vec3 operator*(const Vec3 v, float s) {
    return Vec3(s*v[0], s*v[1], s*v[2]);
}

// scalar division, v/s
inline Vec3 operator/(const Vec3 v, float s) {
    return v*(1/s);
}

// cross product, cross(v1,v2)
inline Vec3 cross(const Vec3 v1, const Vec3 v2) {
    return Vec3(v1[1]*v2[2] - v1[2]*v2[1],
                v1[2]*v2[0] - v1[0]*v2[2],
                v1[0]*v2[1] - v1[1]*v2[0]);
}

// vector dot product, dot(v1,v2)
inline float dot(const Vec3 v1, const Vec3 v2) {
    return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

// return Euclidean vector length, length(v)
inline float length(const Vec3 v) {
    return sqrtf(dot(v, v));
}

// return normalized vector, normalize(v)
inline Vec3 normalize(const Vec3 v) {
    return v / length(v);
}
