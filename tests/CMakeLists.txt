project(GoogleTests)

include(FetchContent)
message(STATUS "Fetching GoogleTests")
FetchContent_Declare(
        googletest
        # Remember to update this url often!
        URL https://github.com/google/googletest/archive/a7f443b80b105f940225332ed3c31f2790092f47.zip
)

# Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(chess_engine_test
        chess_engine/board/perft_test.cpp
        chess_engine/low_level_test_functions.cpp
        chess_engine/board/board_rep_test.cpp
        chess_engine/board/pawn_test.cpp
        chess_engine/board/knight_test.cpp
        chess_engine/board/bishop_test.cpp
        chess_engine/board/rook_test.cpp
        chess_engine/board/queen_test.cpp
        chess_engine/board/king_test.cpp
)
target_include_directories(chess_engine_test PUBLIC
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
        include
        ../source/include
        ../source/src
)
target_link_libraries(chess_engine_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(chess_engine_test)