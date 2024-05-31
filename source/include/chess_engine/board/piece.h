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
 * piece.h - A definition of a chess piece and sub types
 * @author Matthew Brown
 * @date 05/27/2024
 *****************************************************************************/
#ifndef piece_H
#define piece_H

#ifndef WHITE

#define WHITE true
#define BLACK false

#endif // WHITE

#include <cstdint>
#include "bitboard.h"

/** Possible types of chess pieces
 *
 */
enum PieceType
{
    PAWN = 'p',
    KNIGHT = 'n',
    BISHOP = 'b',
    ROOK = 'r',
    QUEEN = 'q',
    KING = 'k'
};

/** Representation of a chess piece
 *
 * @author Matthew Brown
 * @date 05/27/2024
 */
class Piece
{
protected:
    /** Location of the piece on the board */
    unsigned int m_location;
    /** Boolean representation of the color of the piece, true for white, false for black */
    bool m_color = WHITE;
    /** Reference to the board that the piece is on */
    Board *m_board = nullptr;
    Piece *m_king = nullptr;

public:
    // Constructor
    Piece(bool color, Board *boards, unsigned int location) : m_location(location), m_color(color), m_board(boards) {}
    virtual ~Piece() = default;

    // Getters
    [[nodiscard]] int getColor() const { return m_color; }
    [[nodiscard]] Board *getBoards() const { return m_board; }

    // Virtual methods
    virtual void makeMove(int to) { m_location = to; }
    [[nodiscard]] virtual char getType() const = 0;
    virtual void getAttacks(uint64_t &attacks) const = 0;
    virtual void getLegalMoves(uint64_t &moves) const = 0;

    // Setters
    void setKing(Piece *king) { m_king = king; }
    [[nodiscard]] Piece *getKing() const { return m_king; }
};

#endif // piece_H
