cmake_minimum_required(VERSION 3.20)
project(OGLD_LIBRARY)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

include_directories(/ThirdParty)

file(GLOB OGLD_SOURCE_FILES
        "Source/Components/*/*.cpp"
        "Source/Components/*/*.h"
        "Source/Core/*.cpp"
        "Source/Core/*.h"
        "Source/OpenGL/*.cpp"
        "Source/OpenGL/*.h"
        "../ThirdParty/OpenGL/gl_core_4_5.cpp"
        )

add_library(OGLD_LIBRARY STATIC ${OGLD_SOURCE_FILES})

add_subdirectory(../ThirdParty/glfw ThirdParty/glfw)
add_subdirectory(../ThirdParty/glm ThirdParty/glm)

target_include_directories(OGLD_LIBRARY PUBLIC
        ../ThirdParty/
        )

target_link_libraries(OGLD_LIBRARY
        glfw
        glm
        OpenGL::GL
        )