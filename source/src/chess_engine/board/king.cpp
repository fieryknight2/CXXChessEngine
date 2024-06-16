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
 * king.cpp - <Brief description>
 * @author Matthew Brown
 * @date 05/27/2024
 *****************************************************************************/
#include "chess_engine/board/king.h"

using namespace chessengine;
using namespace board;

/** Make a move on the board
 *
 * @param to Location to move the piece to
 */
void King::makeMove(int to)
{
    m_location = to;
}

/** Get the type of the piece
 *
 * @return Type of the piece
 */
char King::getType() const
{
    return PieceType::KING;
}

/** Get the legal moves for the piece
 *
 * @param moves Pointer to a 64-bit integer to store the legal moves
 */
void King::getLegalMoves(uint64_t &moves) const
{
    SL_ASSERT_TRUE(m_board, "Error: Board is null");
    SL_ASSERT_TRUE(m_board->board.genMoveInfo, "Error: Move info not generated, cannot generate legal moves");

    uint64_t attacks = 0;

    getAttacks(attacks);

    moves |= attacks & (~(m_color ? m_board->board.whitePieces : m_board->board.blackPieces).value) &
            (~(m_color ? m_board->board.blackAttacks : m_board->board.whiteAttacks).value);
}

/** Get the possible attacks for the piece
 *
 * @param attacks Pointer to a 64-bit integer to store the legal attacks
 */
void King::getAttacks(uint64_t &attacks) const
{
    // validate top
    if (m_location < 56)
    {
        if (m_location % 8 < 7)
        {
            attacks |= 1ull << (m_location + 9); // top left corner
        }

        attacks |= 1ull << (m_location + 8); // top

        if (m_location % 8 > 0)
        {
            attacks |= 1ull << (m_location + 7); // top right corner
        }
    }

    if (m_location % 8 < 7)
    {
        // validate left
        attacks |= 1ull << (m_location + 1);
    }

    if (m_location % 8 > 0)
    {
        // validate right
        attacks |= 1ull << (m_location - 1);
    }

    if (m_location > 7)
    {
        // validate bottom
        if (m_location % 8 < 7)
        {
            attacks |= 1ull << (m_location - 7); // bottom left corner
        }

        attacks |= 1ull << (m_location - 8); // bottom

        if (m_location % 8 > 0)
        {
            attacks |= 1ull << (m_location - 9); // bottom right corner
        }
    }
}
