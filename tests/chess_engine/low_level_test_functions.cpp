/**
 * @file low_level_test_functions.cpp
 * @author Matthew Brown
 * @brief Unit tests for the move generator class.
 */
#include "low_level_test_functions.h"

#include <cstdint>

bool stack_contains(std::stack<int> stack, int value)
{
    while (!stack.empty())
    {
        if (stack.top() == value)
        {
            return true;
        }
        stack.pop();
    }

    return false;
}

bool stack_is_equal(std::vector<int> stack1, const std::stack<int> &stack2)
{
    if (stack1.size() != stack2.size())
    {
        std::cout << "Diff stack sizes are not equal." << std::endl;
        return false;
    }

    int index = static_cast<int>(stack1.size());
    while (!stack1.empty())
    {
        --index;
        if (!stack_contains(stack2, stack1.back()))
        {
            std::cout << "Diff at index " << index << ", value: " << stack1.back() << " is not found." << std::endl;
            return false;
        }
        stack1.pop_back();
    }

    return true;
}

void empty_stack(std::stack<int> *stack)
{
    while (!stack->empty())
    {
        stack->pop();
    }
}

std::string display_stack(std::stack<int> stack)
{
    std::stringstream ss;
    ss << "{";

    const bool was_empty = stack.empty();
    while (!stack.empty())
    {
        ss << stack.top() << ", ";
        stack.pop();
    }

    if (!was_empty)
    {
        ss << "\b";
    }

    ss << "}";

    return ss.str();
}

void print_uint64_t(uint64_t value)
{
    std::stringstream ss;

    for (int i = 64; i > 0; --i)
    {
        if (i % 4 == 0)
        {
            ss << " ";
        }
        if (i % 8 == 0)
        {
            ss << '\n';
        }

        if (value & (1ull << i))
        {
            ss << "1";
        }
        else
        {
            ss << "0";
        }
    }

    std::cout << ss.str() << std::endl;
}

void print_uint64_t_comp(uint64_t value1, uint64_t value2, const std::string &sep)
{
    std::stringstream ss;

    for (int r = 7; r >= 0; --r)
    {
        for (int c = 7; c >= 0; --c)
        {
            if (c % 4 == 3)
            {
                ss << " ";
            }

            if (value1 & (1ull << (r * 8 + c)))
            {
                ss << "1";
            }
            else
            {
                ss << "0";
            }
        }

        ss << sep;

        for (int c = 7; c >= 0; --c)
        {
            if (c % 4 == 3)
            {
                ss << " ";
            }

            if (value2 & (1ull << (r * 8 + c)))
            {
                ss << "1";
            }
            else
            {
                ss << "0";
            }
        }

        ss << "\n";
    }

    std::cout << ss.str() << std::endl;
}
