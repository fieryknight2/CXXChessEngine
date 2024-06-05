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
 * rook.cpp - <Brief description>
 * @author Matthew Brown
 * @date 05/27/2024
 *****************************************************************************/
#include "chess_engine/board/rook.h"

/** Make a move on the board
 *
 * @param to Location to move the piece to
 */
void Rook::makeMove(int to)
{
    // TODO: Implement
}

/** Get the type of the piece
 *
 * @return Type of the piece
 */
char Rook::getType() const { return PieceType::ROOK; }

/** Get the legal moves for the piece
 *
 * @param moves Pointer to a 64-bit integer to store the legal moves
 */
void Rook::getLegalMoves(uint64_t &moves) const
{
    // TODO: Implement
}

/** Get the possible attacks for the piece
 *
 * @param attacks Pointer to a 64-bit integer to store the legal attacks
 */
void Rook::getAttacks(uint64_t &attacks) const
{
    unsigned int index = m_location;
    const unsigned int rankMin = (m_location / 8) * 8;
    uint64_t totalValue = m_board->board.getTotalValue().value;

    while (index < 56)
    {
        // Top
        index += 8;
        attacks |= 1ull << index;

        if (!(totalValue & (1ull << index)))
        {
            break;
        }
    }

    index = m_location;
    while (index < rankMin + 7)
    {
        // Left
        index += 1;
        attacks |= 1ull << index;

        if (!(totalValue & (1ull << index)))
        {
            break;
        }
    }

    index = m_location;
    while (index >= rankMin + 1)
    {
        // Right
        index -= 1;
        attacks |= 1ull << index;

        if (!(totalValue & (1ull << index)))
        {
            break;
        }
    }

    index = m_location;
    while (index >= 8)
    {
        // Bottom
        index -= 8;
        attacks |= 1ull << index;

        if (!(totalValue & (1ull << index)))
        {
            break;
        }
    }
}
