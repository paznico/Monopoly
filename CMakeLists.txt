# Controlla versione usata da CMake
cmake_minimum_required(VERSION 2.8)

# Controllo versione usata C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Imposta nome del progetto
project(Monopoly)

# Imposta la versione del progetto
set(${CMAKE_PROJECT_VERSION} 1.0)

# Imposta percorso di output per l'eseguibile
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# Imposta cartella dove si trovano le librerie
include_directories(include)

# Imposta opzioni di compilazione
# Usa le opzioni di ottimizzazione attivate
add_compile_options(-O2)

# Crea una libreria unica con diversi file sorgente
add_library(player SHARED src/Player.cpp)
add_library(robot SHARED src/Robot.cpp)
add_library(tile SHARED src/tile.hpp)
add_library(gameboard SHARED src/GameBoard.cpp)
add_library(logger SHARED src/Logger.cpp)

# Fa riconoscere il file 'tile.hpp' a CMake come un file di C++
set_target_properties(tile PROPERTIES LINKER_LANGUAGE CXX)

# Crea il file eseguibile
add_executable(${PROJECT_NAME} src/main.cpp)

# Crea link fra libreria e file eseguibile
target_link_libraries(${PROJECT_NAME} player)
target_link_libraries(${PROJECT_NAME} robot)
target_link_libraries(${PROJECT_NAME} tile)
target_link_libraries(${PROJECT_NAME} gameboard)
target_link_libraries(${PROJECT_NAME} logger)
