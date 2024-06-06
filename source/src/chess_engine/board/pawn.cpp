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
 * pawn.cpp - <Brief description>
 * @author Matthew Brown
 * @date 05/27/2024
 *****************************************************************************/
#include "chess_engine/board/pawn.h"

/** Make a move on the board
 *
 * @param to Location to move the piece to
 */
void Pawn::makeMove(int to) { m_location = to; }

/** Get the type of the piece
 *
 * @return Type of the piece
 */
char Pawn::getType() const { return PieceType::PAWN; }

/** Get the legal moves for the piece
 *
 * @param moves Pointer to a 64-bit integer to store the legal moves
 */
void Pawn::getLegalMoves(uint64_t &moves) const
{
    if (m_location < 8 or m_location > 55)
    {
        return;
    }

    Bitboard pieces;
    Bitboard blackPieces;

    m_board->board.getBlackPieces(blackPieces);
    m_board->board.getTotalValue(pieces);

    unsigned int index = m_location;
    if (m_color) // White
    {
        // Find a possible pin and determine legal moves

        // Direction between ranks: - for up, + for down          Same Column == Up or Down
        if (m_location / 8 - m_whiteKing->getSquare() / 8 > 0 and m_location % 8 - m_whiteKing->getSquare() % 8 == 0)
        {
            /* King is below the pawn,
               Pin direction can be from up */
            while (index < 56) // Not on the 8th rank
            {
                index += 8; // Move up 1 rank

                // Is pinned
                if (m_board->board.data[PieceLoc::BLACK_ROOK].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::BLACK_QUEEN].value & (0b1ull << index))
                {
                    // Black piece is pinning
                    // No attacks are possible, but the pawn can move forward
                    getForwardMoves(moves, pieces);
                    return;
                }

                if (pieces.value & (0b1ull << index))
                {
                    // Piece that does not pin has gotten in the way
                    // All moves are possible
                    getAllMoves(moves);
                    return;
                }
            }
        }
        if (m_location / 8 - m_whiteKing->getSquare() / 8 < 0 and m_location % 8 - m_whiteKing->getSquare() % 8 == 0)
        {
            /* King is above the pawn,
               Pin direction can be from down */
            while (index > 7) // Not on the 1st rank
            {
                index -= 8; // Move down 1 rank

                // Is pinned
                if (m_board->board.data[PieceLoc::BLACK_ROOK].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::BLACK_QUEEN].value & (0b1ull << index))
                {
                    // Black piece is pinning
                    // No attacks are possible, but the pawn can move forward
                    getForwardMoves(moves, pieces);
                    return;
                }

                if (pieces.value & (0b1ull << index))
                {
                    // Piece that does not pin has gotten in the way
                    // All moves are possible
                    getAllMoves(moves);
                    return;
                }
            }
        }

        // Same rank                                               Direction between columns: - for right, + for left
        if (m_location / 8 - m_whiteKing->getSquare() / 8 == 0 and m_location % 8 - m_whiteKing->getSquare() % 8 < 0)
        {
            /** King is on the right of the pawn,
             * Pin direction can be from left */
            while (index % 8 < 7)
            {
                ++index; // Move left 1 column

                if (m_board->board.data[PieceLoc::BLACK_ROOK].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::BLACK_QUEEN].value & (0b1ull << index))
                {
                    // Black piece is pinning from the side, no moves are possible
                    return;
                }

                if (pieces.value & (0b1ull << index))
                {
                    // No pin, all moves are possible
                    getAllMoves(moves);
                    return;
                }
            }
        }
        if (m_location / 8 - m_whiteKing->getSquare() / 8 == 0 and m_location % 8 - m_whiteKing->getSquare() % 8 > 0)
        {
            /** King is on the left of the pawn,
             * Pin direction can be from right */
            while (index % 8 > 0)
            {
                --index; // Move right 1 column

                if (m_board->board.data[PieceLoc::BLACK_ROOK].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::BLACK_QUEEN].value & (0b1ull << index))
                {
                    // Black piece is pinning from the side, no moves are possible
                    return;
                }

                if (pieces.value & (0b1ull << index))
                {
                    // No pin, all moves are possible
                    getAllMoves(moves);
                    return;
                }
            }
        }

        // Diagonal moves
        // Moving from the bottom left to the top right
        if ((m_location / 8 - m_whiteKing->getSquare() / 8) == (m_location % 8 - m_whiteKing->getSquare() % 8))
        {
            // Right is positive
            if (m_location % 8 - m_whiteKing->getSquare() % 8 > 0)
            {
                // Pin has to come from bottom left
                while (index % 8 < 7 and index > 7)
                {
                    index -= 7;

                    if (m_board->board.data[PieceLoc::BLACK_BISHOP].value & (0b1ull << index) or
                        m_board->board.data[PieceLoc::BLACK_QUEEN].value & (0b1ull << index))
                    {
                        // Pinned, only possible move is a capture to the top right
                        if (m_location % 8 > 0 and blackPieces.value & (0b1ull << (m_location + 7)))
                        {
                            moves |= 1ull << (m_location + 7);
                        }

                        return;
                    }

                    if (pieces.value & (0b1ull << index))
                    {
                        // No pin, all moves are possible
                        getAllMoves(moves);
                        return;
                    }
                }
            }
            else
            {
                // Pin has to come from top right
                while (index % 8 > 0 and index < 56)
                {
                    index += 7;

                    if (m_board->board.data[PieceLoc::BLACK_BISHOP].value & (0b1ull << index) or
                        m_board->board.data[PieceLoc::BLACK_QUEEN].value & (0b1ull << index))
                    {
                        // Pinned, only possible move is a capture to the top right
                        if (m_location % 8 > 0 and (blackPieces.value & (0b1ull << m_location + 7) or
                                                    m_location + 7 == m_board->enPassantSquare))
                        {
                            moves |= 1ull << (m_location + 7);
                        }

                        return;
                    }

                    if (pieces.value & (0b1ull << index))
                    {
                        // No pin, all moves are possible
                        getAllMoves(moves);
                        return;
                    }
                }
            }
        }
        // Moving from the top left to the bottom right
        if ((m_location / 8 - m_whiteKing->getSquare() / 8) == -(m_location % 8 - m_whiteKing->getSquare() % 8))
        {
            // Right is positive
            if (m_location % 8 - m_whiteKing->getSquare() % 8 > 0)
            {
                // Pin has to come from bottom right
                while (index % 8 > 0 and index > 7)
                {
                    index -= 9;

                    if (m_board->board.data[PieceLoc::BLACK_BISHOP].value & (0b1ull << index) or
                        m_board->board.data[PieceLoc::BLACK_QUEEN].value & (0b1ull << index))
                    {
                        // Pinned, only possible move is a capture to the top left
                        if (m_location % 8 < 7 and (blackPieces.value & (0b1ull << m_location + 9) or
                                                    m_location + 9 == m_board->enPassantSquare))
                        {
                            moves |= 1ull << (m_location + 9);
                        }

                        return;
                    }

                    if (pieces.value & (0b1ull << index))
                    {
                        // No pin, all moves are possible
                        getAllMoves(moves);
                        return;
                    }
                }
            }
            else
            {
                // Pin has to come from top left
                while (index % 8 < 7 and index < 56)
                {
                    index += 9;

                    if (m_board->board.data[PieceLoc::BLACK_BISHOP].value & (0b1ull << index) or
                        m_board->board.data[PieceLoc::BLACK_QUEEN].value & (0b1ull << index))
                    {
                        // Pinned, only possible move is a capture to the top left
                        if (m_location % 8 < 7 and (blackPieces.value & (0b1ull << m_location + 9) or
                                                    m_location + 9 == m_board->enPassantSquare))
                        {
                            moves |= 1ull << (m_location + 9);
                        }

                        return;
                    }

                    if (pieces.value & (0b1ull << index))
                    {
                        // No pin, all moves are possible
                        getAllMoves(moves);
                        return;
                    }
                }
            }
        }

        // No pins
        getAllMoves(moves);
    }
    else // Black
    {
        // Code for black just flips a lot of the above code
        // The rest is copy and paste, maybe change later?

        // Direction between ranks: - for up, + for down          Same Column == Up or Down
        if (m_location / 8 - m_blackKing->getSquare() / 8 > 0 and m_location % 8 - m_blackKing->getSquare() % 8 == 0)
        {
            /* King is below the pawn,
               Pin direction can be from up */
            while (index < 56) // Not on the 8th rank
            {
                index += 8; // Move up 1 rank

                // Is pinned
                if (m_board->board.data[PieceLoc::WHITE_ROOK].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::WHITE_QUEEN].value & (0b1ull << index))
                {
                    // White piece is pinning
                    // No attacks are possible, but the pawn can move forward
                    getForwardMoves(moves, pieces);
                    return;
                }

                if (pieces.value & (0b1ull << index))
                {
                    // Piece that does not pin has gotten in the way
                    // All moves are possible
                    getAllMoves(moves);
                    return;
                }
            }
        }
        else if (m_location / 8 - m_blackKing->getSquare() / 8 < 0 and
                 m_location % 8 - m_blackKing->getSquare() % 8 == 0)
        {
            /* King is above the pawn,
               Pin direction can be from down */
            while (index > 7) // Not on the 1st rank
            {
                index -= 8; // Move down 1 rank

                // Is pinned
                if (m_board->board.data[PieceLoc::WHITE_ROOK].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::WHITE_QUEEN].value & (0b1ull << index))
                {
                    // White piece is pinning
                    // No attacks are possible, but the pawn can move forward
                    getForwardMoves(moves, pieces);
                    return;
                }

                if (pieces.value & (0b1ull << index))
                {
                    // Piece that does not pin has gotten in the way
                    // All moves are possible
                    getAllMoves(moves);
                    return;
                }
            }
        }

        // Same rank                                               Direction between columns: - for right, + for left
        else if (m_location / 8 - m_blackKing->getSquare() / 8 == 0 and
                 m_location % 8 - m_blackKing->getSquare() % 8 < 0)
        {
            /** King is on the right of the pawn,
             * Pin direction can be from left */
            while (index % 8 < 7)
            {
                ++index; // Move left 1 column

                if (m_board->board.data[PieceLoc::WHITE_ROOK].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::WHITE_QUEEN].value & (0b1ull << index))
                {
                    // White piece is pinning from the side, no moves are possible
                    return;
                }

                if (pieces.value & (0b1ull << index))
                {
                    // No pin, all moves are possible
                    getAllMoves(moves);
                    return;
                }
            }
        }
        else if (m_location / 8 - m_blackKing->getSquare() / 8 == 0 and
                 m_location % 8 - m_blackKing->getSquare() % 8 > 0)
        {
            /** King is on the left of the pawn,
             * Pin direction can be from right */
            while (index % 8 > 0)
            {
                --index; // Move right 1 column

                if (m_board->board.data[PieceLoc::WHITE_ROOK].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::WHITE_QUEEN].value & (0b1ull << index))
                {
                    // White piece is pinning from the side, no moves are possible
                    return;
                }

                if (pieces.value & (0b1ull << index))
                {
                    // No pin, all moves are possible
                    getAllMoves(moves);
                    return;
                }
            }
        }

        // Diagonal moves
        // Moving from the bottom left to the top right
        else if ((m_location / 8 - m_blackKing->getSquare() / 8) == (m_location % 8 - m_blackKing->getSquare() % 8))
        {
            // Right is positive
            if (m_location % 8 - m_blackKing->getSquare() % 8 > 0)
            {
                // Pin has to come from bottom left
                while (index % 8 < 7 and index > 7)
                {
                    index -= 7;

                    if (m_board->board.data[PieceLoc::WHITE_BISHOP].value & (0b1ull << index) or
                        m_board->board.data[PieceLoc::WHITE_QUEEN].value & (0b1ull << index))
                    {
                        // Pinned, only possible move is a capture to the bottom left
                        if (m_location % 8 < 7 and (blackPieces.value & (0b1ull << m_location - 7) or
                                                    m_location - 7 == m_board->enPassantSquare))
                        {
                            moves |= 1ull << (m_location - 7);
                        }

                        return;
                    }

                    if (pieces.value & (0b1ull << index))
                    {
                        // No pin, all moves are possible
                        getAllMoves(moves);
                        return;
                    }
                }
            }
            else
            {
                // Pin has to come from top right
                while (index % 8 > 0 and index < 56)
                {
                    index += 7;

                    if (m_board->board.data[PieceLoc::WHITE_BISHOP].value & (0b1ull << index) or
                        m_board->board.data[PieceLoc::WHITE_QUEEN].value & (0b1ull << index))
                    {
                        // Pinned, only possible move is a capture to the bottom left
                        if (m_location % 8 < 7 and (blackPieces.value & (0b1ull << m_location - 7) or
                                                    m_location - 7 == m_board->enPassantSquare))
                        {
                            moves |= 1ull << (m_location - 7);
                        }

                        return;
                    }

                    if (pieces.value & (0b1ull << index))
                    {
                        // No pin, all moves are possible
                        getAllMoves(moves);
                        return;
                    }
                }
            }
        }
        // Moving from the top left to the bottom right
        else if ((m_location / 8 - m_blackKing->getSquare() / 8) == -(m_location % 8 - m_blackKing->getSquare() % 8))
        {
            // Right is positive
            if (m_location % 8 - m_blackKing->getSquare() % 8 > 0)
            {
                // Pin has to come from bottom right
                while (index % 8 > 0 and index > 7)
                {
                    index -= 9;

                    if (m_board->board.data[PieceLoc::WHITE_BISHOP].value & (0b1ull << index) or
                        m_board->board.data[PieceLoc::WHITE_QUEEN].value & (0b1ull << index))
                    {
                        // Pinned, only possible move is a capture to the bottom right
                        if (m_location % 8 > 0 and (blackPieces.value & (0b1ull << m_location - 9) or
                                                    m_location - 9 == m_board->enPassantSquare))
                        {
                            moves |= 1ull << (m_location - 9);
                        }

                        return;
                    }

                    if (pieces.value & (0b1ull << index))
                    {
                        // No pin, all moves are possible
                        getAllMoves(moves);
                        return;
                    }
                }
            }
            else
            {
                // Pin has to come from top left
                while (index % 8 < 7 and index < 56)
                {
                    index += 9;

                    if (m_board->board.data[PieceLoc::WHITE_BISHOP].value & (0b1ull << index) or
                        m_board->board.data[PieceLoc::WHITE_QUEEN].value & (0b1ull << index))
                    {
                        // Pinned, only possible move is a capture to the top left
                        if (m_location % 8 > 0 and (blackPieces.value & (0b1ull << m_location - 9) or
                                                    m_location - 9 == m_board->enPassantSquare))
                        {
                            moves |= 1ull << (m_location - 9);
                        }

                        return;
                    }

                    if (pieces.value & (0b1ull << index))
                    {
                        // No pin, all moves are possible
                        getAllMoves(moves);
                        return;
                    }
                }
            }
        }

        // No pins
        getAllMoves(moves);
    }
}

/** Get the possible attacks for the piece
 *
 * @param attacks Pointer to a 64-bit integer to store the legal attacks
 */
void Pawn::getAttacks(uint64_t &attacks) const
{
    if (m_location > 55 or m_location < 8)
    {
        return;
    }

    /* White pawn attacks:
     * Loc: 0
     *
     *  +9 X   X +7
     *       P
     *
     *      Loc: 63
     */
    if (m_color) // White
    {
        if (m_location % 8 > 0)
        {
            // Right side
            attacks |= 1ull << (m_location + 7);
        }
        if (m_location % 8 < 7)
        {
            // Left side
            attacks |= 1ull << (m_location + 9);
        }
    }
    else // Black
    {
        if (m_location % 8 > 0)
        {
            // Left side
            attacks |= 1ull << (m_location - 7);
        }
        if (m_location % 8 < 7)
        {
            // Right side
            attacks |= 1ull << (m_location - 9);
        }
    }
}

void Pawn::getAllMoves(uint64_t &moves) const
{
    if (m_location > 55 or m_location < 8)
    {
        return; // Invalid location
    }

    Bitboard pieces;
    m_board->board.getTotalValue(pieces);

    if (m_color) // White
    {
        Bitboard blackPieces;

        m_board->board.getBlackPieces(blackPieces);
        // Possible attacks
        if (m_location % 8 > 0 and
            (blackPieces.value & (1ull << (m_location + 7)) or m_location + 7 == m_board->enPassantSquare))
        {
            // Right side
            moves |= 1ull << (m_location + 7);
        }
        if (m_location % 8 < 7 and
            (blackPieces.value & (1ull << (m_location + 9)) or m_location + 9 == m_board->enPassantSquare))
        {
            // Left side
            moves |= 1ull << (m_location + 9);
        }

        getForwardMoves(moves, pieces);
    }
    else // Black
    {
        Bitboard whitePieces;

        m_board->board.getWhitePieces(whitePieces);
        // Possible attacks
        if (m_location % 8 < 7 and
            (whitePieces.value & (1ull << (m_location - 7) or m_location - 7 == m_board->enPassantSquare)))
        {
            // Right side
            moves |= 1ull << (m_location - 7);
        }
        if (m_location % 8 > 0 and
            (whitePieces.value & (1ull << (m_location - 9) or m_location - 9 == m_board->enPassantSquare)))
        {
            // Left side
            moves |= 1ull << (m_location - 9);
        }

        getForwardMoves(moves, pieces);
    }
}

void Pawn::getForwardMoves(uint64_t &moves, const Bitboard &pieces) const
{
    if (m_location > 55 or m_location < 8)
    {
        return; // Invalid location
    }

    if (m_color) // White
    {
        if (!(pieces.value & (0b1ull << m_location + 8)))
        {
            // Single square move
            moves |= 1ull << (m_location + 8);

            // Double square move
            if (m_location < 16) // On the second rank
            {
                if (!(pieces.value & (0b1ull << m_location + 16)))
                {
                    moves |= 1ull << (m_location + 16);
                }
            }
        }
    }
    else
    {
        if (!(pieces.value & (0b1ull << m_location - 8)))
        {
            // Single square move
            moves |= 1ull << (m_location - 8);

            // Double square move
            if (m_location > 48) // On the second rank
            {
                if (!(pieces.value & (0b1ull << m_location - 16)))
                {
                    moves |= 1ull << (m_location - 16);
                }
            }
        }
    }
}
