cmake_minimum_required(VERSION 3.18)
set(COLLEEN_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

include(${COLLEEN_ROOT_DIR}/CMakeLists.txt)
conan_basic_setup(gtest gmock)
enable_testing()

set(COLLEEN_TEST_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(COLLEEN_TEST_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/source)

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
        )

