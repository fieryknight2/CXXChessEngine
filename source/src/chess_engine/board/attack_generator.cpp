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
 * attack_generator.cpp - Constants used in the program
 * @author Matthew Brown
 * @date 05/21/2024
*****************************************************************************/
#include "chess_engine/board/move_generator.h"

std::stack<std::pair<int, int>> get_attacks(char* board, int piece) {
 /** Generates all legal moves on the board for the given piece
 *
 * Determines which function to call based on the piece type, it may
 * be more efficient to call the appropriate function directly.
 *
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @return All possible legal moves for the given piece
 */

 return std::stack<std::pair<int, int>>{};
}


std::stack<int> get_pawn_attacks(char* board, int piece) {
 /** Generates all legal moves on the board for the given pawn
 *
 * See documentation for legal_pawn_moves() for more information
 * Pawn attacks don't depend on the board so slight time save
 *
 * @param piece The piece to generate legal moves for
 * @return All possible legal moves for the given piece
 */

 return std::stack<int>{};
}

std::stack<int> get_knight_attacks(int piece) {
 /** Generates all legal moves on the board for the given knight
 *
 * The knight only attacks the 8 possible squares and doesn't require the
 * board to be passed in.
 *
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @return All possible legal moves for the given piece
 */

 return std::stack<int>{};
}


std::stack<int> get_bishop_attacks(char* board, int piece) {
 /** Generates all legal moves on the board for the given bishop
 *
 * See documentation for legal_bishop_moves() for more information
 *
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @return All possible legal moves for the given piece
 */

 return std::stack<int>{};
}

std::stack<int> get_rook_attacks(char* board, int piece) {
 /** Generates all legal moves on the board for the given rook
 *
 * See documentation for legal_rook_moves() for more information
 *
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @return All possible legal moves for the given piece
 */

 return std::stack<int>{};
}

std::stack<int> get_queen_attacks(char* board, int piece) {
 /** Generates all legal moves on the board for the given queen
 *
 * See documentation for legal_queen_moves() for more information
 *
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @return All possible legal moves for the given piece
 */

 return std::stack<int>{};
}

std::stack<int> get_king_attacks(char* board, int piece) {
 /** Generates all legal moves on the board for the given king
 *
 * See documentation for legal_king_moves() for more information
 *
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @return All possible legal moves for the given piece
 */

 return std::stack<int>{};
}