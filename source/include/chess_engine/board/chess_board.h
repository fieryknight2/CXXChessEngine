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
 * board_rep.h - Definitions for a bitboard representation
 * @author Matthew Brown
 * @date 5/25/2024
 *****************************************************************************/
#ifndef BOARD_REP_H
#define BOARD_REP_H

#include <cstdint>
#include <string>

#include "chess_engine/board/bitboard.h"
#include "chess_engine/board/piece.h"

// Definitions for convienience
#define EMPTY 0

/** Board Representation
 *
 * This is a representation of a chess board using a combination of several methods.
 * The first method is a series of bitboards, each representing a piece.
 * The second method includes a piece representation
 *
 * @author Matthew Brown
 * @date 5/25/2024
 */
class ChessBoard
{
    /** Bitboard representation of all attacks for white pieces */
    Bitboard whiteAttacks{0};
    /** Bitboard representation of all attacks for black pieces */
    Bitboard blackAttacks{0};

    /** 64-bit representation of all locations of the pieces
     *
     * 64-bit representation of all locations of the pieces
     * Order is: White (pawns, knights, bishops, rooks, queens, kings)
     *           Black (pawns, knights, bishops, rooks, queens, kings)
     */
    Board m_board;

    /** Stored information on all pieces*/
    Piece **pieceInformation = nullptr;
    /** Number of pieces on the board */
    int pieceCount = 0;
    /** Pointer to the white king */
    Piece *m_whiteKing = nullptr;
    /** Pointer to the black king */
    Piece *m_blackKing = nullptr;

    /** Representing the castling rights
     *
     * Represents the castling rights for each side
     * Order represented is: White King
     *                       White Queen
     *                       Black King
     *                       Black Queen
     */
    bool castlingRights[4] = {true, true, true, true};

    /** Single char representing the en passant square */
    uint64_t enPassantSquare = 65; // No en passant square

    /** Boolean representing if white is to move */
    bool whiteToMove = true;

    static uint64_t getSquareFromAlgebraic(const std::string &square);
    static std::string toAlgebraic(uint64_t square);

    [[nodiscard]] char *getDisplayBoard() const;

public:
    // Access and creation methods
    void createFromFEN(const std::string &fen, int *halfMoveClock = nullptr,
                       int *fullMoveClock = nullptr) noexcept(false);
    [[nodiscard]] std::string getFEN(int halfMoveClock = 0, int fullMoveClock = 0) const;
    void printBoard() const;
    void resetBoard();

    // Movement methods
    void movePiece(int from, int to, int piece);

    // Getters
    [[nodiscard]] Piece *getWhiteKing() const;
    [[nodiscard]] Piece *getBlackKing() const;

    // Simple constructor
    ChessBoard() = default;
    // Simple destructor
    ~ChessBoard() = default;
};

#endif // BOARD_REP_H
