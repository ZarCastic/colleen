cmake_minimum_required(VERSION 3.1)
project(Colleen)

find_package(GTest)
enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)


set(COLLEEN_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(COLLEEN_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/source/colleen.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/source/arguments.cpp"
)
set(COLLEEN_TEST_SOURCES
	${COLLEEN_SOURCES}
	"${CMAKE_CURRENT_LIST_DIR}/test/source/main.cpp"
)

include_directories(${COLLEEN_INCLUDE_DIR})

add_executable(ColleenTest ${COLLEEN_TEST_SOURCES} )
target_link_libraries(ColleenTest gtest)
add_test(ColleenTest ColleenTest)