set(SOURCE_FILES    main.cpp
                    Joueur.cpp
                    Case.cpp
                    Cercle.cpp
                    Plateau.cpp
                    ) #Add source files here

include_directories(${CMAKE_SOURCE_DIR}/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
