// implementation code for Polygon object class

#include "Polygon.hpp"
#include "Ray.hpp"
#include "Vec3.inl"

Polygon::Polygon(const Vec3 color_, const std::string surface_) : Object(color_,surface_) {}

void
Polygon::addVertex(const Vec3 v)
{
    vertices.push_back(PolyVert(v));
}

void
Polygon::closePolygon()
{
    // compute normal from first two edges
    Vec3 V0 = vertices[0].V;
    Vec3 V1 = vertices[1].V;
    Vec3 V2 = vertices[2].V;
    Vec3 Vn = vertices.back().V;
    N = normalize(cross(V1 - V0, V2 - V0));

    // tangent and bitangent (2nd tangent perpendicular to 1st)
    // use edge between first and last vertex
    // avoids having to test that edge, and makes loops easier
    T = normalize(V0 - Vn);
    B = cross(N, T);

    // precomputed values for intersection testing
    V0_dot_N = dot(V0, N);
    for(auto &vert : vertices) {
        vert.Vt = dot(vert.V, T);
        vert.Vb = dot(vert.V, B);
    }
}

float Polygon::intersect(const Ray &ray) const 
{
    // compute intersection point with plane
    float t = (V0_dot_N - dot(N, ray.E)) / dot(N, ray.D);

    if (t < Ray::epsilon)
        return Ray::infinity;  // not in ray bounds: no intersection

    // 3D location where ray intersects polygon plane
    Vec3 P = ray.E + ray.D * t;

    // project P to onto plane basis vectors
    float Pt = dot(P, T), Pb = dot(P, B);

    // check if intersection is inside or outside
    // trace ray from p along a tangent vector and count even/odd intersections
    bool inside = false;
    for(auto v1 = vertices.begin(), v0 = v1++; v1 != vertices.end(); v0 = v1, ++v1) {
        // does edge straddle test ray where q dot bitangent = p dot bitangent?
        float b0 = v1->Vb - Pb, b1 = Pb - v0->Vb;
        if ((b0 > 0) ^ (b1 < 0)) {
            // outbound on test ray?
            float Qt = (b0 * v0->Vt + b1 * v1->Vt)/(v1->Vb - v0->Vb);
            if (Qt > Pt)
                inside = !inside;
        }
    }

    // hit at t if inside, otherwise miss
    return inside ? t : Ray::infinity;
}

Vec3 Polygon::normal(Vec3 & T) const {
    return N;
}
