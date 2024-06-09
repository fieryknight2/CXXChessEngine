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
 * bitboard.h - <Brief description>
 * @author Matthew Brown
 * @date 05/28/2024
 *****************************************************************************/
#ifndef bitboard_H
#define bitboard_H

#include <cstdint>

/** Locations of the pieces in the board's array
 *
 *
 * @author Matthew Brown
 * @date 6/6/2024
 */
enum PieceLoc {
    WHITE_PAWN = 0,
    WHITE_KNIGHT = 1,
    WHITE_BISHOP = 2,
    WHITE_ROOK = 3,
    WHITE_QUEEN = 4,
    WHITE_KING = 5,
    BLACK_PAWN = 6,
    BLACK_KNIGHT = 7,
    BLACK_BISHOP = 8,
    BLACK_ROOK = 9,
    BLACK_QUEEN = 10,
    BLACK_KING = 11
};

/** Classic bitboard.
 *
 * One 64-bit integer representing boolean conditions for chess board
 * @author Matthew Brown
 * @date 5/28/2024
 */
struct Bitboard {
    /** Constructors */
    explicit Bitboard(uint64_t nvalue) : value(nvalue) {}
    Bitboard() : value(0) {}

    /** Stored value of the bitboard */
    uint64_t value;

    /** Count all the bits in the bitboard */
    [[nodiscard]] int getBitCount() const;

    /** Assignment operator for simplicity */
    Bitboard &operator=(const uint64_t &nvalue) {
        value = nvalue;
        return *this;
    }
};

struct Board {
    /* 64-bit representation of all locations of the pieces
     *
     * 64-bit representation of all locations of the pieces
     * Order is: White (pawns, knights, bishops, rooks, queens, kings)
     *           Black (pawns, knights, bishops, rooks, queens, kings)
     */
    Bitboard data[12];

    /* Legal move generation information */
    bool genMoveInfo = false;
    Bitboard whiteAttacks;
    Bitboard blackAttacks;
    Bitboard allPieces;
    Bitboard whitePieces;
    Bitboard blackPieces;

    /* Methods */
    [[nodiscard]] Bitboard getTotalValue() const;
    void getTotalValue(Bitboard &total) const;

    void getWhitePieces(Bitboard &pieces) const;
    void getBlackPieces(Bitboard &pieces) const;

    void moveMade();
    uint64_t getWhiteAttacks(Bitboard &whiteAttacks);
    uint64_t getBlackAttacks(Bitboard &blackAttacks);
};

#endif // bitboard_H
