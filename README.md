# A Basic Ray Tracing Engine

The Trace project is a rudimentary ray tracing engine designed to render scenes described by .ray files. Using ray tracing, the program simulates the path of rays of light as they interact with objects in a scene. This method is fundamental in producing high-quality images that simulate realistic lighting conditions.

## Features:
- Parse custom .ray files: For scene description.
- Configurable Rendering: Enable or disable rendering of specific primitives like spheres and polygons.
- Output in PPM format: Provides the rendered image as a .ppm file.
- Real-time Feedback: Display render progress and total elapsed rendering time.

## How to Build and Run:
### 1. Build the Project:

```
mkdir build
cd build
cmake ..
make  # For Unix-like systems. On Windows, use the appropriate build command.
```

### 2. Run the Project:
To run the project, you need to provide a .ray file containing the scene description.

```
./Trace [options] your_scene_file.ray
```

The program will generate an output image named trace.ppm in the build directory.

## Options:
You can control the ray tracing process with several command-line options:

- +spheres or -spheres: Enable or disable the rendering of spheres respectively.
- +polygons or -polygons: Enable or disable the rendering of polygons respectively.

For instance, to render a scene without spheres, use:

```
./Trace -spheres your_scene_file.ray
```

### Input and Output:
- Input:
  - If file.ray is an absolute path, the program will use it directly.
  - Otherwise, the program expects the file in the data directory (PROJECT_DATA_DIR).

- Output:
  - The program will output the rendered scene to trace.ppm in the build directory (PROJECT_BUILD_DIR).
