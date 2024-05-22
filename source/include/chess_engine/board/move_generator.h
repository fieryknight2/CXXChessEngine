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
 * legal_move_generator.h - Constants used in the program
 * @author Matthew Brown
 * @date 05/21/2024
*****************************************************************************/
#ifndef legal_move_generator_H
#define legal_move_generator_H

#include <stack>

void generate_legal_moves(std::stack<std::pair<int, int>>*, const int*, bool);
void generate_legal_moves(std::stack<int>*, const int*, int);

void legal_pawn_moves(std::stack<int>*, const int*, int, int=-1, int=-1);
void legal_knight_moves(std::stack<int>*, const int*, int, int=-1);
void legal_bishop_moves(std::stack<int>*, const int*, int, int=-1);
void legal_rook_moves(std::stack<int>*, const int*, int, int=-1);
void legal_queen_moves(std::stack<int>*, const int*, int, int=-1);
void legal_king_moves(std::stack<int>*, const int*, int, int=-1);

void get_moves(std::stack<int>*, const int*, int);

void get_pawn_moves(std::stack<int>*, const int*, int);
void get_knight_moves(std::stack<int>*, const int*, int);
void get_bishop_moves(std::stack<int>*, const int*, int);
void get_rook_moves(std::stack<int>*, const int*, int);
void get_queen_moves(std::stack<int>*, const int*, int);
void get_king_moves(std::stack<int>*, const int*, int);

void get_attacks(std::stack<int>*, int*, int);

void get_pawn_attacks(std::stack<int>*, bool, int);
void get_pawn_attacks(std::stack<int>*, const int*, int);
void get_knight_attacks(std::stack<int>*, int);
void get_bishop_attacks(std::stack<int>*, const int*, int);
void get_rook_attacks(std::stack<int>*, const int*, int);
void get_queen_attacks(std::stack<int>*, const int*, int);
void get_king_attacks(std::stack<int>*, int);

#endif // legal_move_generator_H
