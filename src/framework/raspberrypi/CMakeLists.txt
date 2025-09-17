cmake_minimum_required(VERSION 3.12.4)

# Project name and languages
project(multi_half_bridge_py)

# Include directories for core library and local sources
include_directories(
    pal/                     # Local platform implementation
    wrapper/                 # Python wrapper
)

# Local platform and wrapper source files
set(Sources
    pal/gpio-rpi.cpp
    pal/logger-rpi.cpp
    pal/spic-rpi.cpp
    pal/timer-rpi.cpp
    wrapper/tle94112-rpi.cpp
    wrapper/tle94112-pybind.cpp
    ../../corelib/tle94112.cpp
    ../../corelib/tle94112-motor.cpp
    ../../corelib/tle94112-logger.cpp
)


# add_subdirectory(tools/pybind11)

# pybind11 integration
find_package(pybind11 REQUIRED)


pybind11_add_module(multi_half_bridge_py ${Sources})


# Add Raspberry Pi bcm library dependency
find_library(bcm2835_dir NAMES libbcm2835.a)

message(STATUS ${bcm2835_dir})

add_library(bcm2835 STATIC IMPORTED)
set_target_properties(bcm2835 PROPERTIES IMPORTED_LOCATION ${bcm2835_dir})

# Link libraries
target_link_libraries(multi_half_bridge_py PUBLIC
    bcm2835
    cap         
)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(multi_half_bridge_py PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})