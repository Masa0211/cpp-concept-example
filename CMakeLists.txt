cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# set the project name and version
# NOTE: `project` automatically defines `PROJECT_NAME` and `PROJECT_SOURSE_DIR`
project(GenericConcept VERSION 1.0)

# Generate executable
add_executable(GenericConcept sample.cpp)

# Set C++20 standard
set_property(TARGET GenericConcept PROPERTY CXX_STANDARD 20)
set_property(TARGET GenericConcept PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET GenericConcept PROPERTY CXX_EXTENSIONS OFF)
