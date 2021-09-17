cmake_minimum_required(VERSION 3.1)
project(colleen)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

execute_process(COMMAND conan profile update settings.compiler.libcxx=libstdc++11 default)
execute_process(COMMAND conan install ${CMAKE_CURRENT_LIST_DIR})
include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(spdlog fmt)


set(COLLEEN_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/source)
set(COLLEEN_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

file(GLOB_RECURSE COLLEEN_SOURCES ${COLLEEN_SOURCE_DIR}/*.cpp)

if (NOT TARGET ${PROJECT_NAME})
    add_library(${PROJECT_NAME})
    target_sources(${PROJECT_NAME}
            PRIVATE
            ${COLLEEN_SOURCES}
            )
    target_include_directories(${PROJECT_NAME}
            PUBLIC
            ${COLLEEN_INCLUDE_DIR}
            )
    target_link_libraries(${PROJECT_NAME}
            PUBLIC
            spdlog
            fmt
            )
endif ()