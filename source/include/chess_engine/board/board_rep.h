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
#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>
#include <string>

// Definitions for convienience
#define EMPTY 0

// Simple pieces
#define PIECE_WHITE_PAWN 0b0001
#define PIECE_WHITE_KNIGHT 0b0010
#define PIECE_WHITE_BISHOP 0b0011
#define PIECE_WHITE_ROOK 0b0100
#define PIECE_WHITE_QUEEN 0b0101
#define PIECE_WHITE_KING 0b0110

#define PIECE_BLACK_PAWN 0b1001
#define PIECE_BLACK_KNIGHT 0b1010
#define PIECE_BLACK_BISHOP 0b1011
#define PIECE_BLACK_ROOK 0b1100
#define PIECE_BLACK_QUEEN 0b1101
#define PIECE_BLACK_KING 0b1110

#define CASTLING_WHITE_KING_SIDE 0b1000
#define CASTLING_WHITE_QUEEN_SIDE 0b0100
#define CASTLING_BLACK_KING_SIDE 0b0010
#define CASTLING_BLACK_QUEEN_SIDE 0b0001

#define SIDE_TO_MOVE_MASK 0b00010000

#define SQUARE_A 0b11110000
#define SQUARE_B 0b00001111

// Representation is split into two parts, one square on each side
// Square 1: 0b0000 Square 2: 0b0000
/** Classic bitboard. One 64-bit integer representing boolean conditions for chess board */
typedef uint64_t bitboard;

/** My method for representing the chess board. Each element represents 2 squares */
typedef uint8_t boardRepSize;

/** Method for storing piece locations and types. Used in combination with bitboards */
typedef uint16_t pieceRepSize;

/** Board Representation
 *
 * This is a representation of a chess board using a combination of several methods.
 * The first method is a board of chars, each representing two squares.
 * The second method includes a piece representation
 *
 * @member whiteAttacks Bitboard representation of all attacks for white pieces
 * @member blackAttacks Bitboard representation of all attacks for black pieces
 * @member board Array of chars representing the board
 * @member whitePieces Array representing the white pieces and their locations
 * @member blackPieces Array representing the black pieces and their locations
 * @author Matthew Brown
 * @date 5/25/2024
 */
struct Board
{
    /* Helper bitboards for move generation
     */
    bitboard whiteAttacks = EMPTY;
    bitboard blackAttacks = EMPTY;

    /* Each element of the uint8_t array represents two squares.
     * The first square is 0x0f and the second is 0xf0
     * a1 is the first element of the array while h8 is the last
     */
    boardRepSize board[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Each element represents 2 squares

    /* Pieces are represented with a 0x0 00 0000 (1 bit wasted)
     * Where the first 4 bits is if the piece is captured, the second set is
     * the type of the piece, and the last 4 bits is the location of the piece. 1 bit is wasted
     *
     * List layout:
     * pppppppp rnbqkbnr
     */
    pieceRepSize whitePieces[16] = {};
    pieceRepSize blackPieces[16] = {};

    /* 3 bits will be ignored (0b000 - ignored) 0 0000
     * The first bit is the side to move, the last four bits are the castling rights
     * 0 is for black, 1 is for white
     */
    uint8_t boardInfo = 0b00011111; // 0x1f
    // 0xff represents no en passant square, otherwise it represents the square, 2 bits will be wasted
    uint8_t enPassantSquare = 0xff;

    bool createFromFEN(const std::string &fen, int *halfMoveClock = nullptr, int *fullMoveClock = nullptr);
    [[nodiscard]] std::string getFEN(int halfMoveClock = 0, int fullMoveClock = 0) const;
    void printBoard() const;
};

#endif // BITBOARD_H
