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
        chess_engine/board/legal_move_generator_test.cpp
        chess_engine/board/attack_generator_test.cpp
        chess_engine/board/move_generator_test.cpp
)
target_include_directories(chess_engine_test PUBLIC
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
        ../source/include
        ../source/src
)
target_link_libraries(chess_engine_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(chess_engine_test)