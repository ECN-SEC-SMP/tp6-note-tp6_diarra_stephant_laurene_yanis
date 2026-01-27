include_directories(${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)

set(TEST_FILES    it_works.cpp
                    ) #Add source files here

add_executable(unit_tests ${TEST_FILES})
target_link_libraries(
  unit_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
