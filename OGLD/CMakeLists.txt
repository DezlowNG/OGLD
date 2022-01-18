cmake_minimum_required(VERSION 3.20)
project(OGLD)

set(CMAKE_CXX_STANDARD 17)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(/ThirdParty)

file(GLOB OGLD_SOURCE_FILES
        "Source/Components/*/*.cpp"
        "Source/Components/*/*.hpp"
        "Source/Objects/*.cpp"
        "Source/Objects/*.hpp"
        "Source/Core/*.cpp"
        "Source/Core/*.hpp"
        "Source/OpenGL/*.cpp"
        "Source/OpenGL/*.hpp"
        "Source/*.cpp"
        "Source/*.hpp"
        )

file(GLOB IMGUI_SRC
        "../ThirdParty/ImGui/*.cpp"
        "../ThirdParty/ImGui/*.h"
        "../ThirdParty/ImGui/backends/imgui_impl_opengl3.cpp"
        "../ThirdParty/ImGui/backends/imgui_impl_glfw.cpp"
        )

add_library(OGLD_LIBRARY STATIC ${OGLD_SOURCE_FILES} ${IMGUI_SRC})

add_subdirectory(../ThirdParty/glfw ThirdParty/glfw)
add_subdirectory(../ThirdParty/glm ThirdParty/glm)
add_subdirectory(../ThirdParty/OpenGL ThirdParty/OpenGL)

target_include_directories(OGLD_LIBRARY PUBLIC
        ../ThirdParty/
        ../ThirdParty/ImGui/
        )

target_link_libraries(OGLD_LIBRARY
        OGL
        glfw
        glm
        )