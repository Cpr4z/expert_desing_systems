cmake_minimum_required(VERSION 3.29)
project(lab4)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)

set(HEADERS
        atom.hpp
        clause.hpp
        resolution.hpp
        resolvent.hpp
        io_join.hpp
)

set(SOURCES
        atom.cpp
        clause.cpp
        resolution.cpp
        resolvent.cpp
    )


add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} main.cpp)
