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

using namespace chessengine;
using namespace board;

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
char Knight::getType() const
{
    return 'n';
}

/** Get the legal moves for the piece
 *
 * @param moves Pointer to a 64-bit integer to store the legal moves
 */
void Knight::getLegalMoves(uint64_t &moves) const
{
    SL_ASSERT_TRUE(m_board, "Error: Board is null");
    SL_ASSERT_TRUE(m_board->board.genMoveInfo, "Error: Move info not generated, cannot generate legal moves");

    // The knight cannot move if it is pinned, so go through every possible
    // pin and return if it is.
    // Same column
    unsigned int index = m_location;
    int pieceOffset = m_color ? 6 : 0; // Black offset is 6
    // King offset is the reverse of piece offset

    if (Piece *king = m_color ? m_whiteKing : m_blackKing;
        m_location / 8 > king->getSquare() / 8 and m_location % 8 == king->getSquare() % 8)
    {
        // King is below the knight
        while (index < 56) // Not on the 8th rank
        {
            index += 8; // Move up 1 rank

            // Is pinned
            if (m_board->board.data[PieceLoc::WHITE_ROOK + pieceOffset].value & (0b1ull << index) or
                m_board->board.data[PieceLoc::WHITE_QUEEN + pieceOffset].value & (0b1ull << index))
            {
                // Check if the king is pinned
                for (index = m_location; index > 7;)
                {
                    index -= 8;

                    if (m_board->board.allPieces.value & (0b1ull << index) and
                        !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)))
                    {
                        // Pawn can't be pinned
                        break;
                    }
                    if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))
                    {
                        // Pinned
                        return;
                    }
                }

                break;
            }

            if (m_board->board.allPieces.value & (0b1ull << index))
            {
                break;
            }
        }
    }
    else if (m_location / 8 < king->getSquare() / 8 and m_location % 8 == king->getSquare() % 8)
    {
        while (index > 7) // Not on the 1st rank
        {
            index -= 8; // Move down 1 rank

            // Is pinned
            if (m_board->board.data[PieceLoc::WHITE_ROOK + pieceOffset].value & (0b1ull << index) or
                m_board->board.data[PieceLoc::WHITE_QUEEN + pieceOffset].value & (0b1ull << index))
            {
                for (index = m_location; index < 56;)
                {
                    index += 8;

                    if (m_board->board.allPieces.value & (0b1ull << index) and
                        !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)))
                    {
                        // Pawn can't be pinned
                        break;
                    }
                    if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))
                    {
                        // Pinned
                        return;
                    }
                }

                break;
            }

            if (m_board->board.allPieces.value & (0b1ull << index))
            {
                break;
            }
        }
    }

    // Same rank
    else if (m_location / 8 - king->getSquare() / 8 == 0 and m_location % 8 < king->getSquare() % 8)
    {
        // King is to the left of the knight
        while (index % 8 > 0)
        {
            --index; // Move left 1 column

            if (m_board->board.data[PieceLoc::WHITE_ROOK + pieceOffset].value & (0b1ull << index) or
                m_board->board.data[PieceLoc::WHITE_QUEEN + pieceOffset].value & (0b1ull << index))
            {
                for (index = m_location; index % 8 < 7;)
                {
                    ++index;

                    if (m_board->board.allPieces.value & (0b1ull << index) and
                        !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)))
                    {
                        // Pawn can't be pinned
                        break;
                    }
                    if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))
                    {
                        // Pinned
                        return;
                    }
                }

                break;
            }

            if (m_board->board.allPieces.value & (0b1ull << index))
            {
                break;
            }
        }
    }
    else if (m_location / 8 - king->getSquare() / 8 == 0 and m_location % 8 > king->getSquare() % 8)
    {
        // King is to the right of the knight
        while (index % 8 < 7)
        {
            ++index;

            if (m_board->board.data[PieceLoc::WHITE_ROOK + pieceOffset].value & (0b1ull << index) or
                m_board->board.data[PieceLoc::WHITE_QUEEN + pieceOffset].value & (0b1ull << index))
            {
                for (index = m_location; index % 8 > 0;)
                {
                    --index;

                    if (m_board->board.allPieces.value & (0b1ull << index) and
                        !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)))
                    {
                        // Pawn can't be pinned
                        break;
                    }
                    if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))
                    {
                        // Pinned
                        return;
                    }
                }

                break;
            }

            if (m_board->board.allPieces.value & (0b1ull << index))
            {
                break;
            }
        }
    }

    // Diagonal
    else if ((m_location / 8 - king->getSquare() / 8) == (m_location % 8 - king->getSquare() % 8))
    {
        // Positive means right
        // Moving from the bottom right to top left
        if (m_location % 8 > king->getSquare() % 8)
        {
            // Pin has to come from top left
            while (index % 8 < 7 and index > 7)
            {
                index += 9;

                if (m_board->board.data[PieceLoc::WHITE_BISHOP + pieceOffset].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::WHITE_QUEEN + pieceOffset].value & (0b1ull << index))
                {
                    for (index = m_location; index % 8 > 0 and index < 56;)
                    {
                        index -= 9;

                        if (m_board->board.allPieces.value & (0b1ull << index) and
                            !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)))
                        {
                            // Pawn can't be pinned
                            break;
                        }
                        if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))
                        {
                            // Pinned
                            return;
                        }
                    }

                    break;
                }

                if (m_board->board.allPieces.value & (0b1ull << index))
                {
                    break;
                }
            }
        }
        else
        {
            // Pin has to come from bottom right
            while (index % 8 > 0 and index < 56)
            {
                index -= 9;

                if (m_board->board.data[PieceLoc::WHITE_BISHOP + pieceOffset].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::WHITE_QUEEN + pieceOffset].value & (0b1ull << index))
                {
                    for (index = m_location; index % 8 < 7 and index > 7;)
                    {
                        index += 9;

                        if (m_board->board.allPieces.value & (0b1ull << index) and
                            !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)))
                        {
                            // Pawn can't be pinned
                            break;
                        }
                        if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))
                        {
                            // Pinned
                            return;
                        }
                    }

                    break;
                }

                if (m_board->board.allPieces.value & (0b1ull << index))
                {
                    break;
                }
            }
        }
    }
    else if ((m_location / 8 - king->getSquare() / 8) == -(m_location % 8 - king->getSquare() % 8))
    {
        // Moving from the bottom left to the top right
        if (m_location % 8 > king->getSquare() % 8)
        {
            // Pin has to come from bottom left
            while (index % 8 < 7 and index > 7)
            {
                index -= 7;

                if (m_board->board.data[PieceLoc::WHITE_BISHOP + pieceOffset].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::WHITE_QUEEN + pieceOffset].value & (0b1ull << index))
                {
                    for (index = m_location; index % 8 > 0 and index < 56;)
                    {
                        index += 7;

                        if (m_board->board.allPieces.value & (0b1ull << index) and
                            !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)))
                        {
                            // Pawn can't be pinned
                            break;
                        }
                        if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))
                        {
                            // Pinned
                            return;
                        }
                    }

                    break;
                }

                if (m_board->board.allPieces.value & (0b1ull << index))
                {
                    break;
                }
            }
        }
        else
        {
            // Pin has to come from top right
            while (index % 8 < 7 and index < 56)
            {
                index += 7;

                if (m_board->board.data[PieceLoc::WHITE_BISHOP + pieceOffset].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::WHITE_QUEEN + pieceOffset].value & (0b1ull << index))
                {
                    for (index = m_location; index % 8 < 7 and index > 7;)
                    {
                        index -= 7;

                        if (m_board->board.allPieces.value & (0b1ull << index) and
                            !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)))
                        {
                            // Pawn can't be pinned
                            break;
                        }
                        if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))
                        {
                            // Pinned
                            return;
                        }
                    }

                    break;
                }

                if (m_board->board.allPieces.value & (0b1ull << index))
                {
                    break;
                }
            }
        }
    }

    // Possible moves:
    uint64_t attacks = 0;
    getAttacks(attacks);

    // Get possible moves
    moves |= ~(m_color ? m_board->board.whitePieces : m_board->board.blackPieces).value & attacks;
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
