cmake_minimum_required(VERSION 3.12.4)
# Set the correct module path

# Define variables that would come from root CMakeLists.txt
#set(mhbcore multi-half-bridge-corelib)

# Project name and languages
project(multi_half_bridge_py)

# Include directories
include_directories(
    pal/
    wrapper/
)


# Set header and source files
set(Headers
    pal/
    wrapper/
)

# List source files
set(Sources
    pal/gpio-rpi.cpp
    pal/logger-rpi.cpp
    pal/spic-rpi.cpp
    pal/timer-rpi.cpp
    wrapper/tle94112-rpi.cpp
    wrapper/tle94112-pybind.cpp
)


# pybind11 integration
find_package(pybind11 REQUIRED)


pybind11_add_module(multi_half_bridge_py ${Sources} ${Headers})

# Create the directory structure that setuptools expects and copy the library there
# This is the proper way to handle pybind11 modules with setuptools
add_custom_command(TARGET multi_half_bridge_py POST_BUILD
    # Create the lib.linux-aarch64-cpython-311 directory at the right level
    COMMAND ${CMAKE_COMMAND} -E make_directory 
        "${CMAKE_BINARY_DIR}/../lib.linux-aarch64-cpython-311"
    # Copy the built library to where setuptools expects it
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:multi_half_bridge_py>"
        "${CMAKE_BINARY_DIR}/../lib.linux-aarch64-cpython-311/$<TARGET_FILE_NAME:multi_half_bridge_py>"
    COMMENT "Copying Python module to setuptools expected location"
)

# Add Raspberry Pi bcm library dependency
find_library(bcm2835_dir NAMES libbcm2835.a)

message(STATUS ${bcm2835_dir})

add_library(bcm2835 STATIC IMPORTED)
set_target_properties(bcm2835 PROPERTIES IMPORTED_LOCATION ${bcm2835_dir})

# Link libraries
target_link_libraries(multi_half_bridge_py PUBLIC
    multi-half-bridge-corelib
    bcm2835
    cap         
)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(multi_half_bridge_py PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})