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
 * queen.cpp - <Brief description>
 * @author Matthew Brown
 * @date 05/27/2024
 *****************************************************************************/
#include "chess_engine/board/queen.h"

/** Make a move on the board
 *
 * @param to Location to move the piece to
 */
void Queen::makeMove(int to) {
    // TODO: Implement
}

/** Get the type of the piece
 *
 * @return Type of the piece
 */
char Queen::getType() const { return PieceType::QUEEN; }

/** Get the legal moves for the piece
 *
 * @param moves Pointer to a 64-bit integer to store the legal moves
 */
void Queen::getLegalMoves(uint64_t &moves) const {
    uint64_t totalValue = m_board->board.getTotalValue().value;
    Bitboard myPieces;
    Bitboard otherPieces;

    int pieceOffset = m_color ? 6 : 0;

    if (m_color) {
        m_board->board.getWhitePieces(myPieces);
        m_board->board.getBlackPieces(otherPieces);
    } else {
        m_board->board.getBlackPieces(myPieces);
        m_board->board.getWhitePieces(otherPieces);
    }

    // Process possible moves
    unsigned int index = m_location;

    // Up and Down
    if (m_location / 8 > m_blackKing->getSquare() / 8 and m_location % 8 == m_blackKing->getSquare() % 8) {
        // King is below the pawn
        while (index < 56) {
            index += 8;

            // Check for potential pin
            if (m_board->board.data[PieceLoc::BLACK_ROOK + pieceOffset].value & (0b1ull << index) or
                m_board->board.data[PieceLoc::BLACK_QUEEN + pieceOffset].value & (0b1ull << index)) {
                for (index = m_location; index > 7;) {
                    index -= 8;

                    if (totalValue & (0b1ull << index) and
                        !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))) {
                        // No pin
                        getAllMoves(moves, totalValue, myPieces.value);
                        return;
                    }
                    if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)) {
                        // Pinned
                        break;
                    }


                    // Pinned
                    getBottomTopMoves(moves, totalValue, myPieces.value);
                    return;
                }

                if (totalValue & (0b1ull << index)) {
                    // Piece that does not pin has gotten in the way
                    // All moves are possible
                    getAllMoves(moves, totalValue, myPieces.value);
                    return;
                }
            }
        }
    } else if (m_location / 8 - m_blackKing->getSquare() / 8 < 0 and
               m_location % 8 - m_blackKing->getSquare() % 8 == 0) {
        // King is above the pawn
        while (index > 7) {
            index -= 8;

            // Check for potential pin
            if (m_board->board.data[PieceLoc::BLACK_ROOK + pieceOffset].value & (0b1ull << index) or
                m_board->board.data[PieceLoc::BLACK_QUEEN + pieceOffset].value & (0b1ull << index)) {
                for (index = m_location; index < 56;) {
                    index += 8;

                    if (totalValue & (0b1ull << index) and
                        !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))) {
                        // No pin
                        getAllMoves(moves, totalValue, myPieces.value);
                        return;
                    }
                    if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)) {
                        // Pinned
                        break;
                    }
                }

                // Pinned
                getBottomTopMoves(moves, totalValue, myPieces.value);
                return;
            }

            if (totalValue & (0b1ull << index)) {
                // Piece that does not pin has gotten in the way
                // All moves are possible
                getAllMoves(moves, totalValue, myPieces.value);
                return;
            }
        }
    }

    // Left and Right
    else if (m_location / 8 == m_blackKing->getSquare() / 8 and m_location % 8 < m_blackKing->getSquare() % 8) {
        // King is on the left of the pawn
        while (index % 8 < 7) {
            ++index;

            // Check for potential pin
            if (m_board->board.data[PieceLoc::BLACK_ROOK + pieceOffset].value & (0b1ull << index) or
                m_board->board.data[PieceLoc::BLACK_QUEEN + pieceOffset].value & (0b1ull << index)) {
                for (index = m_location; index % 8 > 0;) {
                    --index;

                    if (totalValue & (0b1ull << index) and
                        !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))) {
                        // No pin
                        getAllMoves(moves, totalValue, myPieces.value);
                        return;
                    }
                    if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)) {
                        // Pinned
                        break;
                    }
                }

                // Pinned
                getLeftRightMoves(moves, totalValue, myPieces.value);
                return;
            }

            if (totalValue & (0b1ull << index)) {
                // Piece that does not pin has gotten in the way
                // All moves are possible
                getAllMoves(moves, totalValue, myPieces.value);
                return;
            }
        }
    } else if (m_location / 8 - m_blackKing->getSquare() / 8 == 0 and m_location % 8 > m_blackKing->getSquare() % 8) {
        // King is to the right of the pawn
        while (index % 8 > 0) {
            --index;

            // Check for potential pin
            if (m_board->board.data[PieceLoc::BLACK_ROOK + pieceOffset].value & (0b1ull << index) or
                m_board->board.data[PieceLoc::BLACK_QUEEN + pieceOffset].value & (0b1ull << index)) {
                for (index = m_location; index % 8 < 7;) {
                    ++index;

                    if (totalValue & (0b1ull << index) and
                        !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))) {
                        // No pin
                        getAllMoves(moves, totalValue, myPieces.value);
                        return;
                    }
                    if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)) {
                        // Pinned
                        break;
                    }
                }

                // Pinned
                getLeftRightMoves(moves, totalValue, myPieces.value);
                return;
            }

            if (totalValue & (0b1ull << index)) {
                // Piece that does not pin has gotten in the way
                // All moves are possible
                getAllMoves(moves, totalValue, myPieces.value);
                return;
            }
        }
    }

    // Diagonal
    // Top left to the bottom right
    else if ((m_location / 8 - m_blackKing->getSquare() / 8) == (m_location % 8 - m_blackKing->getSquare() % 8)) {
        // King is to the bottom right
        if (m_location % 8 < m_blackKing->getSquare() % 8) {
            while (index % 8 > 0 and index > 7) {
                index -= 9;

                // Check for potential pin
                if (m_board->board.data[PieceLoc::BLACK_ROOK + pieceOffset].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::BLACK_QUEEN + pieceOffset].value & (0b1ull << index)) {
                    for (index = m_location; index % 8 < 7 and index < 56;) {
                        index += 9;

                        if (totalValue & (0b1ull << index) and
                            !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))) {
                            // No pin
                            getAllMoves(moves, totalValue, myPieces.value);
                            return;
                        }
                        if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)) {
                            // Pinned
                            break;
                        }
                    }

                    // Pinned, queen can only move in the direction of the pin
                    getBottomRightTopLeftMoves(moves, totalValue, myPieces.value);
                    return;
                }

                if (totalValue & (0b1ull << index)) {
                    // Piece that does not pin has gotten in the way
                    // All moves are possible

                    getAllMoves(moves, totalValue, myPieces.value);
                    return;
                }
            }
        }
        // King is to the top left
        else {
            while (index % 8 < 7 and index < 56) {
                index += 9;

                // Check for potential pin
                if (m_board->board.data[PieceLoc::BLACK_ROOK + pieceOffset].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::BLACK_QUEEN + pieceOffset].value & (0b1ull << index)) {
                    for (index = m_location; index % 8 > 0 and index > 7;) {
                        index -= 9;

                        if (totalValue & (0b1ull << index) and
                            !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))) {
                            // No pin
                            getAllMoves(moves, totalValue, myPieces.value);
                            return;
                        }
                        if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)) {
                            // Pinned
                            break;
                        }
                    }

                    // Pinned
                    getBottomRightTopLeftMoves(moves, totalValue, myPieces.value);
                    return;
                }

                if (totalValue & (0b1ull << index)) {
                    // Piece that does not pin has gotten in the way
                    // All moves are possible
                    getAllMoves(moves, totalValue, myPieces.value);
                    return;
                }
            }
        }
    }
    // Top right to the bottom left
    else if ((m_location / 8 - m_blackKing->getSquare() / 8) == -(m_location % 8 - m_blackKing->getSquare() % 8)) {
        // King is to the bottom left
        if (m_location % 8 > m_blackKing->getSquare() % 8) {
            while (index % 8 < 7 and index > 7) {
                index -= 7;

                // Check for potential pin
                if (m_board->board.data[PieceLoc::BLACK_ROOK + pieceOffset].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::BLACK_QUEEN + pieceOffset].value & (0b1ull << index)) {
                    for (index = m_location; index % 8 > 0 and index < 56;) {
                        index += 7;

                        if (totalValue & (0b1ull << index) and
                            !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))) {
                            // No pin
                            getAllMoves(moves, totalValue, myPieces.value);
                            return;
                        }
                        if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)) {
                            // Pinned
                            break;
                        }
                    }

                    // Pinned, bishop can only move if pinned ot the side
                    getBottomLeftTopRightMoves(moves, totalValue, myPieces.value);
                    return;
                }

                if (totalValue & (0b1ull << index)) {
                    // Piece that does not pin has gotten in the way
                    // All moves are possible
                    getAllMoves(moves, totalValue, myPieces.value);
                    return;
                }
            }
        }
        // King is to the top right
        else {
            while (index % 8 > 0 and index < 56) {
                index -= 7;

                // Check for potential pin
                if (m_board->board.data[PieceLoc::BLACK_ROOK + pieceOffset].value & (0b1ull << index) or
                    m_board->board.data[PieceLoc::BLACK_QUEEN + pieceOffset].value & (0b1ull << index)) {
                    for (index = m_location; index % 8 < 7 and index > 7;) {
                        index += 7;

                        if (totalValue & (0b1ull << index) and
                            !(m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index))) {
                            // No pin
                            getAllMoves(moves, totalValue, myPieces.value);
                            return;
                        }
                        if (m_board->board.data[PieceLoc::BLACK_KING - pieceOffset].value & (0b1ull << index)) {
                            // Pinned
                            break;
                        }
                    }

                    // Pinned, bishop can only move if pinned ot the side
                    getBottomLeftTopRightMoves(moves, totalValue, myPieces.value);
                    return;
                }

                if (totalValue & (0b1ull << index)) {
                    // Piece that does not pin has gotten in the way
                    // All moves are possible
                    getAllMoves(moves, totalValue, myPieces.value);
                    return;
                }
            }
        }
    }

    // No pins, all possible moves:
    getAllMoves(moves, totalValue, myPieces.value);
}

/** Get the possible attacks for the piece
 *
 * @param attacks Pointer to a 64-bit integer to store the legal attacks
 */
void Queen::getAttacks(uint64_t &attacks) const {
    unsigned int index = m_location;
    uint64_t totalValue = m_board->board.getTotalValue().value;

    // Rook Code
    while (index < 56) {
        // Top
        index += 8;
        attacks |= 1ull << index;

        if (totalValue & (1ull << index)) {
            break;
        }
    }

    index = m_location;
    while (index % 8 < 7) {
        // Left
        index += 1;
        attacks |= 1ull << index;

        if (totalValue & (1ull << index)) {
            break;
        }
    }

    index = m_location;
    while (index % 8 > 0) {
        // Right
        index -= 1;
        attacks |= 1ull << index;

        if (totalValue & (1ull << index)) {
            break;
        }
    }

    index = m_location;
    while (index >= 8) {
        // Bottom
        index -= 8;
        attacks |= 1ull << index;

        if (totalValue & (1ull << index)) {
            break;
        }
    }

    // Bishop Code
    index = m_location;
    while (index > 7 and index % 8 > 0) {
        // Bottom Right
        index -= 9;
        attacks |= 1ull << index;

        if (totalValue & (1ull << index)) {
            break;
        }
    }

    index = m_location;
    while (index > 7 and index % 8 < 7) {
        // Bottom Left
        index -= 7;
        attacks |= 1ull << index;

        if (totalValue & (1ull << index)) {
            break;
        }
    }

    index = m_location;
    while (index < 57 and index % 8 > 0) {
        // Top Left
        index += 7;
        attacks |= 1ull << index;

        if (totalValue & (1ull << index)) {
            break;
        }
    }

    index = m_location;
    while (index < 57 and index % 8 < 7) {
        // Top Right
        index += 9;
        attacks |= 1ull << index;

        if (totalValue & (1ull << index)) {
            break;
        }
    }
}

void Queen::getLeftRightMoves(uint64_t &moves, uint64_t &totalValue, uint64_t &myPieces) const {
    unsigned int index = m_location;

    while (index % 8 < 7) {
        // Left
        index += 1;

        if (!(myPieces & (1ull << index))) {
            moves |= 1ull << index;
        }

        if (totalValue & (1ull << index)) {
            break;
        }
    }

    index = m_location;
    while (index % 8 > 0) {
        // Right
        index -= 1;

        if (!(myPieces & (1ull << index))) {
            moves |= 1ull << index;
        }

        if (totalValue & (1ull << index)) {
            break;
        }
    }
}

void Queen::getBottomTopMoves(uint64_t &moves, uint64_t &totalValue, uint64_t &myPieces) const {
    unsigned int index = m_location;

    while (index < 56) {
        // Top
        index += 8;

        if (!(myPieces & (1ull << index))) {
            moves |= 1ull << index;
        }

        if (totalValue & (1ull << index)) {
            break;
        }
    }

    index = m_location;
    while (index > 7) {
        // Bottom
        index -= 8;

        if (!(myPieces & (1ull << index))) {
            moves |= 1ull << index;
        }

        if (totalValue & (1ull << index)) {
            break;
        }
    }
}

void Queen::getBottomLeftTopRightMoves(uint64_t &moves, uint64_t &totalValue, uint64_t &myPieces) const {
    unsigned int index = m_location;

    while (index > 7 and index % 8 < 7) {
        // Bottom Left
        index -= 7;

        if (!(myPieces & (1ull << index))) {
            moves |= 1ull << index;
        }

        if (totalValue & (1ull << index)) {
            break;
        }
    }

    index = m_location;
    while (index < 56 and index % 8 > 0) {
        // Top Right
        index += 7;

        if (!(myPieces & (1ull << index))) {
            moves |= 1ull << index;
        }

        if (totalValue & (1ull << index)) {
            break;
        }
    }
}

void Queen::getBottomRightTopLeftMoves(uint64_t &moves, uint64_t &totalValue, uint64_t &myPieces) const {
    unsigned int index = m_location;

    while (index > 7 and index % 8 > 0) {
        // Bottom Right
        index -= 9;


        if (!(myPieces & (1ull << index))) {
            moves |= 1ull << index;
        }

        if (totalValue & (1ull << index)) {
            break;
        }
    }

    index = m_location;
    while (index < 56 and index % 8 < 7) {
        // Top Left
        index += 9;

        if (!(myPieces & (1ull << index))) {
            moves |= 1ull << index;
        }

        if (totalValue & (1ull << index)) {
            break;
        }
    }
}

void Queen::getAllMoves(uint64_t &moves, uint64_t &totalValue, uint64_t &myPieces) const {
    getLeftRightMoves(moves, totalValue, myPieces);
    getBottomTopMoves(moves, totalValue, myPieces);
    getBottomLeftTopRightMoves(moves, totalValue, myPieces);
    getBottomRightTopLeftMoves(moves, totalValue, myPieces);
}
