cmake_minimum_required(VERSION 3.20)
project(OGLD_LIBRARY)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BINARY_DIR "../../../bin/${CMAKE_PROJECT_NAME}/${CMAKE_SYSTEM_NAME}")

find_package(OpenGL REQUIRED)

include_directories(/ThirdParty)

file(GLOB OGLD_SOURCE_FILES
        "Source/*.cpp"
        )

add_library(OGLD_LIBRARY STATIC ${OGLD_SOURCE_FILES})

add_subdirectory(../ThirdParty/glfw ${CMAKE_BINARY_DIR}/ThirdParty/glfw)
add_subdirectory(../ThirdParty/glm ${CMAKE_BINARY_DIR}/ThirdParty/glm)
add_subdirectory(../ThirdParty/glad ${CMAKE_BINARY_DIR}/ThirdParty/glad)

target_link_libraries(OGLD_LIBRARY
        glfw
        glm
        glad
        OpenGL::GL
        )