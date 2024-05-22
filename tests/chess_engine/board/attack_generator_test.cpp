/**
* @file move_generator_test.cpp
 * @author Matthew Brown
 * @brief Unit tests for the move generator class.
 */
#include "chess_engine/board/move_generator.h"
#include "gtest/gtest.h"

TEST(AttackGeneratorTest, get_pawn_attacks) {
 // Purely for visual aid
 //  0,  0,  1,  0,  0,  0, -1,  0,  // 0-7
 //  1,  1,  1,  1,  1,  1,  1, -1,  // 8-15
 //  0, -1,  0,  0,  0,  0,  0,  0,  // 16-23
 //  0,  0, -1,  0,  0,  0,  0,  1,  // 24-31
 //  0,  1,  0,  0,  0,  0, -1,  0,  // 32-39
 //  1,  0,  0,  1,  0,  0,  0,  0,  // 40-47
 //  1, -1, -1,  0,  0,  1,  0,  0,  // 48-55
 //  0,  0,  0,  0,  0,  0, -1,  1   // 56-63

 // Verify that the pawn attacks the correct squares
 std::stack<int> attacks = get_pawn_attacks(2);
 ASSERT_EQ(attacks.size(), 0);

 attacks = get_pawn_attacks(8);
 ASSERT_EQ(attacks.size(), 1);
 ASSERT_EQ(attacks.top(), 17);

 attacks = get_pawn_attacks(10);
 ASSERT_EQ(attacks.size(), 2);
 ASSERT_EQ(attacks.top(), 17);
 attacks.pop();
 ASSERT_EQ(attacks.top(), 19);

 attacks = get_pawn_attacks(31);
 ASSERT_EQ(attacks.size(), 1);
 ASSERT_EQ(attacks.top(), 38);

 attacks = get_pawn_attacks(33);
 ASSERT_EQ(attacks.size(), 2);
 ASSERT_EQ(attacks.top(), 40);
 attacks.pop();
 ASSERT_EQ(attacks.top(), 42);

 attacks = get_pawn_attacks(53);
 ASSERT_EQ(attacks.size(), 1);
 ASSERT_EQ(attacks.top(), 60);
 attacks.pop();
 ASSERT_EQ(attacks.top(), 62);

 attacks = get_pawn_attacks(63);
 ASSERT_EQ(attacks.size(), 0);
}