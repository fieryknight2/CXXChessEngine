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

#include "chess_engine/board/piece.h"

// Definitions for convienience
#define EMPTY 0

// Simple unsigned integer for my convenience
typedef uint64_t u64int;

/** Classic bitboard.
 *
 * One 64-bit integer representing boolean conditions for chess board
 * @author Matthew Brown
 * @date 5/28/2024
 */
struct Bitboard
{
    /** Constructors */
    explicit Bitboard(u64int nvalue) : value(nvalue) {}
    Bitboard() : value(0) {}

    /** Stored value of the bitboard */
    u64int value;

    /** Count all the bits in the bitboard */
    [[nodiscard]] int getBitCount() const;

    /** Assignment operator for simplicity */
    Bitboard &operator=(const u64int &nvalue)
    {
        value = nvalue;
        return *this;
    }
};

/** Board Representation
 *
 * This is a representation of a chess board using a combination of several methods.
 * The first method is a series of bitboards, each representing a piece.
 * The second method includes a piece representation
 *
 * @author Matthew Brown
 * @date 5/25/2024
 */
struct Board
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
    Bitboard pieces[12];

    /** Stored information on all pieces*/
    Piece *pieceInformation = nullptr;
    /** Number of pieces on the board */
    int pieceCount = 0;

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
    u64int enPassantSquare = 65; // No en passant square

    /** Boolean representing if white is to move */
    bool whiteToMove = true;

    static u64int getSquareFromAlgebraic(const std::string &square);
    static std::string toAlgebraic(u64int square);

    // Access and creation methods
    void createFromFEN(const std::string &fen, int *halfMoveClock = nullptr,
                       int *fullMoveClock = nullptr) noexcept(false);
    [[nodiscard]] std::string getFEN(int halfMoveClock = 0, int fullMoveClock = 0) const;
    [[nodiscard]] char *getDisplayBoard() const;
    void printBoard() const;
    void resetBoard();

    // Movement methods
    void movePiece(int from, int to, int piece);

    // Simple constructor
    Board()
    {
        for (auto &piece: pieces)
        {
            piece = EMPTY;
        }
    }
};

#endif // BOARD_REP_H
