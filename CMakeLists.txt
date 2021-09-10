cmake_minimum_required(VERSION 3.1)
project(colleen)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COLLEEN_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/source)
set(COLLEEN_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

set(COLLEEN_SOURCES
        ${COLLEEN_SOURCE_DIR}/colleen/colleen.cpp
        ${COLLEEN_SOURCE_DIR}/colleen/argument.cpp
        )

add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
        PRIVATE
        ${COLLEEN_SOURCES}
        )
target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${COLLEEN_INCLUDE_DIR}
        )
target_precompile_headers(${PROJECT_NAME}
        PRIVATE ${COLLEEN_INCLUDE_DIR}/colleen/common.h
        )