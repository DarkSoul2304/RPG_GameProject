# 1. Minimalna wymagana wersja programu CMake
cmake_minimum_required(VERSION 3.10)

# 2. Nazwa projektu
project(MyProject)

# 3. Flagi kompilatora wymagane przez prowadzących (niezbędne dla GDB i Valgrinda)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -pedantic")

# 4. Wskazanie folderu z plikami nagłówkowymi (.h)
include_directories(include)

# 5. Utworzenie pliku wykonywalnego o nazwie "program" z podanych plików źródłowych
add_executable(program main.cpp src/rpg_system.cpp)
