cmake_minimum_required(VERSION 3.20)
project(OGL)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)

include_directories(include/OpenGL)

add_library(OGL STATIC src/gl_core_4_5.cpp include/OpenGL/gl_core_4_5.hpp)
target_include_directories(OGL INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_link_libraries(OGL
        OpenGL::GL
        )