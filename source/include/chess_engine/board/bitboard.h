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
 * bitboard.h - <Brief description>
 * @author Matthew Brown
 * @date 05/28/2024
 *****************************************************************************/
#ifndef bitboard_H
#define bitboard_H

#include <cstdint>

/** Classic bitboard.
 *
 * One 64-bit integer representing boolean conditions for chess board
 * @author Matthew Brown
 * @date 5/28/2024
 */
struct Bitboard
{
    /** Constructors */
    explicit Bitboard(uint64_t nvalue) : value(nvalue) {}
    Bitboard() : value(0) {}

    /** Stored value of the bitboard */
    uint64_t value;

    /** Count all the bits in the bitboard */
    [[nodiscard]] int getBitCount() const;

    /** Assignment operator for simplicity */
    Bitboard &operator=(const uint64_t &nvalue)
    {
        value = nvalue;
        return *this;
    }
};

struct Board
{
    Bitboard data[12];

    [[nodiscard]] Bitboard getTotalValue() const;
};

#endif // bitboard_H
