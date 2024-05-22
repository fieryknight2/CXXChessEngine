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
 * constants.h - Constants used in the program
 * @author Matthew Brown
 * @date 5/21/2024
*****************************************************************************/
#ifndef constants_H
#define constants_H

enum PieceType {
    EMPTY = 0,
    PAWN = 1,
    KNIGHT = 2,
    BISHOP = 3,
    ROOK = 4,
    QUEEN = 5,
    KING = 6
};

enum ColorPieceType {
    WHITE_PAWN = PAWN,
    WHITE_KNIGHT = KNIGHT,
    WHITE_BISHOP = BISHOP,
    WHITE_ROOK = ROOK,
    WHITE_QUEEN = QUEEN,
    WHITE_KING = KING,
    BLACK_PAWN = -PAWN,
    BLACK_KNIGHT = -KNIGHT,
    BLACK_BISHOP = -BISHOP,
    BLACK_ROOK = -ROOK,
    BLACK_QUEEN = -QUEEN,
    BLACK_KING = -KING
};

#endif // constants_H
