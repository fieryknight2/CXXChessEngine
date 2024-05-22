/**
 * @file move_generator_test.cpp
 * @author Matthew Brown
 * @brief Unit tests for the move generator class.
 */
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "chess_engine/board/move_generator.h"
#include "gtest/gtest.h"

bool stack_contains(std::stack<int> stack, int value) {
    while (!stack.empty()) {
        if (stack.top() == value) {
            return true;
        }
        stack.pop();
    }

    return false;
}

bool stack_is_equal(std::vector<int> stack1, const std::stack<int>& stack2) {
    if (stack1.size() != stack2.size()) {
        return false;
    }

    while (!stack1.empty()) {
        if (!stack_contains(stack2, stack1.back())) {
            return false;
        }
        stack1.pop_back();
    }

    return true;
}

void empty_stack(std::stack<int> *stack) {
    while (!stack->empty()) {
        stack->pop();
    }
}

std::string display_stack(std::stack<int> stack) {
    std::stringstream ss;
    ss << "{";

    const bool was_empty = stack.empty();
    while (!stack.empty()) {
        ss << stack.top() << ", ";
        stack.pop();
    }

    if (!was_empty) {
        ss << "\b";
    }

    ss << "}";

    return ss.str();
}

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
    EXPECT_TRUE(stack_is_equal(std::vector<int>{}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_pawn_attacks(&attacks, false, 8);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{17}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_pawn_attacks(&attacks, false, 10);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{17, 19}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_pawn_attacks(&attacks, false, 31);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{38}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_pawn_attacks(&attacks, false, 33);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{40, 42}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_pawn_attacks(&attacks, false, 53);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{60, 62}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_pawn_attacks(&attacks, false, 63);
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
    EXPECT_TRUE(stack_is_equal(std::vector<int>{10, 17}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 4);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{10, 14, 19, 21}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 7);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{13, 22}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 9);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{3, 19, 24, 26}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 11);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{1, 5, 17, 21, 26, 2}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 14);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{4, 20, 29, 3}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 18);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{1, 3, 8, 12, 24, 28, 33, 3}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 21);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{4, 6, 11, 15, 27, 31, 36, 3}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 25);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{8, 10, 19, 35, 40, 4}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 30);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{13, 15, 20, 36, 45, 4}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 32);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{17, 26, 42, 4}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 34);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{17, 19, 24, 28, 40, 44, 49, 5}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 39);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{22, 29, 45, 5}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 44);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{27, 29, 34, 38, 50, 54, 59, 6}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 49);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{32, 34, 43, 5}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 54);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{37, 39, 44, 6}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 56);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{41, 5}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 59);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{42, 44, 49, 5}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

    get_knight_attacks(&attacks, 63);
    EXPECT_TRUE(stack_is_equal(std::vector<int>{46, 5}, attacks)) << display_stack(attacks);
    empty_stack(&attacks);

}

// Not necessary to use this, but if I do:
// int main(int argc, char **argv) {
//     testing::InitGoogleTest(&argc, argv);
//
//     return RUN_ALL_TESTS();
// }