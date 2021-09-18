cmake_minimum_required(VERSION 3.18)
set(COLLEEN_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

include(${COLLEEN_ROOT_DIR}/CMakeLists.txt)
conan_basic_setup(gtest gmock)
enable_testing()

set(COLLEEN_TEST_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(COLLEEN_TEST_INCLUDE_DIR ${COLLEEN_TEST_ROOT_DIR}/include)
set(COLLEEN_TEST_SOURCE_DIR ${COLLEEN_TEST_ROOT_DIR}/source)

project(colleen-test)
add_executable(${PROJECT_NAME})
file(GLOB_RECURSE COLLEEN_TEST_SOURCES ${COLLEEN_TEST_SOURCE_DIR}/*.cpp)
target_sources(${PROJECT_NAME}
        PRIVATE
        ${COLLEEN_TEST_SOURCES}
        )
target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${COLLEEN_TEST_INCLUDE_DIR}
        ${CONAN_INCLUDE_DIRS}
        )
target_compile_options(${PROJECT_NAME}
        PRIVATE
        -Wall
        -Werror
        )
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        colleen
        gtest
        pthread
        )

set(TEST_OPTIONS ${COLLEEN_TEST_ROOT_DIR}/configuration/test_options.json)
target_add_colleen_config(${PROJECT_NAME} ${TEST_OPTIONS})

