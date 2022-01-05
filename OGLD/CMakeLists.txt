cmake_minimum_required(VERSION 3.20)
project(OGLD)

set(CMAKE_CXX_STANDARD 17)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)

include_directories(/ThirdParty)

file(GLOB OGLD_SOURCE_FILES
        "Source/Components/Camera/*.cpp"
        "Source/Components/Camera/*.hpp"
        "Source/Objects/*.cpp"
        "Source/Objects/*.hpp"
        "Source/Objects/Terrain/*.cpp"
        "Source/Objects/Terrain/*.hpp"
        "Source/Objects/Cube/*.cpp"
        "Source/Objects/Cube/*.hpp"
        "Source/Core/*.cpp"
        "Source/Core/*.hpp"
        "Source/OpenGL/*.cpp"
        "Source/OpenGL/*.hpp"
        "Source/*.cpp"
        "Source/*.hpp"
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