cmake_minimum_required(VERSION 3.28)
project(ChessEngine)

set(CMAKE_CXX_STANDARD 26)

add_executable(ChessEngine
        source/src/main.cpp
)

target_include_directories(ChessEngine PUBLIC
        source/include
)
