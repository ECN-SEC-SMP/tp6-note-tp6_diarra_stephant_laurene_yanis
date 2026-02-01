include_directories(${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)

set(TEST_FILES
                  test_controleur.cpp
                  tests_bot.cpp
                    ) #Add source files here

add_executable(unit_tests ${TEST_FILES}
../src/Controleur.cpp
../src/Joueur.cpp
../src/Coup.cpp
../src/Plateau.cpp
../src/Case.cpp
../src/Cercle.cpp
../src/Bot.cpp
)
target_link_libraries(
  unit_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
