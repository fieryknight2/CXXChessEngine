cmake_minimum_required(VERSION 3.28)
project(ChessEngine)

set(CMAKE_CXX_STANDARD 26)

add_executable(ChessEngine
        source/src/main.cpp
        source/src/chess_engine/board/legal_move_generator.cpp
        source/include/chess_engine/constants.h
        source/include/chess_engine/board/move_generator.h
        source/src/chess_engine/board/attack_generator.cpp
        source/src/chess_engine/board/move_generator.cpp
)

target_include_directories(ChessEngine PUBLIC
        source/include
)

add_subdirectory(tests)