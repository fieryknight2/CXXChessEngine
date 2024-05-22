/**
 * @file move_generator_test.cpp
 * @author Matthew Brown
 * @brief Unit tests for the move generator class.
 */
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
    get_pawn_attacks(&attacks, false, 2);
    EXPECT_EQ(attacks.size(), 0);
    while (!attacks.empty()) attacks.pop();

    get_pawn_attacks(&attacks, false, 8);
    EXPECT_EQ(attacks.size(), 1);
    EXPECT_EQ(attacks.top(), 17);
    while (!attacks.empty()) attacks.pop();

    get_pawn_attacks(&attacks, false, 10);
    EXPECT_EQ(attacks.size(), 2);
    EXPECT_EQ(attacks.top(), 17);
    attacks.pop();
    EXPECT_EQ(attacks.top(), 19);
    while (!attacks.empty()) attacks.pop();

    get_pawn_attacks(&attacks, false, 31);
    EXPECT_EQ(attacks.size(), 1);
    EXPECT_EQ(attacks.top(), 38);
    while (!attacks.empty()) attacks.pop();

    get_pawn_attacks(&attacks, false, 33);
    EXPECT_EQ(attacks.size(), 2);
    EXPECT_EQ(attacks.top(), 40);
    attacks.pop();
    EXPECT_EQ(attacks.top(), 42);
    while (!attacks.empty()) attacks.pop();

    get_pawn_attacks(&attacks, false, 53);
    EXPECT_EQ(attacks.size(), 1);
    EXPECT_EQ(attacks.top(), 60);
    attacks.pop();
    EXPECT_EQ(attacks.top(), 62);
    while (!attacks.empty()) attacks.pop();

    get_pawn_attacks(&attacks, false, 63);
    EXPECT_EQ(attacks.size(), 0);
}
