cmake_minimum_required(VERSION 3.29)
project(lab6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(
    HEADERS
    types/atom.hpp
    types/clause.hpp
    types/formula.hpp
    types/terminal.hpp
    ResolutionSolver.hpp
)

set(
    SOURCES
    types/atom.cpp
    types/clause.cpp
    types/formula.cpp
    types/terminal.cpp
    ResolutionSolver.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} main.cpp)
