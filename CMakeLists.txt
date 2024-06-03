cmake_minimum_required(VERSION 3.25)
project(ChessEngine)

set(CMAKE_CXX_STANDARD 26)

add_library(ChessBoard STATIC
        # Header files
        source/include/chess_engine/board/chess_board.h
        source/include/chess_engine/board/piece.h
        source/include/chess_engine/board/pawn.h
        source/include/chess_engine/board/knight.h
        source/include/chess_engine/board/bishop.h
        source/include/chess_engine/board/rook.h
        source/include/chess_engine/board/queen.h
        source/include/chess_engine/board/king.h
        source/include/chess_engine/board/bitboard.h
        source/include/chess_engine/chess_game.h

        # Source files
        source/src/chess_engine/board/chess_board.cpp
        source/src/chess_engine/board/pawn.cpp
        source/src/chess_engine/board/knight.cpp
        source/src/chess_engine/board/bishop.cpp
        source/src/chess_engine/board/rook.cpp
        source/src/chess_engine/board/queen.cpp
        source/src/chess_engine/board/king.cpp
        source/src/chess_engine/board/bitboard.cpp
        source/src/chess_engine/chess_game.cpp
)

target_include_directories(ChessBoard PUBLIC
        source/include
)

add_library(ChessEngine STATIC
        # Header files
        source/include/chess_engine/chess_engine.h
        source/include/chess_engine/chess_error.h

        # Source files
        source/src/chess_engine/chess_engine.cpp
)

target_include_directories(ChessEngine PUBLIC
        source/include
)

target_link_libraries(ChessEngine ChessBoard)

add_executable(ChessEngineRun
        source/src/main.cpp
)

target_link_libraries(ChessEngineRun ChessEngine)

add_subdirectory(tests)
target_link_libraries(chess_engine_test ChessEngine)