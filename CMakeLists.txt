cmake_minimum_required(VERSION 3.28)

project(TP6) #Modify this

set (CMAKE_CXX_STANDARD 17) #Set CPP standard

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Tests
include(CTest)
include(GoogleTest)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)

find_package(Doxygen)

if (DOXYGEN_FOUND)
    message(STATUS "Doxygen trouvé. Génération de la cible de documentation 'doxygen_doc'.")

    doxygen_add_docs(
        doxygen_doc
        ALL_SOURCES 
        ${PROJECT_SOURCE_DIR} 
    )
else()
    message(STATUS "Doxygen non trouvé. La cible de documentation ne sera pas créée.")
endif()
