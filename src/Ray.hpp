// Rays
#pragma once

// other classes we use DIRECTLY in our interface
#include "Vec3.hpp"

// a ray consists of a starting point and direction
// ray is defined as start + t*direction, for t>=0
class Ray {

public: // scoped constants
    // constants for infinity and small value for comparisons
    static const float infinity, epsilon;

public: // public data
    Vec3 E;             // ray start point
    Vec3 D;             // ray direction

    // derived, for intersection testing
    float D_dot_D;

public: // constructors
    Ray(const Vec3 start_, const Vec3 direction_);
};
