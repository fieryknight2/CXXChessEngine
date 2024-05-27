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

// Definitions for convienience
#define EMPTY 0

/** Classic bitboard. One 64-bit integer representing boolean conditions for chess board */
typedef uint64_t bitboard;

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
    bitboard whiteAttacks = EMPTY;
    /** Bitboard representation of all attacks for black pieces */
    bitboard blackAttacks = EMPTY;

    /** 64-bit representation of all locations of the pieces
     *
     * 64-bit representation of all locations of the pieces
     * Order is: White (pawns, knights, bishops, rooks, queens, kings)
     *           Black (pawns, knights, bishops, rooks, queens, kings)
     */
    bitboard pieces[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    /** Stored location of the king */
    uint16_t kingLoc = -1;
    /** Representing the side to move and castling rights */
    uint16_t boardInfo = 0xf; // All castling rights enabled
    // 0xff represents no en passant square, otherwise it represents the square, 2 bits will be wasted
    /** Single char representing the en passant square */
    uint16_t enPassantSquare = 0;

    bool createFromFEN(const std::string &fen, int *halfMoveClock = nullptr, int *fullMoveClock = nullptr);
    [[nodiscard]] std::string getFEN(int halfMoveClock = 0, int fullMoveClock = 0) const;
    void printBoard() const;
};

#endif // BOARD_REP_H
