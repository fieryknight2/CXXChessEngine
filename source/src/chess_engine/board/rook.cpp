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

using namespace chessengine;
using namespace board;

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
char Rook::getType() const
{
    return PieceType::ROOK;
}

/** Get the legal moves for the piece
 *
 * @param moves Pointer to a 64-bit integer to store the legal moves
 */
void Rook::getLegalMoves(uint64_t &moves) const
{
    SL_ASSERT_TRUE(m_board, "Error: Board is null");
    SL_ASSERT_TRUE(m_board->board.genMoveInfo, "Error: Move info not generated, cannot generate legal moves");

    Bitboard myPieces;
    Bitboard otherPieces;

    int pieceOffset = m_color ? 6 : 0;

    if (m_color)
    {
        myPieces = m_board->board.whitePieces;
        otherPieces = m_board->board.blackPieces;
    }
    else
    {
        myPieces = m_board->board.blackPieces;
        otherPieces = m_board->board.whitePieces;
    }

    // Process possible moves
    unsigned int index = m_location;

    // Up and Down
    if (m_location / 8 > m_blackKing->getSquare() / 8 and m_location % 8 == m_blackKing->getSquare() % 8)
    {
        // King is below the pawn
        while (index < 56)
        {
            index += 8;

            // Check for potential pin
            if (m_board->board.data[PieceLoc::BLACK_ROOK + pieceOffset].value & (0b1ull << index) or
                m_board->board.data[PieceLoc::BLACK_QUEEN + pieceOffset].value & (0b1ull << index))
            {
                for (index = m_location; index > 7;)
                {
                    index -= 8;

                    if (m_board->board.allPieces.value & (0b1ull << index) and
                        !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)))
                    {
                        // No pin
                        getBottomTopMoves(moves);
                        getLeftRightMoves(moves);
                        return;
                    }
                    if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))
                    {
                        // Pinned
                        break;
                    }


                    // Pinned
                    getBottomTopMoves(moves);
                    return;
                }

                if (m_board->board.allPieces.value & (0b1ull << index))
                {
                    // Piece that does not pin has gotten in the way
                    // All moves are possible
                    getBottomTopMoves(moves);
                    getLeftRightMoves(moves);
                    return;
                }
            }
        }
    }
    else if (m_location / 8 - m_blackKing->getSquare() / 8 < 0 and m_location % 8 - m_blackKing->getSquare() % 8 == 0)
    {
        // King is above the pawn
        while (index > 7)
        {
            index -= 8;

            // Check for potential pin
            if (m_board->board.data[PieceLoc::BLACK_ROOK + pieceOffset].value & (0b1ull << index) or
                m_board->board.data[PieceLoc::BLACK_QUEEN + pieceOffset].value & (0b1ull << index))
            {
                for (index = m_location; index < 56;)
                {
                    index += 8;

                    if (m_board->board.allPieces.value & (0b1ull << index) and
                        !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)))
                    {
                        // No pin
                        getBottomTopMoves(moves);
                        getLeftRightMoves(moves);
                        return;
                    }
                    if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))
                    {
                        // Pinned
                        break;
                    }
                }

                // Pinned
                getBottomTopMoves(moves);
                return;
            }

            if (m_board->board.allPieces.value & (0b1ull << index))
            {
                // Piece that does not pin has gotten in the way
                // All moves are possible
                getBottomTopMoves(moves);
                getLeftRightMoves(moves);
                return;
            }
        }
    }

    // Left and Right
    else if (m_location / 8 == m_blackKing->getSquare() / 8 and m_location % 8 < m_blackKing->getSquare() % 8)
    {
        // King is on the left of the pawn
        while (index % 8 < 7)
        {
            ++index;

            // Check for potential pin
            if (m_board->board.data[PieceLoc::BLACK_ROOK + pieceOffset].value & (0b1ull << index) or
                m_board->board.data[PieceLoc::BLACK_QUEEN + pieceOffset].value & (0b1ull << index))
            {
                for (index = m_location; index % 8 > 0;)
                {
                    --index;

                    if (m_board->board.allPieces.value & (0b1ull << index) and
                        !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)))
                    {
                        // No pin
                        getBottomTopMoves(moves);
                        getLeftRightMoves(moves);
                        return;
                    }
                    if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))
                    {
                        // Pinned
                        break;
                    }
                }

                // Pinned
                getLeftRightMoves(moves);
                return;
            }

            if (m_board->board.allPieces.value & (0b1ull << index))
            {
                // Piece that does not pin has gotten in the way
                // All moves are possible
                getBottomTopMoves(moves);
                getLeftRightMoves(moves);
                return;
            }
        }
    }
    else if (m_location / 8 - m_blackKing->getSquare() / 8 == 0 and m_location % 8 > m_blackKing->getSquare() % 8)
    {
        // King is to the right of the pawn
        while (index % 8 > 0)
        {
            --index;

            // Check for potential pin
            if (m_board->board.data[PieceLoc::BLACK_ROOK + pieceOffset].value & (0b1ull << index) or
                m_board->board.data[PieceLoc::BLACK_QUEEN + pieceOffset].value & (0b1ull << index))
            {
                for (index = m_location; index % 8 < 7;)
                {
                    ++index;

                    if (m_board->board.allPieces.value & (0b1ull << index) and
                        !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)))
                    {
                        // No pin
                        getBottomTopMoves(moves);
                        getLeftRightMoves(moves);
                        return;
                    }
                    if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))
                    {
                        // Pinned
                        break;
                    }
                }

                // Pinned
                getLeftRightMoves(moves);
                return;
            }

            if (m_board->board.allPieces.value & (0b1ull << index))
            {
                // Piece that does not pin has gotten in the way
                // All moves are possible
                getBottomTopMoves(moves);
                getLeftRightMoves(moves);
                return;
            }
        }
    }

    // Diagonal
    // Top left to the bottom right
    else if ((m_location / 8 - m_blackKing->getSquare() / 8) == (m_location % 8 - m_blackKing->getSquare() % 8))
    {
        // King is to the bottom right
        if (m_location % 8 < m_blackKing->getSquare() % 8)
        {
            while (index % 8 > 0 and index > 7)
            {
                index -= 9;

                // Check for potential pin
                if (m_board->board.data[PieceLoc::BLACK_ROOK + pieceOffset].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::BLACK_QUEEN + pieceOffset].value & (0b1ull << index))
                {
                    for (index = m_location; index % 8 < 7 and index < 56;)
                    {
                        index += 9;

                        if (m_board->board.allPieces.value & (0b1ull << index) and
                            !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)))
                        {
                            // No pin
                            getBottomTopMoves(moves);
                            getLeftRightMoves(moves);
                            return;
                        }
                        if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))
                        {
                            // Pinned
                            break;
                        }
                    }

                    // Pinned, rook can't move when pinned diagonally
                    return;
                }

                if (m_board->board.allPieces.value & (0b1ull << index))
                {
                    // Piece that does not pin has gotten in the way
                    // All moves are possible
                    getBottomTopMoves(moves);
                    getLeftRightMoves(moves);
                    return;
                }
            }
        }
        // King is to the top left
        else
        {
            while (index % 8 < 7 and index < 56)
            {
                index += 9;

                // Check for potential pin
                if (m_board->board.data[PieceLoc::BLACK_ROOK + pieceOffset].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::BLACK_QUEEN + pieceOffset].value & (0b1ull << index))
                {
                    for (index = m_location; index % 8 > 0 and index > 7;)
                    {
                        index -= 9;

                        if (m_board->board.allPieces.value & (0b1ull << index) and
                            !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)))
                        {
                            // No pin
                            getBottomTopMoves(moves);
                            getLeftRightMoves(moves);
                            return;
                        }
                        if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))
                        {
                            // Pinned
                            break;
                        }
                    }

                    // Pinned
                    return;
                }

                if (m_board->board.allPieces.value & (0b1ull << index))
                {
                    // Piece that does not pin has gotten in the way
                    // All moves are possible
                    getBottomTopMoves(moves);
                    getLeftRightMoves(moves);
                    return;
                }
            }
        }
    }
    // Top right to the bottom left
    else if ((m_location / 8 - m_blackKing->getSquare() / 8) == -(m_location % 8 - m_blackKing->getSquare() % 8))
    {
        // King is to the bottom left
        if (m_location % 8 > m_blackKing->getSquare() % 8)
        {
            while (index % 8 < 7 and index > 7)
            {
                index -= 7;

                // Check for potential pin
                if (m_board->board.data[PieceLoc::BLACK_ROOK + pieceOffset].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::BLACK_QUEEN + pieceOffset].value & (0b1ull << index))
                {
                    for (index = m_location; index % 8 > 0 and index < 56;)
                    {
                        index += 7;

                        if (m_board->board.allPieces.value & (0b1ull << index) and
                            !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)))
                        {
                            // No pin
                            getBottomTopMoves(moves);
                            getLeftRightMoves(moves);
                            return;
                        }
                        if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))
                        {
                            // Pinned
                            break;
                        }
                    }

                    // Pinned
                    return;
                }

                if (m_board->board.allPieces.value & (0b1ull << index))
                {
                    // Piece that does not pin has gotten in the way
                    // All moves are possible
                    getBottomTopMoves(moves);
                    getLeftRightMoves(moves);
                    return;
                }
            }
        }
        // King is to the top right
        else
        {
            while (index % 8 > 0 and index < 56)
            {
                index -= 7;

                // Check for potential pin
                if (m_board->board.data[PieceLoc::BLACK_ROOK + pieceOffset].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::BLACK_QUEEN + pieceOffset].value & (0b1ull << index))
                {
                    for (index = m_location; index % 8 < 7 and index > 7;)
                    {
                        index += 7;

                        if (m_board->board.allPieces.value & (0b1ull << index) and
                            !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)))
                        {
                            // No pin
                            getBottomTopMoves(moves);
                            getLeftRightMoves(moves);
                            return;
                        }
                        if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))
                        {
                            // Pinned
                            break;
                        }
                    }

                    // Pinned
                    return;
                }

                if (m_board->board.allPieces.value & (0b1ull << index))
                {
                    // Piece that does not pin has gotten in the way
                    // All moves are possible
                    getBottomTopMoves(moves);
                    getLeftRightMoves(moves);
                    return;
                }
            }
        }
    }

    // No pins, all possible moves:
    getLeftRightMoves(moves);
    getBottomTopMoves(moves);
}

/** Get the possible attacks for the piece
 *
 * @param attacks Pointer to a 64-bit integer to store the legal attacks
 */
void Rook::getAttacks(uint64_t &attacks) const
{
    unsigned int index = m_location;

    while (index < 56)
    {
        // Top
        index += 8;
        attacks |= 1ull << index;

        if (m_board->board.allPieces.value & (1ull << index))
        {
            break;
        }
    }

    index = m_location;
    while (index % 8 < 7)
    {
        // Left
        index += 1;
        attacks |= 1ull << index;

        if (m_board->board.allPieces.value & (1ull << index))
        {
            break;
        }
    }

    index = m_location;
    while (index % 8 > 0)
    {
        // Right
        index -= 1;
        attacks |= 1ull << index;

        if (m_board->board.allPieces.value & (1ull << index))
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

        if (m_board->board.allPieces.value & (1ull << index))
        {
            break;
        }
    }
}

void Rook::getLeftRightMoves(uint64_t &moves) const
{
    unsigned int index = m_location;

    while (index % 8 < 7)
    {
        // Left
        index += 1;

        if (!((m_color ? m_board->board.whitePieces : m_board->board.blackPieces).value & (1ull << index)))
        {
            moves |= 1ull << index;
        }

        if (m_board->board.allPieces.value & (1ull << index))
        {
            break;
        }
    }

    index = m_location;
    while (index % 8 > 0)
    {
        // Right
        index -= 1;

        if (!((m_color ? m_board->board.whitePieces : m_board->board.blackPieces).value & (1ull << index)))
        {
            moves |= 1ull << index;
        }

        if (m_board->board.allPieces.value & (1ull << index))
        {
            break;
        }
    }
}

void Rook::getBottomTopMoves(uint64_t &moves) const
{
    unsigned int index = m_location;

    while (index < 56)
    {
        // Top
        index += 8;

        if (!((m_color ? m_board->board.whitePieces : m_board->board.blackPieces).value & (1ull << index)))
        {
            moves |= 1ull << index;
        }

        if (m_board->board.allPieces.value & (1ull << index))
        {
            break;
        }
    }

    index = m_location;
    while (index > 7)
    {
        // Bottom
        index -= 8;

        if (!((m_color ? m_board->board.whitePieces : m_board->board.blackPieces).value & (1ull << index)))
        {
            moves |= 1ull << index;
        }

        if (m_board->board.allPieces.value & (1ull << index))
        {
            break;
        }
    }
}
