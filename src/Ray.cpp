// implementation for Ray class

#include "Ray.hpp"
#include "Vec3.inl"

// constants for infinity and small value for comparisons
const float Ray::infinity = 1.f / 0.f;
const float Ray::epsilon = 1e-4f;

Ray::Ray(const Vec3 start_, const Vec3 direction_)
{
    E = start_;
    D = direction_;
    D_dot_D = dot(D,D);
}
