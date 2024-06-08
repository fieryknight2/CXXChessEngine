project(GoogleTests)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Remember to update this url often!
        URL https://github.com/google/googletest/archive/9b4993ca7d1279dec5c5d41ba327cb11a77bdc00.zip
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

if (MSVC AND WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_options(chess_engine_test PRIVATE /W4 /WX)
	target_compile_options(chess_engine_test PRIVATE /Od)
	target_compile_options(chess_engine_test PRIVATE /Zi)
	target_link_options(chess_engine_test PRIVATE /DEBUG)
    target_link_options(chess_engine_test PRIVATE /INCREMENTAL)

endif()

include(GoogleTest)
gtest_discover_tests(chess_engine_test)