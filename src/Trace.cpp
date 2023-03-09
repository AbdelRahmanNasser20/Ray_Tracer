// ray tracer main program
// includes input file parsing and spawning screen pixel rays

#include "World.hpp"
#include "Ray.hpp"
#include "Vec3.inl"
#include "Color.hpp"
#include "Config.h"
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <cstring>
// #include "omp.h"

using namespace std;

int main(int argc, char **argv)
{
    auto startTime = chrono::high_resolution_clock::now();

    // parse command line arguments
    char *filename = nullptr;
    char *progname = argv[0];
    for(++argv, --argc;  argc != 0;  ++argv, --argc) {
        // print usage on -h, -help, -?, --h, --help, etc.
        if (strncmp(argv[0], "-h", 2) == 0 || 
                strncmp(argv[0], "--h", 3) == 0 || 
                strcmp(argv[0], "-?") == 0)
            break;

        // remaining arguments start + to turn on or - to turn off
        if (argv[0][0] == '-' || argv[0][0] == '+') {
            bool state = argv[0][0] == '+';
            char *arg = argv[0]+1;
            if (strcmp(arg, "polygons") == 0) {
                World::enables.polygons = state;
                continue;
            }
            else if (strcmp(arg, "spheres") == 0) {
                World::enables.spheres = state;
                continue;
            }
        }

        // remaining sole argument is filename
        if (argc == 1)
            filename = argv[0];
        else
            break;
    }

    // unparsed arguments? print usage and exit
    if (!filename || argc != 0) {
        cerr << "Usage: " << progname << " [options] file.ray\n";
        cerr << "For options, use +option to enable, -option to disable\n";
        cerr << "Available options (with default state):\n";
        cerr << "  " 
            << (World::enables.spheres  ? '+' : '-') << "spheres, "
            << (World::enables.polygons ? '+' : '-') << "polygons = primitives\n";
        cerr << '\n';
        cerr << "If file.ray is an absolute path, use directly\n";
        cerr << "Otherwise input from " << PROJECT_DATA_DIR << "file.ray\n";
        cerr << "Output to " << PROJECT_BUILD_DIR << "trace.ppm\n";
        return 1;
    }

    // find and open input file
    string ifname = PROJECT_DATA_DIR;
    if (filename[0] == '/') // absolute path
        ifname = filename;
    else                    // file in data directory
        ifname += filename;
    
    ifstream infile(ifname);
    if (!infile) {
        cerr << "Error opening " << ifname << '\n';
        return 1;
    }

    // parse the input into everything we know about the world
    World world(infile);

    // array of image data in ppm-file order
    Color *pixels = new Color[world.height*world.width];

    int thread_sum[4];
    // spawn a ray for each pixel and place the result in the pixel
    for(int y=0, i=0; y<world.height; ++y) {
        // ray direction for first pixel in row
        float vs = world.top  + (world.bottom - world.top ) * (y+0.5f)/world.height;
        Vec3 rowStart = -world.dist * world.w + vs * world.v;

        for(int x=0; x<world.width; ++x, ++i) {
            // trace new ray
            float us = world.left + (world.right - world.left) * (x+0.5f)/world.width;
            Vec3 dir = rowStart + us * world.u ;
            Ray ray(world.eye, dir);
            pixels[i] = Color(world.objects.trace(ray,0, 1.0));
        }

        if (y % 32 == 0) cout << "line " << y << '\n'; // render progress
    }
    
    // write ppm file of pixels
    string ofname = PROJECT_BUILD_DIR "trace.ppm";
    ofstream output(ofname, ofstream::out | ofstream::binary);
    output << "P6\n" << world.width << ' ' << world.height << '\n' << 255 << '\n';
    output.write((char *)(&pixels[0]), world.height*world.width * sizeof(Color));

    delete[] pixels;

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<float> elapsed = endTime - startTime;
    cout << elapsed.count() << " seconds\n";
    return 0;
}

// cr
