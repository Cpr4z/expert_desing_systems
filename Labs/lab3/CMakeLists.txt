cmake_minimum_required(VERSION 3.29)
project(lab3)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(HEADERS
        types/common.hpp
        types/graph.hpp
        utils/io_utils.hpp
        graph/graph.hpp
        graph/depth_first_search.hpp
        utils/my_stack.hpp
)

set(SOURCES
    graph/graph.cpp
    graph/depth_first_search.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${HESDERS} ${SOURCES} main.cpp)
