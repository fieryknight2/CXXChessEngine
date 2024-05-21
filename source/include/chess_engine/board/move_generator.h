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

/** Generates all legal moves on the board for the given color
 *
 * Loops through every piece on the board and returns all possible
 * legal moves for the given color.
 *
 * @param board List of all pieces and their locations on the board
 * @param color The color of pieces to generate legal moves for
 * @return All possible legal moves for the given color
 */
std::stack<std::pair<int, int>> generate_legal_moves(char board[64], bool color);

/** Generates all legal moves on the board for the given piece
 *
 * Determines which function to call based on the piece type, it may
 * be more efficient to call the appropriate function directly.
 *
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @return All possible legal moves for the given piece
 */
std::stack<int> generate_legal_moves(char board[64], int piece);

/** Generate the legal moves for a given pawn
 *
 * The pawn can move forward one square if it is not blocked, and it can
 * capture an enemy piece one space forward to its left or right. It can also move
 * forward two spaces if on its starting square. Though it isn't handled here, a pawn
 * can also promote at the end of the board.
 *
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @param kingLoc The location of the King (optional)
 * @param enPassantSquare Square where en passant is possible (optional)
 * @return A stack of all legal moves for the given piece
 */
std::stack<int> legal_pawn_moves(char board[64], int piece, int kingLoc=-1, int enPassantSquare=-1);

/** Generate the legal moves for a given knight
 *
 * The knight can move in an L shape in any direction, jumping over
 * pieces as it goes.
 *
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @param kingLoc The location of the King (optional)
 * @return A stack of all legal moves for the given piece
 */
std::stack<int> legal_knight_moves(char board[64], int piece, int kingLoc=-1);

/** Generate the legal moves for a given bishop
 *
 * The bishop can move diagonally in all four directions
 *
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @param kingLoc The location of the King (optional)
 * @return A stack of all legal moves for the given piece
 */
std::stack<int> legal_bishop_moves(char board[64], int piece, int kingLoc=-1);
std::stack<int> legal_rook_moves(char board[64], int piece, int kingLoc=-1);
std::stack<int> legal_queen_moves(char board[64], int piece, int kingLoc=-1);
std::stack<int> legal_king_moves(char board[64], int piece, int kingLoc=-1);

std::stack<std::pair<int, int>> get_moves(char board[64], int piece);

std::stack<int> get_pawn_moves(char board[64], int piece);
std::stack<int> get_knight_moves(char board[64], int piece);
std::stack<int> get_bishop_moves(char board[64], int piece);
std::stack<int> get_rook_moves(char board[64], int piece);
std::stack<int> get_queen_moves(char board[64], int piece);
std::stack<int> get_king_moves(char board[64], int piece);

std::stack<std::pair<int, int>> get_attacks(char board[64], int piece);

std::stack<int> get_pawn_attacks(char board[64], int piece);
std::stack<int> get_knight_attacks(char board[64], int piece);
std::stack<int> get_bishop_attacks(char board[64], int piece);
std::stack<int> get_rook_attacks(char board[64], int piece);
std::stack<int> get_queen_attacks(char board[64], int piece);
std::stack<int> get_king_attacks(char board[64], int piece);

#endif // legal_move_generator_H
