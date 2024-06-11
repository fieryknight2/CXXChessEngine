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
 * pawn.h - <Brief description>
 * @author Matthew Brown
 * @date 05/27/2024
 *****************************************************************************/
#pragma once

#include "chess_engine/board/piece.h"

namespace chessengine
{

namespace board
{

/** Pawn class
 *
 * @author Matthew Brown
 * @date 05/28/2024
 */
class Pawn : public Piece
{
public:
    Pawn(bool color, ChessBoard *board, unsigned int location) : Piece(color, board, location) {}

    void makeMove(int to) override;
    [[nodiscard]] char getType() const override { return PieceType::PAWN; }
};

/** White pawn class
 *
 * @author Matthew Brown
 * @date 06/7/2024
 *
 */
class WhitePawn : public Pawn
{
public:
    WhitePawn(ChessBoard *board, unsigned int location) : Pawn(true, board, location) {}
    ~WhitePawn() override = default;

    void getAttacks(uint64_t &attacks) const override;
    void getLegalMoves(uint64_t &moves) const override;
    void getAllMoves(uint64_t &moves) const;
    void getForwardMoves(uint64_t &moves) const;
};

/** Black pawn class
 *
 * @author Matthew Brown
 * @date 06/7/2024
 */
class BlackPawn : public Pawn
{
public:
    BlackPawn(ChessBoard *board, unsigned int location) : Pawn(false, board, location) {}
    ~BlackPawn() override = default;

    void getAttacks(uint64_t &attacks) const override;
    void getLegalMoves(uint64_t &moves) const override;
    void getAllMoves(uint64_t &moves) const;
    void getForwardMoves(uint64_t &moves) const;
};

} // namespace board

} // namespace chessengine
