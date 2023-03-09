// polygon objects
#pragma once

// other classes we use DIRECTLY in our interface
#include "Object.hpp"
#include "Vec3.hpp"
#include <string>
// system includes necessary for the interface
#include <vector>

class Polygon : public Object {
private: // private data
    struct PolyVert {
        Vec3 V;              // vertex location
        float Vt, Vb;       // coordinates in plane tangent basis

        PolyVert(const Vec3 V_) { V = V_; }
    };
    typedef std::vector<PolyVert> VertexList;

    VertexList vertices;    // list of vertices
    Vec3 N;                 // face normal
    Vec3 T;                 // first basis vector in polygon plane
    Vec3 B;                 // 2nd basis vector in polygon plane
    float V0_dot_N;         // derived, for intersection testing
    const std::string surfname;

public: // constructors
    Polygon(const Vec3 color_, const std::string surface_);

public: // manipulators
    // add a new vertex to the polygon
    // given vertex and per-vertex normal
    void addVertex(const Vec3 v);

    // close the polygon after the last vertex
    void closePolygon();

public: // object functions
    float intersect(const Ray &ray) const override;
    Vec3 normal(Vec3 & T) const override;
};
