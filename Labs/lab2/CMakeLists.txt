cmake_minimum_required(VERSION 3.29)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(
    HEADERS
    graph/breadth_first_search.hpp
    graph/graph.hpp
    types/graph.hpp
    types/common.hpp
    utils/io_utils.hpp
)

set(
    SOURCES
    graph/breadth_first_search.cpp
    graph/graph.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} main.cpp)
