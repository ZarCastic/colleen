cmake_minimum_required(VERSION 3.1)
project(Colleen)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/googletest.cmake)
fetch_googletest(
		${PROJECT_SOURCE_DIR}/cmake
		${PROJECT_BINARY_DIR}/googletest
)
set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

enable_testing()
add_subdirectory(test)