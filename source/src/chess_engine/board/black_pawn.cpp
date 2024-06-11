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
 * black_pawn.cpp - Implementation of black pawn methods
 * @author Matthew Brown
 * @date 6/7/2024
 *****************************************************************************/
#include "chess_engine/board/pawn.h"

using namespace chessengine;
using namespace board;

void BlackPawn::getLegalMoves(uint64_t &moves) const {
    if (!m_board->board.genMoveInfo) {
        throw ChessError("Error: Move info not generated, cannot generate legal moves");
    }

    if (m_location < 8 or m_location > 55) {
        return;
    }

    unsigned int index = m_location;

    CHESS_ASSERT(m_blackKing != nullptr, "Error: Black king is null");

    // Direction between ranks: - for up, + for down          Same Column == Up or Down
    if (m_location / 8 > m_blackKing->getSquare() / 8 and m_location % 8 - m_blackKing->getSquare() % 8 == 0) {
        /* King is below the pawn,
           Pin direction can be from up */
        while (index < 56) // Not on the 8th rank
        {
            index += 8; // Move up 1 rank

            if (m_board->board.data[PieceLoc::WHITE_ROOK].value & (0b1ull << index) or
                m_board->board.data[PieceLoc::WHITE_QUEEN].value & (0b1ull << index)) {
                for (index = m_location; index > 7;) {
                    index -= 8;

                    if (m_board->board.allPieces.value & (0b1ull << index) and
                        !(m_board->board.data[PieceLoc::BLACK_KING].value & (0b1ull << index))) {
                        // Pawn can't be pinned
                        getAllMoves(moves);
                        return;
                    }
                    if (m_board->board.data[PieceLoc::BLACK_KING].value & (0b1ull << index)) {
                        // Pinned
                        break;
                    }
                }

                // White piece is pinning
                // No attacks are possible, but the pawn can move forward
                getForwardMoves(moves);
                return;
            }

            if (m_board->board.allPieces.value & (0b1ull << index)) {
                // Piece that does not pin has gotten in the way
                // All moves are possible
                getAllMoves(moves);
                return;
            }
        }
    } else if (m_location / 8 - m_blackKing->getSquare() / 8 < 0 and
               m_location % 8 - m_blackKing->getSquare() % 8 == 0) {
        /* King is above the pawn,
           Pin direction can be from down */
        while (index > 7) // Not on the 1st rank
        {
            index -= 8; // Move down 1 rank

            // Is pinned
            if (m_board->board.data[PieceLoc::WHITE_ROOK].value & (0b1ull << index) or
                m_board->board.data[PieceLoc::WHITE_QUEEN].value & (0b1ull << index)) {
                for (index = m_location; index < 56;) {
                    index += 8;

                    if (m_board->board.allPieces.value & (0b1ull << index) and
                        !(m_board->board.data[PieceLoc::BLACK_KING].value & (0b1ull << index))) {
                        // Pawn can't be pinned
                        getAllMoves(moves);
                        return;
                    }
                    if (m_board->board.data[PieceLoc::BLACK_KING].value & (0b1ull << index)) {
                        // Pinned
                        break;
                    }
                }

                // White piece is pinning
                // No attacks are possible, but the pawn can move forward
                getForwardMoves(moves);
                return;
            }

            if (m_board->board.allPieces.value & (0b1ull << index)) {
                // Piece that does not pin has gotten in the way
                // All moves are possible
                getAllMoves(moves);
                return;
            }
        }
    }

    // Same rank                                               Direction between columns: - for right, + for left
    else if (m_location / 8 == m_blackKing->getSquare() / 8 and m_location % 8 - m_blackKing->getSquare() % 8 < 0) {
        /** King is on the right of the pawn,
         * Pin direction can be from left */
        while (index % 8 < 7) {
            ++index; // Move left 1 column

            if (m_board->board.data[PieceLoc::WHITE_ROOK].value & (0b1ull << index) or
                m_board->board.data[PieceLoc::WHITE_QUEEN].value & (0b1ull << index)) {
                for (index = m_location; index % 8 > 0;) {
                    --index;

                    if (m_board->board.allPieces.value & (0b1ull << index) and
                        !(m_board->board.data[PieceLoc::BLACK_KING].value & (0b1ull << index))) {
                        // Pawn can't be pinned
                        getAllMoves(moves);
                        return;
                    }
                    if (m_board->board.data[PieceLoc::BLACK_KING].value & (0b1ull << index)) {
                        // Pinned
                        break;
                    }
                }

                // White piece is pinning from the side, no moves are possible
                return;
            }

            if (m_board->board.allPieces.value & (0b1ull << index)) {
                // No pin, all moves are possible
                getAllMoves(moves);
                return;
            }
        }
    } else if (m_location / 8 - m_blackKing->getSquare() / 8 == 0 and m_location % 8 > m_blackKing->getSquare() % 8) {
        /** King is on the left of the pawn,
         * Pin direction can be from right */
        while (index % 8 > 0) {
            --index; // Move right 1 column

            if (m_board->board.data[PieceLoc::WHITE_ROOK].value & (0b1ull << index) or
                m_board->board.data[PieceLoc::WHITE_QUEEN].value & (0b1ull << index)) {
                for (index = m_location; index % 8 < 7;) {
                    ++index;

                    if (m_board->board.allPieces.value & (0b1ull << index) and
                        !(m_board->board.data[PieceLoc::BLACK_KING].value & (0b1ull << index))) {
                        // Pawn can't be pinned
                        getAllMoves(moves);
                        return;
                    }
                    if (m_board->board.data[PieceLoc::BLACK_KING].value & (0b1ull << index)) {
                        // Pinned
                        break;
                    }
                }

                // White piece is pinning from the side, no moves are possible
                return;
            }

            if (m_board->board.allPieces.value & (0b1ull << index)) {
                // No pin, all moves are possible
                getAllMoves(moves);
                return;
            }
        }
    }

    // Diagonal moves
    // Moving from the top left to the bottom right
    else if ((m_location / 8 - m_blackKing->getSquare() / 8) == (m_location % 8 - m_blackKing->getSquare() % 8)) {
        // Right is positive
        if (m_location % 8 < m_blackKing->getSquare() % 8) {
            // Pin has to come from bottom right
            while (index % 8 > 0 and index > 7) {
                index -= 9;

                if (m_board->board.data[PieceLoc::WHITE_BISHOP].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::WHITE_QUEEN].value & (0b1ull << index)) {
                    for (index = m_location; index % 8 < 7 and index < 56;) {
                        index += 9;

                        if (m_board->board.allPieces.value & (0b1ull << index) and
                            !(m_board->board.data[PieceLoc::BLACK_KING].value & (0b1ull << index))) {
                            // Pawn can't be pinned
                            getAllMoves(moves);
                            return;
                        }
                        if (m_board->board.data[PieceLoc::BLACK_KING].value & (0b1ull << index)) {
                            // Pinned
                            break;
                        }
                    }

                    // Pinned, only possible move is a capture to the bottom left
                    if (m_location % 8 < 7 and (m_board->board.whitePieces.value & (0b1ull << m_location - 9) or
                                                m_location - 9 == m_board->enPassantSquare)) {
                        moves |= 1ull << (m_location - 9);
                    }

                    return;
                }

                if (m_board->board.allPieces.value & (0b1ull << index)) {
                    // No pin, all moves are possible
                    getAllMoves(moves);
                    return;
                }
            }
        } else {
            // Pin has to come from top left
            while (index % 8 < 7 and index < 56) {
                index += 9;

                if (m_board->board.data[PieceLoc::WHITE_BISHOP].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::WHITE_QUEEN].value & (0b1ull << index)) {
                    for (index = m_location; index % 8 > 7 and index > 7;) {
                        index -= 9;

                        if (m_board->board.allPieces.value & (0b1ull << index) and
                            !(m_board->board.data[PieceLoc::BLACK_KING].value & (0b1ull << index))) {
                            // Pawn can't be pinned
                            getAllMoves(moves);
                            return;
                        }
                        if (m_board->board.data[PieceLoc::BLACK_KING].value & (0b1ull << index)) {
                            // Pinned
                            break;
                        }
                    }

                    // Pinned, only possible move is a capture to the bottom left
                    if (m_location % 8 < 7 and (m_board->board.whitePieces.value & (0b1ull << m_location - 9) or
                                                m_location - 9 == m_board->enPassantSquare)) {
                        moves |= 1ull << (m_location - 9);
                    }

                    return;
                }

                if (m_board->board.allPieces.value & (0b1ull << index)) {
                    // No pin, all moves are possible
                    getAllMoves(moves);
                    return;
                }
            }
        }
    }
    // Moving from the bottom left to the top right
    else if ((m_location / 8 - m_blackKing->getSquare() / 8) == -(m_location % 8 - m_blackKing->getSquare() % 8)) {
        // Right is positive
        if (m_location % 8 > m_blackKing->getSquare() % 8) {
            // Pin has to come from bottom left
            while (index % 8 < 7 and index > 7) {
                index -= 7;

                if (m_board->board.data[PieceLoc::WHITE_BISHOP].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::WHITE_QUEEN].value & (0b1ull << index)) {
                    for (index = m_location; index % 8 > 0 and index < 56;) {
                        index += 7;

                        if (m_board->board.allPieces.value & (0b1ull << index) and
                            !(m_board->board.data[PieceLoc::BLACK_KING].value & (0b1ull << index))) {
                            // Pawn can't be pinned
                            getAllMoves(moves);
                            return;
                        }
                        if (m_board->board.data[PieceLoc::BLACK_KING].value & (0b1ull << index)) {
                            // Pinned
                            break;
                        }
                    }

                    if (m_location % 8 < 7 and (m_board->board.whitePieces.value & (0b1ull << m_location - 7) or
                                                m_location - 7 == m_board->enPassantSquare)) {
                        moves |= 1ull << (m_location - 7);
                    }

                    return;
                }

                if (m_board->board.allPieces.value & (0b1ull << index)) {
                    // No pin, all moves are possible
                    getAllMoves(moves);
                    return;
                }
            }
        } else {
            // Pin has to come from top right
            while (index % 8 > 0 and index < 56) {
                index += 7;

                if (m_board->board.data[PieceLoc::WHITE_BISHOP].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::WHITE_QUEEN].value & (0b1ull << index)) {
                    for (index = m_location; index % 8 < 7 and index > 7;) {
                        index -= 7;

                        if (m_board->board.allPieces.value & (0b1ull << index) and
                            !(m_board->board.data[PieceLoc::BLACK_KING].value & (0b1ull << index))) {
                            // Pawn can't be pinned
                            getAllMoves(moves);
                            return;
                        }
                        if (m_board->board.data[PieceLoc::BLACK_KING].value & (0b1ull << index)) {
                            // Pinned
                            break;
                        }
                    }

                    // Pinned, only possible move is a capture to the bottom left
                    if (m_location % 8 < 7 and (m_board->board.whitePieces.value & (0b1ull << m_location - 7) or
                                                m_location - 7 == m_board->enPassantSquare)) {
                        moves |= 1ull << (m_location - 7);
                    }

                    return;
                }

                if (m_board->board.allPieces.value & (0b1ull << index)) {
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

/** Get the possible attacks for the piece
 *
 * @param attacks Pointer to a 64-bit integer to store the legal attacks
 */
void BlackPawn::getAttacks(uint64_t &attacks) const {
    if (m_location > 55 or m_location < 8) {
        return;
    }

    if (m_location % 8 > 0) {
        // Left side
        attacks |= 1ull << (m_location - 7);
    }
    if (m_location % 8 < 7) {
        // Right side
        attacks |= 1ull << (m_location - 9);
    }
}

void BlackPawn::getAllMoves(uint64_t &moves) const {
    if (m_location > 55 or m_location < 8) {
        return; // Invalid location
    }

    // Possible attacks
    if (m_location % 8 < 7 and
        (m_board->board.whitePieces.value & (1ull << (m_location - 7)) or m_location - 7 == m_board->enPassantSquare)) {
        // Right side
        moves |= 1ull << (m_location - 7);
    }
    if (m_location % 8 > 0 and
        (m_board->board.whitePieces.value & (1ull << (m_location - 9)) or m_location - 9 == m_board->enPassantSquare)) {
        // Left side
        moves |= 1ull << (m_location - 9);
    }

    getForwardMoves(moves);
}

void BlackPawn::getForwardMoves(uint64_t &moves) const {
    if (m_location > 55 or m_location < 8) {
        return; // Invalid location
    }

    if (!(m_board->board.allPieces.value & (0b1ull << m_location - 8))) {
        // Single square move
        moves |= 1ull << (m_location - 8);

        // Double square move
        if (m_location > 48) // On the second rank
        {
            if (!(m_board->board.allPieces.value & (0b1ull << m_location - 16))) {
                moves |= 1ull << (m_location - 16);
            }
        }
    }
}
