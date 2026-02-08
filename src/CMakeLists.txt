set(SOURCE_FILES    main.cpp
                    Joueur.cpp
                    Case.cpp
                    Bot.cpp
                    Cercle.cpp
                    Plateau.cpp
                    JoueurHumain.cpp
                    Controleur.cpp
                    Coup.cpp
                    ) #Add source files here

include_directories(${CMAKE_SOURCE_DIR}/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
