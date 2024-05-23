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
        std::cout << "Diff stack sizes are not equal." << std::endl;
        return false;
    }

    unsigned int index = stack1.size() - 1;
    while (!stack1.empty()) {
        ++index;
        if (!stack_contains(stack2, stack1.back())) {
            std::cout << "Diff at index " << index << ", value: " << stack1.back() << " is not found." << std::endl;
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

    // Not necessary to use this, but if I do:
    // int main(int argc, char **argv) {
    //     testing::InitGoogleTest(&argc, argv);
    //
    //     return RUN_ALL_TESTS();
// }