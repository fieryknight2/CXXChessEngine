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
 * board_rep.cpp - Implementation of board methods
 * @author Matthew Brown
 * @date 05/25/2024
 *****************************************************************************/
#include "chess_engine/board/board_rep.h"

#include <iostream>
#include <sstream>

/** Create a board from a FEN string
 *
 * A FEN string is an official standard for representing a chess board.
 * It is written in the following format:
 * rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
 * Where a letter indicates a piece and a number
 * indicates empty squares. Captial letters indicate white and lowercase represents
 * black. The w after the board indicates white to move. KQkq indicates castling rights
 * an optional square given in algebraic notation indicates an en passant square.
 * The final two numbers are the half move clock and full move clock.
 *
 * @param fen String representation of the board
 * @param halfMoveClock Optional pointer to an integer to store the half move clock
 * @param fullMoveClock Optional pointer to an integer to store the full move clock
 * @return True if the board was created successfully
 */
bool Board::createFromFEN(const std::string &fen, int *halfMoveClock, int *fullMoveClock) {}

/** Get the FEN string for the board
 *
 * See documentation for createFromFEN for how the FEN string is formatted.
 * This function will return all the information about the board in a simple string.
 *
 * @param halfMoveClock Value of the half move clock
 * @param fullMoveClock Value of the full move clock
 * @return String representation of the board
 */
std::string Board::getFEN(int halfMoveClock, int fullMoveClock) const {}


/** Print the board to the console
 *
 * This function will print the board to the console in a human readable format.
 */
void Board::printBoard() const {}
