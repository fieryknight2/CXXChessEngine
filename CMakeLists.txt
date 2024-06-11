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

add_subdirectory(dependencies)

add_executable(ChessGUI
        # Header files
        source/include/chess_gui/chess_gui.h

        # Source files
        source/src/chess_gui/chess_gui.cpp
        source/src/chess_gui/gui_main.cpp

)

target_include_directories(ChessGUI PUBLIC
        source/include
)

target_link_libraries(ChessGUI
        ChessEngine
        ImGui-SFML::ImGui-SFML
)

if (win32)
    if (BUILD_SHARED_LIBS)
        add_custom_command(TARGET ChessGUI POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
                $<TARGET_FILE:sfml-graphics>
                $<TARGET_FILE:sfml-window>
                $<TARGET_FILE:sfml-system>
                $<TARGET_FILE_DIR:example_exe>)
    endif ()
endif ()


# -------------------------- Chess Engine Run ----------------------------

add_executable(ChessEngineRun
        source/src/main.cpp
)

target_link_libraries(ChessEngineRun ChessEngine)

# -------------------------- Google tests --------------------------------

add_subdirectory(tests)
target_link_libraries(chess_engine_test ChessEngine)

if (MSVC AND WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(chess_engine_test PRIVATE /W4 /WX)
    target_compile_options(chess_engine_test PRIVATE /Od)
    target_compile_options(chess_engine_test PRIVATE /Zi)
    target_link_options(chess_engine_test PRIVATE /DEBUG)
    target_link_options(chess_engine_test PRIVATE /INCREMENTAL)

endif ()