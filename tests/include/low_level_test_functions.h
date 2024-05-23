/**
 * @file low_level_test_functions.h
 * @author Matthew Brown
 * @brief Unit tests for the move generator class.
 */
#ifndef LOW_LEVEL_TEST_FUNCTIONS_H
#define LOW_LEVEL_TEST_FUNCTIONS_H

#include <vector>
#include <stack>
#include <iostream>
#include <sstream>
#include <string>

bool stack_contains(std::stack<int> stack, int value);
bool stack_is_equal(std::vector<int> stack1, const std::stack<int>& stack2);
void empty_stack(std::stack<int> *stack);
std::string display_stack(std::stack<int> stack);

#endif //LOW_LEVEL_TEST_FUNCTIONS_H
