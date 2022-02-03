cmake_minimum_required(VERSION 3.20)
project(OGLD)

set(CMAKE_CXX_STANDARD 17)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(/ThirdParty)

file(GLOB OGLD_SRC
        "Source/Components/*/*.cpp"
        "Source/Objects/*.cpp"
        "Source/Core/*.cpp"
        "Source/OpenGL/*.cpp"
        "Source/*.cpp"
        )

if (NOT (DEFINED ${OGLD_GL_VERSION_MAJOR}))
    set(OGLD_GL_VERSION_MAJOR 3)
endif()
if (NOT (DEFINED ${OGLD_GL_VERSION_MINOR}))
    set(OGLD_GL_VERSION_MINOR 3)
endif()
if (NOT DEFINED OGLD_USE_IMGUI)
    set(OGLD_USE_IMGUI 0)
elseif(${OGLD_USE_IMGUI})
    set(OGLD_USE_IMGUI 1)
else()
    set(OGLD_USE_IMGUI 0)
endif()
configure_file("Source/Core/Config.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Config.hpp")

if(${OGLD_USE_IMGUI})
    file(GLOB IMGUI_SRC
            "../ThirdParty/ImGui/*.cpp"
            "../ThirdParty/ImGui/backends/imgui_impl_opengl3.cpp"
            "../ThirdParty/ImGui/backends/imgui_impl_glfw.cpp"
            )
endif()

add_library(OGLD_LIBRARY STATIC ${OGLD_SRC} ${IMGUI_SRC})

add_subdirectory(../ThirdParty/glfw ThirdParty/glfw)
add_subdirectory(../ThirdParty/glm ThirdParty/glm)
add_subdirectory(../ThirdParty/OpenGL ThirdParty/OpenGL)

if (${OGLD_USE_IMGUI})
    target_include_directories(OGLD_LIBRARY PUBLIC
            ../ThirdParty/ImGui/
            )
endif()
target_include_directories(OGLD_LIBRARY PUBLIC
        ../ThirdParty/
        )

target_link_libraries(OGLD_LIBRARY
        OGL
        glfw
        glm
        )