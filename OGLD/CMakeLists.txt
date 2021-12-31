cmake_minimum_required(VERSION 3.20)
project(OGLD)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

include_directories(/ThirdParty)

file(GLOB OGLD_SOURCE_FILES
        "Source/Components/*/*.cpp"
        "Source/Components/*/*.hpp"
        "Source/Core/*.cpp"
        "Source/Core/*.hpp"
        "Source/OpenGL/*.cpp"
        "Source/OpenGL/*.hpp"
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