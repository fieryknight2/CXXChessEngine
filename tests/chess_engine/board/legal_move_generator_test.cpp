/**
 * @file move_generator_test.cpp
 * @author Matthew Brown
 * @brief Unit tests for the move generator class.
 */
#include "chess_engine/board/move_generator.h"
#include "gtest/gtest.h"

TEST(LegalMoveGeneratorTest, GenerateLegalMoves) {
 char test_pawn_board[64] = { 0,  0,  1,  0,  0,  0, -1,  0,  # 0-7
                              1,  1,  1,  1,  1,  1,  1, -1,  # 8-15
                              0, -1,  0,  0,  0,  0,  0,  0,  # 16-23
                              0,  0, -1,  0,  0,  0,  0,  1,  # 24-31
                              0,  1,  0,  0,  0,  0, -1,  0,  # 32-39
                              1,  0,  0,  1,  0,  0,  0,  0,  # 40-47
                             -1, -1, -1,  0,  0,  1,  0,  0,  # 48-55
                              0,  0,  0,  0,  0,  0, -1,  1  # 56-63
                             };

 std::stack<int> moves = generate_legal_moves(test_pawn_board, 0);
 ASSERT_EQ(moves.size(), 10);
 for
}
