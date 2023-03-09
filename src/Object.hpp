// pure virtual base class for any object
#pragma once

// other classes we use DIRECTLY in our interface
#include "Vec3.hpp"
#include <string>
// classes we only use by pointer or reference
class Ray;

class Object {
public: // public data
    Vec3 color;                   // this object's color
    std::string surfname;         // this object's surface name

public: // constructor & destructor
    Object();
    Object(const Vec3 _color, const std::string surfname);
    virtual ~Object();


public: // computational members
    // return t for closest intersection with ray
    virtual float intersect(const Ray &ray) const = 0;
    virtual Vec3 normal(Vec3 & T) const = 0;

};
