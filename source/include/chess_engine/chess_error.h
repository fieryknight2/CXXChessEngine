/****************************************************************************
 * MIT License
 * Copyright (c) 2024 Matthew
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * error.h - My custom exception class
 * @author Matthew Brown
 * @date 05/28/2024
 *****************************************************************************/
#pragma once

#include <exception>
#include <string>
#include <utility>

namespace chessengine {

class ChessError final : public std::exception {
public:
    explicit ChessError(std::string message) : m_message(std::move(message)) {}

    [[nodiscard]] const char *what() const noexcept override { return m_message.c_str(); }

private:
    std::string m_message;
};

} // namespace chessengine

/* Assertions */
#ifndef CHESS_ASSERT
#ifndef NDEBUG
#define CHESS_ASSERT(condition, message)                                                                               \
    if (!(condition)) {                                                                                                \
        throw chessengine::ChessError(message);                                                                        \
    }

// #define CHESS_ASSERT(condition) CHESS_ASSERT(condition, "Assertion failed")
#else
#define CHESS_ASSERT(condition, message)
// #define CHESS_ASSERT(condition)
#endif // NDEBUG
#endif // CHESS_ASSERT
