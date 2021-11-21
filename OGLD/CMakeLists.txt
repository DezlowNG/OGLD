cmake_minimum_required(VERSION 3.20)
project(OGLD_LIBRARY)

set(CMAKE_CXX_STANDARD 20)

file(GLOB OGLD_SOURCE_FILES
        "Source/*.cpp"
        )

add_library(OGLD_LIBRARY STATIC ${OGLD_SOURCE_FILES})