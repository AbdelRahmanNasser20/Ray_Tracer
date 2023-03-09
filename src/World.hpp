// Everything we know about the world
#pragma once

// other classes we use DIRECTLY in our interface
#include "Vec3.hpp"
#include "ObjectList.hpp"
#include <fstream>
#include <map>
#include <string>

class World {
public: // public data
    // feature flags
    struct Features {
        bool spheres : 1;
        bool polygons : 1;

        Features();
    };
    struct Light {
        float intensity;
        std::string type;
        float x, y, z;
    };
    
    struct Surface {
        std::string name;
        Vec3 ambient;
        Vec3 diffuse;
        Vec3 specular;
        float specpow;
        float reflect;
    };
    
    static Features enables;

    // image size
    int width, height;

    // view origin and basis parameters
    Vec3 eye, w, u, v;
    float dist, left, right, bottom, top;


    // list of objects in the scene
    ObjectList objects;
    
    static std::vector<Light> lights; // list of lights
    static std::map<std::string, Surface> surfaceMap; // map of string to surfaces

public:                                 
    // constructor: read world data from a file
    World(std::istream &ifile);
//    static void addLight(const Light &light);
//    static void addSurface(const Surface &surface, const std::string surfname);
};


