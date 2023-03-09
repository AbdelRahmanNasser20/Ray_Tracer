cmake_minimum_required(VERSION 3.12...3.25)
project(Trace)
set(TARGET Trace)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET})

# set C++ version to use
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# I'm lazy here, and building with all cpp files in src
file(GLOB SOURCES  "src/*.cpp")
file(GLOB INCLUDES "src/*.hpp")
file(GLOB INLINES  "src/*.inl")
add_executable(${TARGET} ${SOURCES} ${INCLUDES} ${INLINES})

# set up config.h to find directories
set(PROJECT_BASE_DIR  "${PROJECT_SOURCE_DIR}")
set(PROJECT_DATA_DIR  "${PROJECT_BASE_DIR}/data")
set(PROJECT_BUILD_DIR "${PROJECT_BINARY_DIR}")
configure_file(src/Config.h.in Config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
