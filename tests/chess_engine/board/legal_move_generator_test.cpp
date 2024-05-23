/**
 * @file move_generator_test.cpp
 * @author Matthew Brown
 * @brief Unit tests for the move generator class.
 */
#include "chess_engine/board/move_generator.h"
#include "gtest/gtest.h"
#include "low_level_test_functions.h"

TEST(LegalMoveGeneratorTest, test_legal_pawn_moves) {
    int test_pawn_board[64] = { 0,  0, -5,  0,  6,  0, -1,  0,  // 0-7
                                1,  1,  1,  1, -5,  1,  1, -1,  // 8-15
                                0, -1,  0,  0, -1,  5, -3,  0,  // 16-23
                                0,  0, -1,  0,  0,  0,  0,  1,  // 24-31
                               -3,  1,  5,  0,  0,  0, -1,  3,  // 32-39
                                1,  0,  0,  1,  0,  0,  0,  0,  // 40-47
                               -1, -1, -1,  0,  0,  1,  0,  0,  // 48-55
                                0,  0, -5,  0,  0,  0, -1,  1   // 56-63
                              };
    std::stack<int> moves;

    legal_pawn_moves(&moves, test_pawn_board, 11, 4);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{}, moves)) << display_stack(moves);
    empty_stack(&moves);

    legal_pawn_moves(&moves, test_pawn_board, 13, 4);
    EXPECT_TRUE(stack_is_equal(std::vector{22}, moves)) << display_stack(moves);
    empty_stack(&moves);
}