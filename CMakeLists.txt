# Controlla versione usata da CMake
cmake_minimum_required(VERSION 3.8)

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
# Usa le opzioni di ottimizzazione
if(CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_options(/O2)
endif()

# Crea una libreria unica con diversi file sorgente
add_library(logger STATIC src/Logger.cpp)
add_library(player STATIC src/Player.cpp)
add_library(robot STATIC src/Robot.cpp)
add_library(gameboard STATIC src/GameBoard.cpp)

# Crea il file eseguibile
add_executable(${PROJECT_NAME} src/main.cpp)

# Crea link fra libreria e file eseguibile
target_link_libraries(${PROJECT_NAME} player robot gameboard logger)
