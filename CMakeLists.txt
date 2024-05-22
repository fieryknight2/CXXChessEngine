cmake_minimum_required(VERSION 3.28)
project(ChessEngine)

set(CMAKE_CXX_STANDARD 26)

add_library(ChessEngine
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

add_executable(ChessEngineRun
        source/src/main.cpp
)

target_link_libraries(ChessEngineRun ChessEngine)

add_subdirectory(tests)
target_link_libraries(tests ChessEngine)