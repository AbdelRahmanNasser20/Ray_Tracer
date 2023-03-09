// lists of objects in scene
#pragma once

// other classes we use DIRECTLY in our interface
#include "Vec3.hpp"
#include <vector>

// classes we only use by pointer or reference
class Object;
class Ray;

class ObjectList {
public:
    // list of objects
    typedef std::vector<Object*> ObjList;
    ObjList objects;

    // background color
    Vec3 background;

    // constructor & destructor
    ObjectList() {}
    ~ObjectList();

    // Add an object to the list. Objects should be allocated with
    // new. Objects will be deleted when this ObjectList is destroyed
    void addObject(Object *obj) { objects.push_back(obj); }

    // number of objects
    std::size_t size() { return objects.size(); }

    // trace ray r through all objects, returning first intersection
    Vec3 trace(const Ray&r, int depth, float reflectionCoefficent) const;
    bool probe(const Ray& r, const float distance) const;
    float reflectRay(Ray &r, Ray &n) const;

};
