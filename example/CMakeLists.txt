cmake_minimum_required(VERSION 3.1)
project(Colleen-Tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COLLEEN_EXAMPLE_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(COLLEEN_ROOT ${COLLEEN_EXAMPLE_ROOT}/..)
set(COLLEEN_EXAMPLE_SOURCE_DIR ${COLLEEN_EXAMPLE_ROOT}/source)
set(COLLEEN_EXAMPLE_INCLUDE_DIR ${COLLEEN_EXAMPLE_ROOT}/include)

include(${COLLEEN_ROOT}/CMakeLists.txt)


include_directories(${COLLEEN_EXAMPLE_INCLUDE_DIR})
set(EXAMPLE_SOURCES
        ${COLLEEN_EXAMPLE_SOURCE_DIR}/colleen/example/main.cpp
        )

add_definitions("-Wall -Werror -Wno-unknown-pragmas")
add_executable(example ${EXAMPLE_SOURCES})
target_link_libraries(example colleen)

