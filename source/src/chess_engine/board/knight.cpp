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
 * knight.cpp - <Brief description>
 * @author Matthew Brown
 * @date 05/27/2024
 *****************************************************************************/
#include "chess_engine/board/knight.h"

/** Make a move on the board
 *
 * @param to Location to move the piece to
 */
void Knight::makeMove(int to)
{
    // TODO: Implement
}

/** Get the type of the piece
 *
 * @return Type of the piece
 */
char Knight::getType() const { return 'n'; }

/** Get the legal moves for the piece
 *
 * @param moves Pointer to a 64-bit integer to store the legal moves
 */
void Knight::getLegalMoves(uint64_t &moves) const
{
    // TODO: Implement
}

/** Get attacks for the piece
 *
 * @param attacks Pointer to a 64-bit integer to store the legal attacks
 */
void Knight::getAttacks(uint64_t &attacks) const
{
    if (m_location / 8 > 1)
    {
        // C++ automatically converts int / int to int, no integer division necessary
        // validate bottom far
        if (m_location % 8 > 0)
        {
            // validate right close
            attacks |= 1ull << (m_location - 17);
        }
        if (m_location % 8 < 7)
        {
            // validate left close
            attacks |= 1ull << (m_location - 15);
        }
    }

    if (m_location / 8 > 0)
    {
        // validate bottom close
        if (m_location % 8 > 1)
        {
            // validate right far
            attacks |= 1ull << (m_location - 10);
        }
        if (m_location % 8 < 6)
        {
            // validate left far
            attacks |= 1ull << (m_location - 6);
        }
    }

    if (m_location / 8 < 7)
    {
        // validate top close
        if (m_location % 8 > 1)
        {
            // validate right far
            attacks |= 1ull << (m_location + 6);
        }
        if (m_location % 8 < 6)
        {
            // validate left far
            attacks |= 1ull << (m_location + 10);
        }
    }

    if (m_location / 8 < 6)
    {
        // validate top far
        if (m_location % 8 > 0)
        {
            // validate right close
            attacks |= 1ull << (m_location + 15);
        }
        if (m_location % 8 < 7)
        {
            // validate left close
            attacks |= 1ull << (m_location + 17);
        }
    }
}
