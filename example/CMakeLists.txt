cmake_minimum_required(VERSION 3.1)
set(COLLEEN_ROOT ${CMAKE_CURRENT_LIST_DIR}/..)
include(${COLLEEN_ROOT}/CMakeLists.txt)
include(${COLLEEN_ROOT}/config_generator/colleen.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COLLEEN_EXAMPLE_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(COLLEEN_EXAMPLE_SOURCE_DIR ${COLLEEN_EXAMPLE_ROOT}/source)
set(COLLEEN_EXAMPLE_INCLUDE_DIR ${COLLEEN_EXAMPLE_ROOT}/include)

project(colleen-example)
add_executable(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${COLLEEN_EXAMPLE_INCLUDE_DIR}
        )
file(GLOB_RECURSE COLLEEN_EXAMPLE_SOURCES ${COLLEEN_EXAMPLE_SOURCE_DIR}/*.cpp)
target_sources(${PROJECT_NAME}
        PRIVATE
        ${COLLEEN_EXAMPLE_SOURCES})

set(EXAMPLE_OPTIONS ${COLLEEN_EXAMPLE_ROOT}/configuration/example_options.json ${COLLEEN_EXAMPLE_ROOT}/configuration/example_options_1.json)
target_add_colleen_config(${PROJECT_NAME} "${EXAMPLE_OPTIONS}")
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wno-unknown-pragmas)

