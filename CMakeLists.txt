cmake_minimum_required(VERSION 3.1)
project(Colleen)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COLLEEN_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/source)
set(COLLEEN_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

include_directories(${COLLEEN_INCLUDE_DIR})
set(COLLEEN_SOURCES
        ${COLLEEN_SOURCE_DIR}/colleen/colleen.cpp
        ${COLLEEN_SOURCE_DIR}/colleen/argument.cpp
        )

add_library(colleen ${COLLEEN_SOURCES})
target_precompile_headers(colleen
        PRIVATE ${COLLEEN_INCLUDE_DIR}/colleen/common.h
        )