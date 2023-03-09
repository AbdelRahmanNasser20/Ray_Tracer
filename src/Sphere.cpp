// implementation code for Sphere object class

#include "Sphere.hpp"
#include "Ray.hpp"
#include "Vec3.inl"
#include "World.hpp"


Sphere::Sphere(const Vec3 color_, const Vec3 center_, float radius_, const std::string surface_)
    : Object(color_,surface_)
{
    C = center_;
    R = radius_;
    Rsquared = R*R;
}

// sphere-ray intersection
float Sphere::intersect(const Ray &r) const
{
    // solve p=r.start-center + t*r.direction; p*p -radius^2=0
    float a = r.D_dot_D;
    Vec3 g = r.E - C;
    float b = dot(r.D, g);
    float c = dot(g,g) - Rsquared;

    float discriminant = b*b - a*c; // no intersection if negative
    if (discriminant < 0) return Ray::infinity;

    // solve quadratic equation for desired surface
    float dsq = sqrtf(discriminant);
    float t = (-b - dsq) / a;       // first intersection within ray extent?
    
    if (t > Ray::epsilon) return t;

    t = (-b + dsq) / a;             // second intersection within ray extent?
    if (t > Ray::epsilon) return t;

    return Ray::infinity;           // sphere entirely behind start point
}

Vec3 Sphere::normal(Vec3 & T) const {
    return normalize(T - this->C);
}
