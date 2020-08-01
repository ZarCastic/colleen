set(SOURCES 
  ../source/arguments.cpp
  ../source/colleen.cpp
)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions("-Wall -Werror -Wno-unknown-pragmas")

set(TEST_SOURCES source/main_tests.cpp
        source/colleen_test.cpp)
add_executable(unit_tests ${SOURCES} ${TEST_SOURCES})
target_link_libraries(unit_tests gtest_main )

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )
