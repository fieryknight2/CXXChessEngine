/**
 * @file move_generator_test.cpp
 * @author Matthew Brown
 * @brief Unit tests for the move generator class.
 */
#include "low_level_test_functions.h"
#include "chess_engine/board/move_generator.h"
#include "gtest/gtest.h"

TEST(AttackGeneratorTest, get_pawn_attacks) {
    //  0,  0,  1,  0,  0,  0, -1,  0,  // 0-7
    //  1,  1,  1,  1,  1,  1,  1, -1,  // 8-15
    //  0, -1,  0,  0,  0,  0,  0,  0,  // 16-23
    //  0,  0, -1,  0,  0,  0,  0,  1,  // 24-31
    //  0,  1,  0,  0,  0,  0, -1,  0,  // 32-39
    //  1,  0,  0,  1,  0,  0,  0,  0,  // 40-47
    //  1, -1, -1,  0,  0,  1,  0,  0,  // 48-55
    //  0,  0,  0,  0,  0,  0, -1,  1   // 56-63

    // Verify that the pawn attacks the correct squares
    std::stack<int> attacks;
    get_pawn_attacks(&attacks, true, 2);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_pawn_attacks(&attacks, true, 8);
    EXPECT_TRUE(stack_is_equal(std::vector{17}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_pawn_attacks(&attacks, true, 10);
    EXPECT_TRUE(stack_is_equal(std::vector{17, 19}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_pawn_attacks(&attacks, true, 31);
    EXPECT_TRUE(stack_is_equal(std::vector{38}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_pawn_attacks(&attacks, true, 33);
    EXPECT_TRUE(stack_is_equal(std::vector{40, 42}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_pawn_attacks(&attacks, true, 53);
    EXPECT_TRUE(stack_is_equal(std::vector{60, 62}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_pawn_attacks(&attacks, true, 63);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    // Other color
    get_pawn_attacks(&attacks, false, 6) ;
    EXPECT_TRUE(stack_is_equal(std::vector<int>{}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_pawn_attacks(&attacks, false, 15);
     EXPECT_TRUE(stack_is_equal(std::vector<int>{6}, attacks)) << display_stack(attacks);
     empty_stack(&attacks);

    get_pawn_attacks(&attacks, false, 17);
     EXPECT_TRUE(stack_is_equal(std::vector<int>{8, 10}, attacks)) << display_stack(attacks);
     empty_stack(&attacks);

    get_pawn_attacks(&attacks, false, 26);
     EXPECT_TRUE(stack_is_equal(std::vector<int>{17, 19}, attacks)) << display_stack(attacks);
     empty_stack(&attacks);

    get_pawn_attacks(&attacks, false, 38);
     EXPECT_TRUE(stack_is_equal(std::vector<int>{29, 31}, attacks)) << display_stack(attacks);
     empty_stack(&attacks);

    get_pawn_attacks(&attacks, false, 48);
     EXPECT_TRUE(stack_is_equal(std::vector<int>{41}, attacks)) << display_stack(attacks);
     empty_stack(&attacks);

    get_pawn_attacks(&attacks, false, 62);
     EXPECT_TRUE(stack_is_equal(std::vector<int>{}, attacks)) << display_stack(attacks);
}

TEST(AttackGeneratorTest, get_knight_attacks) {
    //  2,  0,  0,  0,  2,  0,  0,  2,  # 0-7
    //  0,  2,  0, -2,  0,  0, -2,  0,  # 8-15
    //  0,  0, -2,  0,  0,  2,  0,  0,  # 16-23
    //  0,  2,  0,  0,  0,  0,  2,  0,  # 24-31
    //  2,  0, -2,  0,  0,  0,  0,  2,  # 32-39
    //  0,  0,  0,  0,  2,  0,  0,  0,  # 40-47
    //  0, -2,  0,  0,  0,  0,  2,  0,  # 48-55
    //  2,  0,  0,  2,  0,  0,  0,  2   # 56-63

    std::stack<int> attacks;

    get_knight_attacks(&attacks, 0);
    EXPECT_TRUE(stack_is_equal(std::vector{10, 17}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 4);
    EXPECT_TRUE(stack_is_equal(std::vector{10, 14, 19, 21}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 7);
    EXPECT_TRUE(stack_is_equal(std::vector{13, 22}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 9);
    EXPECT_TRUE(stack_is_equal(std::vector{3, 19, 24, 26}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 11);
    EXPECT_TRUE(stack_is_equal(std::vector{1, 5, 17, 21, 26, 28}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 14);
    EXPECT_TRUE(stack_is_equal(std::vector{4, 20, 29, 31}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 18);
    EXPECT_TRUE(stack_is_equal(std::vector{1, 3, 8, 12, 24, 28, 33, 35}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 21);
    EXPECT_TRUE(stack_is_equal(std::vector{4, 6, 11, 15, 27, 31, 36, 38}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 25);
    EXPECT_TRUE(stack_is_equal(std::vector{8, 10, 19, 35, 40, 42}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 30);
    EXPECT_TRUE(stack_is_equal(std::vector{13, 15, 20, 36, 45, 47}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 32);
    EXPECT_TRUE(stack_is_equal(std::vector{17, 26, 42, 49}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 34);
    EXPECT_TRUE(stack_is_equal(std::vector{17, 19, 24, 28, 40, 44, 49, 51}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 39);
    EXPECT_TRUE(stack_is_equal(std::vector{22, 29, 45, 54}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 44);
    EXPECT_TRUE(stack_is_equal(std::vector{27, 29, 34, 38, 50, 54, 59, 61}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 49);
    EXPECT_TRUE(stack_is_equal(std::vector{32, 34, 43, 59}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 54);
    EXPECT_TRUE(stack_is_equal(std::vector{37, 39, 44, 60}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 56);
    EXPECT_TRUE(stack_is_equal(std::vector{41, 50}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 59);
    EXPECT_TRUE(stack_is_equal(std::vector{42, 44, 49, 53}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 63);
    EXPECT_TRUE(stack_is_equal(std::vector{46, 53}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);
}

TEST(AttackGeneratorTest, get_bishop_attacks) {
    int bishop_board[64] = {3,  0,  3,  0,  3,  0,  0,  3,  // 0-7
                            0,  3,  0, -3,  0,  0, -3,  0,  // 8-15
                            3,  0, -3,  0,  0,  3,  0,  3,  // 16-23
                            0,  3,  0,  0,  0,  0,  3,  0,  // 24-31
                            3,  0, -3,  0,  0,  0,  0,  3,  // 32-39
                            0,  0,  0,  0,  3,  0,  0,  0,  // 40-47
                            0, -3,  0,  0,  0,  0,  3,  0,  // 48-55
                            3,  0,  0,  3,  0,  0,  0,  3   // 56-63
                            };
    std::stack<int> attacks;

    get_bishop_attacks(&attacks, bishop_board, 0);
    EXPECT_TRUE(stack_is_equal(std::vector{9}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 2);
    EXPECT_TRUE(stack_is_equal(std::vector{9, 11}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 4);
    EXPECT_TRUE(stack_is_equal(std::vector{11, 13, 22, 31}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 7);
    EXPECT_TRUE(stack_is_equal(std::vector{14}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 9);
    EXPECT_TRUE(stack_is_equal(std::vector{0, 2, 16, 18}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 11);
    EXPECT_TRUE(stack_is_equal(std::vector{2, 4, 18, 20, 29, 38, 47}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 14);
    EXPECT_TRUE(stack_is_equal(std::vector{5, 7, 21, 23}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 16);
    EXPECT_TRUE(stack_is_equal(std::vector{9, 25}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 18);
    EXPECT_TRUE(stack_is_equal(std::vector{9, 11, 25, 27, 36, 45, 54}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 21);
    EXPECT_TRUE(stack_is_equal(std::vector{12, 3, 14, 28, 35, 42, 49, 30}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 23);
    EXPECT_TRUE(stack_is_equal(std::vector{14, 30}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 25);
    EXPECT_TRUE(stack_is_equal(std::vector{16, 18, 32, 34}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 30);
    EXPECT_TRUE(stack_is_equal(std::vector{21, 23, 37, 44, 39}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 32);
    EXPECT_TRUE(stack_is_equal(std::vector{25, 41, 50, 59}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 34);
    EXPECT_TRUE(stack_is_equal(std::vector{25, 27, 20, 13, 6, 41, 48, 43, 52, 61}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 39);
    EXPECT_TRUE(stack_is_equal(std::vector{30, 46, 53, 60}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 44);
    EXPECT_TRUE(stack_is_equal(std::vector{35, 26, 17, 8, 37, 30, 51, 58, 53, 62}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 49);
    EXPECT_TRUE(stack_is_equal(std::vector{40, 42, 35, 28, 21, 56, 58}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 54);
    EXPECT_TRUE(stack_is_equal(std::vector{45, 36, 27, 18, 47, 61, 63}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 56);
    EXPECT_TRUE(stack_is_equal(std::vector{49}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 59);
    EXPECT_TRUE(stack_is_equal(std::vector{50, 41, 52, 45, 38, 31, 32}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_bishop_attacks(&attacks, bishop_board, 63);
    EXPECT_TRUE(stack_is_equal(std::vector{54}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);
}

TEST(AttackGeneratorTest, get_rook_attacks) {
    constexpr int rook_board[64] = { 4,  0,  0,  0,  4,  0,  0,  4,  // 0-7
                                     0,  0,  0,  0,  0,  0,  0,  0,  // 8-15
                                     0,  0,  0,  0,  0,  0,  0,  0,  // 16-23
                                     0,  4,  0,  0,  0,  0,  0, -4,  // 24-31
                                     0,  0,  0,  0,  0,  0,  0,  0,  // 32-39
                                     0,  4,  0,  0,  4,  0,  0,  0,  // 40-47
                                    -4,  0,  0,  0,  0,  0,  0,  0,  // 48-55
                                     4,  0,  0,  0,  0,  0,  0,  4   // 56-63
                                   };
    std::stack<int> attacks;

    get_rook_attacks(&attacks, rook_board, 0);
    EXPECT_TRUE(stack_is_equal(std::vector{1, 2, 3, 4, 8, 16, 24, 32, 40, 48}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_rook_attacks(&attacks, rook_board, 4);
    EXPECT_TRUE(stack_is_equal(std::vector{3, 2, 1, 0, 5, 6, 7, 12, 20, 28, 36, 44}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_rook_attacks(&attacks, rook_board, 7);
    EXPECT_TRUE(stack_is_equal(std::vector{6, 5, 4, 15, 23, 31}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_rook_attacks(&attacks, rook_board, 25);
    EXPECT_TRUE(stack_is_equal(std::vector{17, 9, 1, 24, 26, 27, 28, 29, 30, 31, 33, 41}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_rook_attacks(&attacks, rook_board, 31);
    EXPECT_TRUE(stack_is_equal(std::vector{23, 15, 7, 30, 29, 28, 27, 26, 25, 39, 47, 55, 63}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_rook_attacks(&attacks, rook_board, 41);
    EXPECT_TRUE(stack_is_equal(std::vector{33, 25, 40, 42, 43, 44, 49, 57}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_rook_attacks(&attacks, rook_board, 44);
    EXPECT_TRUE(stack_is_equal(std::vector{36, 28, 20, 12, 4, 43, 42, 41, 45, 46, 47, 52, 60}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_rook_attacks(&attacks, rook_board, 48);
    EXPECT_TRUE(stack_is_equal(std::vector{40, 32, 24, 16, 8, 0, 49, 50, 51, 52, 53, 54, 55, 56}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_rook_attacks(&attacks, rook_board, 56);
    EXPECT_TRUE(stack_is_equal(std::vector{48, 57, 58, 59, 60, 61, 62, 63}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_rook_attacks(&attacks, rook_board, 63);
    EXPECT_TRUE(stack_is_equal(std::vector{55, 47, 39, 31, 62, 61, 60, 59, 58, 57, 56}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);
}

TEST(AttackGeneratorTest, get_queen_attacks) {
    constexpr int queen_board[64] = { 5,  0,  0,  0,  5,  0,  0,  5,  // 0-7
                                      0,  0,  0,  0,  0,  0,  0,  0,  // 8-15
                                      0,  0,  0,  0,  0,  0,  0,  0,  // 16-23
                                      0,  5,  0,  5,  0,  0,  0, -5,  // 24-31
                                      0,  0,  0,  0,  0,  0,  0,  0,  // 32-39
                                      0,  5,  0,  0,  5,  0,  0,  0,  // 40-47
                                     -5,  0,  0,  0,  0,  0,  0,  0,  // 48-55
                                      5,  0,  0,  0,  0,  0,  0,  5   // 56-63
                                    };
    std::stack<int> attacks;

    get_queen_attacks(&attacks, queen_board, 0);
    EXPECT_TRUE(stack_is_equal(std::vector{1, 2, 3, 4, 8, 16, 24, 32, 40, 48,
        9, 18, 27}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_queen_attacks(&attacks, queen_board, 4);
    EXPECT_TRUE(stack_is_equal(std::vector{3, 2, 1, 0, 5, 6, 7, 11, 18, 25, 12,
        20, 28, 36, 44, 13, 22, 31}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_queen_attacks(&attacks, queen_board, 7);
    EXPECT_TRUE(stack_is_equal(std::vector{6, 5, 4, 14, 21, 28, 35, 42, 49,
        56, 15, 23, 31}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_queen_attacks(&attacks, queen_board, 25);
    EXPECT_TRUE(stack_is_equal(std::vector{16, 17, 9, 1, 18, 11, 4, 24, 26, 27,
        32, 33, 41, 34, 43, 52, 61}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_queen_attacks(&attacks, queen_board, 27);
    EXPECT_TRUE(stack_is_equal(std::vector{18, 9, 0, 19, 11, 3, 20, 13, 6, 26, 25,
        28, 29, 30, 31, 34, 41, 35, 43, 51, 59, 36, 45, 54, 63}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_queen_attacks(&attacks, queen_board, 31);
    EXPECT_TRUE(stack_is_equal(std::vector{22, 13, 4, 23, 15, 7, 30, 29, 28,
        27, 38, 45, 52, 59, 39, 47, 55, 63}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_queen_attacks(&attacks, queen_board, 41);
    EXPECT_TRUE(stack_is_equal(std::vector{32, 33, 25, 34, 27, 40, 42, 43,
        44, 48, 49, 57, 50, 59}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_queen_attacks(&attacks, queen_board, 44);
    EXPECT_TRUE(stack_is_equal(std::vector{35, 26, 17, 8, 36, 28, 20, 12, 4,
        37, 30, 23, 43, 42, 41, 45, 46, 47, 51, 58, 52, 60, 53, 62}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_queen_attacks(&attacks, queen_board, 48);
    EXPECT_TRUE(stack_is_equal(std::vector{40, 32, 24, 16, 8, 0, 41, 49,
        50, 51, 52, 53, 54, 55, 56, 57}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_queen_attacks(&attacks, queen_board, 56);
    EXPECT_TRUE(stack_is_equal(std::vector{48, 49, 42, 35, 28, 21, 14, 7,
        57, 58, 59, 60, 61, 62, 63}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_queen_attacks(&attacks, queen_board, 63);
    EXPECT_TRUE(stack_is_equal(std::vector{54, 45, 36, 27, 55, 47, 39, 31,
        62, 61, 60, 59, 58, 57, 56}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);
}

TEST(AttackGeneratorTest, get_king_attacks) {
    // Purely for visual reference:
    //  6,  0,  0,  6, -6,  0,  0,  6,  -  0-7
    // -6,  0,  0,  0, -6,  0,  0,  0,  -  8-15
    //  0,  0,  0,  0,  0,  0,  0,  0,  -  16-23
    //  0,  0,  0, -6,  0,  0,  0,  0,  -  24-31
    //  0,  0,  0,  0,  6,  0, -6,  6,  -  32-39
    // -6,  0,  0,  6, -6,  6,  0,  6,  -  40-47
    //  0, -6,  0,  0,  0,  0,  6,  0,  -  48-55
    // -6,  6,  0,  0,  0,  0, -6,  6   -  56-63
    std::stack<int> attacks;

    get_king_attacks(&attacks, 0) ;
    EXPECT_TRUE(stack_is_equal(std::vector{1, 8, 9}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_king_attacks(&attacks, 3) ;
    EXPECT_TRUE(stack_is_equal(std::vector{2, 4, 10, 11, 12}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_king_attacks(&attacks, 7) ;
    EXPECT_TRUE(stack_is_equal(std::vector{6, 14, 15}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_king_attacks(&attacks, 8) ;
    EXPECT_TRUE(stack_is_equal(std::vector{0, 1, 9, 16, 17}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_king_attacks(&attacks, 12);
    EXPECT_TRUE(stack_is_equal(std::vector{3, 4, 5, 11, 13, 19, 20, 21}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_king_attacks(&attacks, 27);
    EXPECT_TRUE(stack_is_equal(std::vector{18, 19, 20, 26, 28, 34, 35, 36}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_king_attacks(&attacks, 36);
    EXPECT_TRUE(stack_is_equal(std::vector{27, 28, 29, 35, 37, 43, 44, 45}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_king_attacks(&attacks, 38);
    EXPECT_TRUE(stack_is_equal(std::vector{29, 30, 31, 37, 39, 45, 46, 47}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_king_attacks(&attacks, 39);
    EXPECT_TRUE(stack_is_equal(std::vector{30, 31, 38, 46, 47}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_king_attacks(&attacks, 40);
    EXPECT_TRUE(stack_is_equal(std::vector{32, 33, 41, 48, 49}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_king_attacks(&attacks, 43);
    EXPECT_TRUE(stack_is_equal(std::vector{34, 35, 36, 42, 44, 50, 51, 52}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_king_attacks(&attacks, 44);
    EXPECT_TRUE(stack_is_equal(std::vector{35, 36, 37, 43, 45, 51, 52, 53}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_king_attacks(&attacks, 45);
    EXPECT_TRUE(stack_is_equal(std::vector{36, 37, 38, 44, 46, 52, 53, 54}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_king_attacks(&attacks, 47);
    EXPECT_TRUE(stack_is_equal(std::vector{38, 39, 46, 54, 55}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_king_attacks(&attacks, 49);
    EXPECT_TRUE(stack_is_equal(std::vector{40, 41, 42, 48, 50, 56, 57, 58}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_king_attacks(&attacks, 54);
    EXPECT_TRUE(stack_is_equal(std::vector{45, 46, 47, 53, 55, 61, 62, 63}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_king_attacks(&attacks, 56);
    EXPECT_TRUE(stack_is_equal(std::vector{48, 49, 57}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_king_attacks(&attacks, 57);
    EXPECT_TRUE(stack_is_equal(std::vector{48, 49, 50, 56, 58}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_king_attacks(&attacks, 62);
    EXPECT_TRUE(stack_is_equal(std::vector{53, 54, 55, 61, 63}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_king_attacks(&attacks, 63);
    EXPECT_TRUE(stack_is_equal(std::vector{54, 55, 62}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);
}


// Not necessary to use this, but if I do:
// int main(int argc, char **argv) {
//     testing::InitGoogleTest(&argc, argv);
//
//     return RUN_ALL_TESTS();
// }