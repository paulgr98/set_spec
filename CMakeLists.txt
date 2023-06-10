cmake_minimum_required(VERSION 3.24)

set(This spec)

project(${This} CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set (Headers
    cunits.hpp
        specVec.hpp Rand.hpp specSet.hpp)

set (Sources
        main.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_executable(src main.cpp)

add_subdirectory(test)