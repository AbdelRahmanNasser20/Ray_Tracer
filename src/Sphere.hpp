// sphere objects
#pragma once

// other classes we use DIRECTLY in the interface
#include "Object.hpp"
#include "Vec3.hpp"
#include "World.hpp"
#include <string>

// sphere objects
class Sphere : public Object {
    Vec3 C;
    float R;
    // derived, for intersection testing
    float Rsquared;
    const std::string surfname;
    Vec3 N;

public: // constructors
    Sphere(const Vec3 color, const Vec3 center, float radius, const std::string surfname);

public: // object functions
    float intersect(const Ray &ray) const override;
    Vec3 normal(Vec3 & T) const override;
};

