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
 * move_generator.cpp - Constants used in the program
 * @author Matthew Brown
 * @date 05/21/2024
*****************************************************************************/
#include "chess_engine/board/move_generator.h"


/** Generates all legal moves on the board for the given piece
*
* Determines which function to call based on the piece type, it may
* be more efficient to call the appropriate function directly.
*
* @param moves Stack of moves to add to
* @param board List of all pieces and their locations on the board
* @param piece The piece to generate legal moves for
*/

void get_moves(std::stack<std::pair<int, int>>* moves, char* board, int piece) {
}


/** Generates all legal moves on the board for the given pawn
*
* See documentation for legal_pawn_moves() for more information
* This function returns all possible moves, and does not check for
* legality.
*
* @param moves Stack of moves to add to
* @param board List of all pieces and their locations on the board
* @param piece The piece to generate legal moves for
*/
void get_pawn_moves(std::stack<int>* moves, char* board, int piece) {
}


/** Generates all legal moves on the board for the given knight
*
* See documentation for legal_knight_moves() for more information
*
* @param moves Stack of moves to add to
* @param board List of all pieces and their locations on the board
* @param piece The piece to generate legal moves for
*/
void get_knight_moves(std::stack<int>* moves, char* board, int piece) {
}


/** Generates all legal moves on the board for the given bishop
*
* See documentation for legal_bishop_moves() for more information
*
* @param moves Stack of moves to add to
* @param board List of all pieces and their locations on the board
* @param piece The piece to generate legal moves for
*/
void get_bishop_moves(std::stack<int>* moves, char* board, int piece) {
}

/** Generates all legal moves on the board for the given rook
*
* See documentation for legal_rook_moves() for more information
*
* @param moves Stack of moves to add to
* @param board List of all pieces and their locations on the board
* @param piece The piece to generate legal moves for
*/
void get_rook_moves(std::stack<int>* moves, char* board, int piece) {
}

/** Generates all legal moves on the board for the given queen
*
* See documentation for legal_queen_moves() for more information
*
* @param moves Stack of moves to add to
* @param board List of all pieces and their locations on the board
* @param piece The piece to generate legal moves for
*/
void get_queen_moves(std::stack<int>* moves, char* board, int piece) {
}

/** Generates all legal moves on the board for the given king
*
* See documentation for legal_king_moves() for more information
*
* @param moves Stack of moves to add to
* @param board List of all pieces and their locations on the board
* @param piece The piece to generate legal moves for
*/
void get_king_moves(std::stack<int>* moves, char* board, int piece) {
}