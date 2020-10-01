cmake_minimum_required(VERSION 3.5)

project(ChessProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB files "*.h" "*.cpp") # files

add_executable(ChessProject main.cpp ${files}) # linking
