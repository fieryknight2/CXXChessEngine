/**
 * @file move_generator_test.cpp
 * @author Matthew Brown
 * @brief Unit tests for the move generator class.
 */
#include "chess_engine/board/move_generator.h"
#include "gtest/gtest.h"
#include "low_level_test_functions.h"

TEST(LegalMoveGeneratorTest, test_legal_pawn_moves) {
    constexpr int test_pawn_board[64] = { 0,  0, -5,  0,  6,  0, -1,  0,  // 0-7
                                          1,  1,  1,  1, -5,  1,  1, -1,  // 8-15
                                          0, -1,  0,  0, -1,  5, -3,  0,  // 16-23
                                          0,  0, -1,  0,  0,  0,  0,  1,  // 24-31
                                         -3,  1,  5,  0,  5,  0, -1,  3,  // 32-39
                                          1,  0,  0,  0,  0,  0,  0,  0,  // 40-47
                                         -1, -1, -1,  0,  0,  1,  0,  0,  // 48-55
                                          0, -6, -5, -6,  0,  0, -1,  1   // 56-63
                                        };
    std::stack<int> moves;

    legal_pawn_moves(&moves, test_pawn_board, 11, 4);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{}, moves)) << display_stack(moves);
    empty_stack(&moves);

    legal_pawn_moves(&moves, test_pawn_board, 13, 4);
    EXPECT_TRUE(stack_is_equal(std::vector{22}, moves)) << display_stack(moves);
    empty_stack(&moves);

    legal_pawn_moves(&moves, test_pawn_board, 50, 57);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{}, moves)) << display_stack(moves);
}

TEST(LegalMoveGeneratorTest, test_legal_knight_moves) {
    constexpr int test_knight_board[64] = { 0,  0,  0,  0,  0,  3,  0,  0,  // 0-7
                                            0,  0,  0,  0,  0,  0,  0,  0,  // 8-15
                                            0,  3,  5,  6,  0,  3, -5,  0,  // 16-23
                                            0,  0,  0, -3,  0,  0, -3,  0,  // 24-31
                                            0,  3,  0,  0,  0,  3,  0,  0,  // 32-39
                                           -5,  0,  5, -3,  0, -6,  0,  0,  // 40-47
                                            0,  0,  0,  0,  0,  0,  0,  0,  // 48-55
                                            0,  0,  0,  0,  0,  0,  0,  0   // 56-63
                                          };
    std::stack<int> moves;

    legal_knight_moves(&moves, test_knight_board, 5, 19);
    EXPECT_TRUE(stack_is_equal(std::vector{11, 15, 20, 22}, moves)) << display_stack(moves);
    empty_stack(&moves);

    legal_knight_moves(&moves, test_knight_board, 17, 19);
    EXPECT_TRUE(stack_is_equal(std::vector{0, 2, 11, 27, 34, 32}, moves)) << display_stack(moves);
    empty_stack(&moves);

    legal_knight_moves(&moves, test_knight_board, 21, 19);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{}, moves)) << display_stack(moves);
    empty_stack(&moves);

    legal_knight_moves(&moves, test_knight_board, 33, 19);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{}, moves)) << display_stack(moves);
    empty_stack(&moves);

    legal_knight_moves(&moves, test_knight_board, 37, 19);
    EXPECT_TRUE(stack_is_equal(std::vector{20, 22, 27, 43, 52, 54, 31, 47}, moves)) << display_stack(moves);
    empty_stack(&moves);

    legal_knight_moves(&moves, test_knight_board, 27, 45);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{}, moves)) << display_stack(moves);
    empty_stack(&moves);

    legal_knight_moves(&moves, test_knight_board, 30, 45);
    EXPECT_TRUE(stack_is_equal(std::vector{15, 13, 20, 36, 47}, moves)) << display_stack(moves);
    empty_stack(&moves);

    legal_knight_moves(&moves, test_knight_board, 43, 45);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{}, moves)) << display_stack(moves);
    empty_stack(&moves);
}