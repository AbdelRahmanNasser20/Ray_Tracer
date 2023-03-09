// implementation code for ObjectList class
// list of objects in scene

#include "ObjectList.hpp"
#include "Object.hpp"
#include "Ray.hpp"
#include <iostream>
#include "World.hpp"
#include "Vec3.inl"
#include <math.h>
#include "Sphere.hpp"
using namespace std;


const int MAXDEPTH = 15;
const float REFLECTIONCOEFFICIENTS = 0.002;

static std::size_t RayCount = 0, IsectCount = 0;

// destructor: report ray stats and delete all contained objects
ObjectList::~ObjectList() {
    std::cout << RayCount << " Photon Ray" << (RayCount == 1 ? "" : "s") << '\n';
    std::cout << IsectCount << " Intersection" << (IsectCount == 1 ? "" : "s") << '\n';

    for(auto obj : objects)
        delete obj;
}

// trace ray r through all objects, returning first intersection
Vec3 ObjectList::trace(const Ray &r, int depth, float reflectionCoefficent) const
{
    //The recursion should stop when the number of bounces reaches the maxdepth (default 15), or the product of the reflection coefficients along the ray is less than the cutoff (default 0.002)
    if (depth >= MAXDEPTH || reflectionCoefficent < REFLECTIONCOEFFICIENTS) {
        return Vec3(0,0,0);
    }
    
    ++RayCount;
    
    // initially null object at furthest distance
    Object *hitObj = nullptr;
    float hitT = Ray::infinity;

    // check all objects for a closer intersection
    for(auto obj : objects) {
        ++IsectCount;
        float current = obj->intersect(r);
        if (current < hitT) {
            hitT = current;
            hitObj = obj;
        }
    }
    
    
//    return hitObj ? hitObj->color : background;
    // no intersection
    if (!hitObj) return background;
    
    Vec3 color(0,0,0);
    
    Vec3 P = r.E + hitT * r.D; // the intersection point
    Vec3 N = hitObj->normal(P);
    const World::Surface S = World::surfaceMap[hitObj->surfname]; // surface parameter
    
    // iterate over every light
    for (auto &light : World::lights) {
        
        // calculate the position of the light and the normal vector
        Vec3 lightPosition(light.x, light.y, light.z);
        Vec3 L = normalize(lightPosition - P);
        float NdotL = dot(N,L);
        
        Ray objLightRay(P,L); // create a ray for obj intersection and light
        
        // diffuse if no shadow
        if (NdotL > 0 and probe(objLightRay, length(lightPosition - P))){
            
            float I = light.intensity * NdotL;
            Vec3 diffuseXIntensity = (S.diffuse * I);
            color = color + diffuseXIntensity;
            

            Vec3 H = normalize(L + normalize(r.D));
            float NdotH = dot(N, H);

            //  apply specular
            if (NdotH > 0){
                Vec3 specularXIntensity = (S.specular * I);
                specularXIntensity = specularXIntensity * (pow(NdotH, S.specpow));
                color = color + specularXIntensity;
            }
        }
    }
    
    Vec3 reflectionDirection = 2 * N * dot(N,-r.D) - (-r.D);
    reflectionCoefficent *= S.reflect;
    Ray reflectionRay(P, reflectionDirection);
    color = color + (S.reflect * trace(reflectionRay, depth + 1, reflectionCoefficent));

    return color;
    
}

//You will want two ray tracing functions. The first, commonly called probe or anyhit, is used for shadow testing. 
//It should return true if there is any intersection between the start and end of the ray, and does not need to necessarily 
//find the closest intersection or continue intersection testing once it has found a hit.
bool ObjectList::probe(const Ray& r, const float distance) const {
    for (auto obj : objects) {
        if (Ray::epsilon < obj->intersect(r) && obj->intersect(r) < distance) {
            return false;
        }
    }
    return true;
}
