// implementation code for Object parent class

#include "Object.hpp"

// default constructor just uses default color
Object::Object() {}

// construct object given color
Object::Object(const Vec3 color_, const std::string surfname_) {
    color = color_;
    surfname = surfname_;
}

// virtual destructor since this class has virtual members and derived children
Object::~Object() {}
