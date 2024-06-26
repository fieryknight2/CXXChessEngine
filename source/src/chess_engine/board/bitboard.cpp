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
 * bitboard.cpp - <Brief description>
 * @author Matthew Brown
 * @date 05/28/2024
 *****************************************************************************/
#include "chess_engine/board/bitboard.h"

using namespace chessengine::board;

int Bitboard::getBitCount() const
{
    int count = 0;
    for (uint64_t i = 0; i < 64; ++i)
    {
        if (value & (0b1ull << i))
        {
            ++count;
        }
    }
    return count;
}

Bitboard Board::getTotalValue() const
{
    Bitboard total;

    for (auto &board: data)
    {
        total.value |= board.value;
    }

    return total;
}

void Board::getTotalValue(Bitboard &total) const
{
    for (auto &board: data)
    {
        total.value |= board.value;
    }
}

void Board::getWhitePieces(Bitboard &pieces) const
{
    pieces.value = data[0].value | data[1].value | data[2].value | data[3].value | data[4].value | data[5].value;
}

void Board::getBlackPieces(Bitboard &pieces) const
{
    pieces.value = data[6].value | data[7].value | data[8].value | data[9].value | data[10].value | data[11].value;
}

/* To be worked on in the future */
void Board::moveMade() { genMoveInfo = false; }
