# Controlla versione usata da CMake
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# Controllo versione usata C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Imposta nome del progetto
project(Monopoly VERSION 1.0)

# Imposta percorso di output per l'eseguibile
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# Imposta cartella dove si trovano le librerie
include_directories(include)

# Imposta opzioni di compilazione
# Usa le opzioni di ottimizzazione attivate
add_compile_options(-O2)

# Crea una libreria unica con diversi file sorgente
add_library(${PROJECT_NAME} SHARED src/Player.cpp src/Robot.cpp src/Tile.hpp src/GameBoard.cpp src/Logger.cpp)

# Crea il file eseguibile
add_executable(monopoly src/main.cpp)

# Crea link fra libreria e file eseguibile
target_link_libraries(monopoly ${PROJECT_NAME})
