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
#pragma once


#include <cstdint>
#include "chess_board.h"
#include "simplelogger.hpp"


namespace chessengine::board
{

constexpr bool WHITE = true;
constexpr bool BLACK = false;

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
    uint64_t m_location;
    /* Boolean representation of the color of the piece, true for white, false for black */
    bool m_color;

    ChessBoard *m_board;

    /* References to the white and black kings */
    Piece *m_blackKing = nullptr;
    Piece *m_whiteKing = nullptr;

public:
    /** Constructor */
    Piece(bool color, ChessBoard *board, uint64_t location) :
        m_location(location), m_color(color), m_board(board)
    {
    }

    /** Destructor */
    virtual ~Piece() = default;

    // Getters
    /** Get the represented color of the piece */
    [[nodiscard]] bool getColor() const
    {
        return m_color;
    }

    /** Get the referenced boards that the piece is on */
    [[nodiscard]] ChessBoard *getBoard() const
    {
        return m_board;
    }

    /** Get the current location of the piece */
    [[nodiscard]] uint64_t getSquare() const
    {
        return m_location;
    }

    /** Get the current reference to the white/black king */
    [[nodiscard]] Piece *getKing(int color) const
    {
        return color ? m_whiteKing : m_blackKing;
    }

    /** Return if the piece is valid */
    [[nodiscard]] bool isValid() const
    {
        return m_location < 65;
    }

    void setKing(Piece *king)
    {
        if (king == nullptr)
            return;

        king->getColor() ? m_whiteKing = king : m_blackKing = king;
    }

    // Virtual methods
    /** Make a move on the board, to be overridden for special behavior */
    virtual void makeMove(int to)
    {
        m_location = to;
    }

    /** Get the type of the piece */
    [[nodiscard]] virtual char getType() const = 0;
    /** Retrieve all possible attacks for the piece */
    virtual void getAttacks(uint64_t &attacks) const = 0;
    /** Retrieve all possible legal moves for the piece */
    virtual void getLegalMoves(uint64_t &moves) const = 0;
};

} // namespace chessengine::board


