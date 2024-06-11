cmake_minimum_required(VERSION 3.25)
project(ChessEngine)

set(CMAKE_CXX_STANDARD 26)

# -------------------------- ChessBoard library --------------------------

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
        source/src/chess_engine/board/white_pawn.cpp
        source/src/chess_engine/board/knight.cpp
        source/src/chess_engine/board/bishop.cpp
        source/src/chess_engine/board/rook.cpp
        source/src/chess_engine/board/queen.cpp
        source/src/chess_engine/board/king.cpp
        source/src/chess_engine/board/bitboard.cpp
        source/src/chess_engine/chess_game.cpp
        source/src/chess_engine/board/black_pawn.cpp
)

target_include_directories(ChessBoard PUBLIC
        source/include
)

# -------------------------- Chess Engine library ------------------------

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

# -------------------------- Chess GUI library ---------------------------

add_executable(ChessGUI
		# Header files

		# Source files
		source/src/chess_gui/chess_gui.cpp

)

target_include_directories(ChessGUI PUBLIC
		source/include
)

target_link_libraries(ChessGUI ChessEngine)


if (WIN32)
    target_link_libraries(ChessGUI ${CMAKE_SOURCE_DIR}/win_libs/SDL2-2.30.3/lib/x64/SDL2main.lib)
    target_link_libraries(ChessGUI ${CMAKE_SOURCE_DIR}/win_libs/SDL2-2.30.3/lib/x64/SDL2.lib)

    configure_file(${CMAKE_SOURCE_DIR}/win_libs/SDL2-2.30.3/lib/x64/SDL2.dll ${CMAKE_BINARY_DIR}/SDL2.dll)

    target_include_directories(ChessGUI PUBLIC ${CMAKE_SOURCE_DIR}/win_libs/SDL2-2.30.3/include)
endif(WIN32)

if (UNIX AND NOT APPLE)
    find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)

	target_link_libraries(ChessGUI
        SDL2::SDL2main
		SDL2
	)

    target_include_directiores(ChessGUI PUBLIC
		${SDL2_INCLUDE_DIRS}
    )

endif(UNIX AND NOT APPLE)

if (APPLE)

 # If anybody knows how to do this go ahead.

endif(APPLE)

# -------------------------- Chess Engine Run ----------------------------

add_executable(ChessEngineRun
        source/src/main.cpp
)

target_link_libraries(ChessEngineRun ChessEngine)

# -------------------------- Google tests --------------------------------

add_subdirectory(tests)
target_link_libraries(chess_engine_test ChessEngine)