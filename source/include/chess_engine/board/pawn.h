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
#ifndef pawn_H
#define pawn_H

#include "chess_engine/board/piece.h"

/** Pawn class
 *
 * @author Matthew Brown
 * @date 05/28/2024
 */
class Pawn final : public Piece
{
public:
    Pawn(bool color, ChessBoard *board, unsigned int location) : Piece(color, board, location) {}
    ~Pawn() override = default;

    void makeMove(int to) override;
    [[nodiscard]] char getType() const override;
    void getAttacks(uint64_t &attacks) const override;
    void getLegalMoves(uint64_t &moves) const override;
};

#endif // pawn_H
