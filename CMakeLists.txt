cmake_minimum_required(VERSION 3.28)

project(TP6) #Modify this

set (CMAKE_CXX_STANDARD 14) #Set CPP standard

set(SOURCE_FILES    src/main.cpp
                    src/Cercle.cpp
                    ) #Add source files here

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

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
