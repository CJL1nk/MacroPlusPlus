cmake_minimum_required(VERSION 3.30)
project(MacroPlusPlus)

set(CMAKE_CXX_STANDARD 20)

add_executable(MacroPlusPlus
        src/main.cpp
        src/main.h
        src/input.cpp
        src/input.h
        src/interpreter.cpp
        src/interpreter.h
        src/record.cpp
        src/record.h
)
