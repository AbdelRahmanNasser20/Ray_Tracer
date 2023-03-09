// implementation code for World object
// World holds everything we know about the world.
// Code here initializes it based on file input

#include "World.hpp"
#include "Polygon.hpp"
#include "Sphere.hpp"
#include "Vec3.inl"
#include <math.h>
#include <istream>
#include <iostream>
#include <string>
#include <map>
using namespace std;

std::vector<World::Light> World::lights;
std::map<std::string, World::Surface> World::surfaceMap;

//void World::addLight(const Light &light) {
//    lights.push_back(light);
//}
//
//void World::addSurface(const Surface &surface, const std::string surfname) {
//    surfaceMap[surfname] = surface;
//}

// scoped global for what is enabled
World::Features World::enables;

// feature defaults
World::Features::Features()
{
    spheres = polygons = true;
}

// read input file
World::World(std::istream &ifile)
: eye(0,-8,0), width(512), height(512)
{
    int SphereCount = 0, PolyCount = 0;

    // temporary variables while parsing
    Vec3 look(0,0,0), up(0,1,0);
    float xfov=45, yfov=45;
    std::string surfname;
    bool read = true;

    // map of surface names to colors, only need while parsing
//    Surface *currentSurface = &World::surfaceMap[""];

    // parse file one token at a time
    std::string token;
    ifile >> token;
    while(! ifile.eof()) {
//        cout << "Start -> Outer loop the token:: " << token << endl;
        if (token == "background")
            ifile >> objects.background[0] >> objects.background[1] >> objects.background[2];
        else if (token == "eyep")
            ifile >> eye[0] >> eye[1] >> eye[2];
        else if (token == "lookp")
            ifile >> look[0] >> look[1] >> look[2];
        else if (token == "up")
            ifile >> up[0] >> up[1] >> up[2];
        else if (token == "fov")
            ifile >> xfov >> yfov;
        else if (token == "screen")
            ifile >> width >> height;
        else if (token == "light"){
            Light light;
            ifile >> light.intensity >> light.type >> light.x >> light.y >> light.z;
            lights.push_back(light);
        }

        else if (token == "surface") {
            ifile >> surfname;
            Surface *currentSurface;
            currentSurface = &World::surfaceMap[surfname];
            currentSurface->name = surfname;
            
            ifile >> token;
            while(!ifile.eof()) {
//                cout << "\t\t INNER SURFACE loop the token is " << token << endl;
                if (token == "diffuse")
                    ifile >> (currentSurface->diffuse)[0] >> (currentSurface->diffuse)[1] >> (currentSurface->diffuse)[2];
                else if (token == "ambient")
                    ifile >> currentSurface->ambient[0] >> currentSurface->ambient[1] >> currentSurface->ambient[2];
                else if (token == "specular")
                    ifile >> currentSurface->specular[0] >> currentSurface->specular[1] >> currentSurface->specular[2];
                else if (token == "specpow")
                    ifile >> currentSurface->specpow;
                else if (token == "reflect")
                    ifile >> currentSurface->reflect;
                else{
//                    cout << "\t\tbreaking out of token " << token << endl;
                    read = false;
                    break;
                }
                
                ifile >> token;
            }
//            cout << "done with Surface the current token is " << token << endl;

        }
        else if (enables.polygons && (token == "polygon" || token == "triangle")) {
            ifile >> surfname;
            Polygon *poly = new Polygon(surfaceMap[surfname].diffuse, surfname);
            Vec3 vert;
            try { // read until stof throws on non-numeric token
                while(! ifile.eof()) {
                    ifile >> token; vert[0] = std::stof(token);
                    ifile >> token; vert[1] = std::stof(token);
                    ifile >> token; vert[2] = std::stof(token);
                    
                    if (ifile.eof()) break;
                    poly->addVertex(vert);
                }
            }
            catch(...) {}
            poly->closePolygon();
            objects.addObject(poly);
            ++PolyCount;

            // have an unused non-numeric token
            // skip token read at end of loop to process next iteration
            continue;
        }

         else if (enables.spheres && token == "sphere") {
            float radius;
            Vec3 center;
            ifile >> surfname >> radius >> center[0] >> center[1] >> center[2];
            objects.addObject(new Sphere(surfaceMap[surfname].diffuse, center, radius, surfname));
            ++SphereCount;
        }
//        cout << "---------END last token read is-->" << token  << " bool:: " << read << endl;
        if (read)
            ifile >> token;
        read = true;
    }
    
    // compute view basis
    w = eye - look;
    dist = length(w);
    w = normalize(w);
    u = normalize(cross(up, w));
    v = cross(w, u);

    // solve for screen edges
    right = dist * tanf(xfov * 3.1415926536f/360);
    left = -right;
    top = dist * tanf(yfov * 3.1415926536f/360);
    bottom = -top;

    // report loading stats
    std::cout << objects.size() << " Objects (" 
        << SphereCount << " Sphere" << (SphereCount == 1 ? "" : "s") << ", " 
        << PolyCount << " Polygon" << (PolyCount == 1 ? "" : "s") << ")\n";   
}


//int main1(){
//    std::string ifname = "/Users/abdelnasser/Desktop/cg23/assn1soln/data/balls.ray";
//    std::ifstream infile(ifname);
//    cout << "attempting to read file" << endl;
//    World world(infile);
//
//        std::cout << "Surface Information:" << std::endl;
//        for (auto& s : World::surfaceMap) {
//            std::cout << "Name: " << s.second.name << std::endl;
//            std::cout << "Ambient: " << s.second.ambient[0] << ", " << s.second.ambient[1] << ", " << s.second.ambient[2] << std::endl;
//            std::cout << "Diffuse: " << s.second.diffuse[0] << ", " << s.second.diffuse[1] << ", " << s.second.diffuse[2] << std::endl;
//            std::cout << "Specular: " << s.second.specular[0] << ", " << s.second.specular[1] << ", " << s.second.specular[2] << std::endl;
//            std::cout << "Specular power: " << s.second.specpow << std::endl;
//            std::cout << "Reflectivity: " << s.second.reflect << std::endl;
//        }
//
//        for (const auto& light : World::lights) {
//            std::cout << "Intensity: " << light.intensity << std::endl;
//            std::cout << "Type: " << light.type << std::endl;
//            std::cout << "Position: (" << light.x << ", " << light.y << ", " << light.z << ")" << std::endl;
//        }
//
//}
