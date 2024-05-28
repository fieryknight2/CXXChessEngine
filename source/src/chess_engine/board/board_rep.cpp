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

#include <exception>
#include <iostream>
#include <sstream>
#include <string>

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
 */
void Board::createFromFEN(const std::string &fen, int *halfMoveClock, int *fullMoveClock)
{
    // Reset the board
    for (int i = 0; i < 12; ++i)
    {
        pieces[i] = 0;
    }

    int i = 0; // We need the leftover value
    int r = 0, c = 0;
    for (; i < fen.size(); ++i)
    {
        if (fen[i] == ' ')
        {
            break;
        }

        if (fen[i] == '/')
        {
            ++r;
            c = 0;
            continue;
        }
        if (c > 7 or r > 7) // file index out of bounds
        {
            throw std::exception("Ran out of bounds while processing FEN");
        }


        if (fen[i] >= '0' and fen[i] <= '9')
        {
            c += fen[i] - '0' - 1;
            continue;
        }

        // 8 * r + c is the index, so shift 1 bit that much to write the bit
        uint64_t shift = 0b1 << (8 * r + c);
        switch (fen[i])
        {
            case 'p':
                pieces[0] |= shift;
                break;
            case 'n':
                pieces[1] |= shift;
                break;
            case 'b':
                pieces[2] |= shift;
                break;
            case 'r':
                pieces[3] |= shift;
                break;
            case 'q':
                pieces[4] |= shift;
                break;
            case 'k':
                pieces[5] |= shift;
                break;
            case 'P':
                pieces[6] |= shift;
                break;
            case 'N':
                pieces[7] |= shift;
                break;
            case 'B':
                pieces[8] |= shift;
                break;
            case 'R':
                pieces[9] |= shift;
                break;
            case 'Q':
                pieces[10] |= shift;
                break;
            case 'K':
                pieces[11] |= shift;
                break;
            default:
                throw std::exception(("Invalid piece " + std::to_string(fen[i]) + "in FEN").c_str());
        }
    }

    // Process the rest of the information
}

/** Get the FEN string for the board
 *
 * See documentation for createFromFEN for how the FEN string is formatted.
 * This function will return all the information about the board in a simple string.
 *
 * @param halfMoveClock Value of the half move clock
 * @param fullMoveClock Value of the full move clock
 * @return String representation of the board
 */
std::string Board::getFEN(int halfMoveClock, int fullMoveClock) const { return ""; }


/** Get the a visible representation of the board
 *
 * This function will return a string of characters that represent the current
 * state of the board. The string will be 64 characters long.
 *
 * @return String representation of the board
 */
char *Board::getDisplayBoard() const
{
    auto *dBoard = new char[64];
    for (int i = 0; i < 64; dBoard[i++] = '*')
        ; // Fill the board with empty squares

    // Generate display board
    for (int i = 0; i < 12; ++i)
    {
        for (int j = 0; j < 64; ++j)
        {
            // 1 << j is the bit that represents the square
            uint masked = pieces[i] & (0b1 << j); // Apply the bit mask
            if (masked >> j) // Get the value of the bit
            {
                switch (i)
                {
                    case 0: // First element is white pawns
                        dBoard[j] = 'P';
                        break;
                    case 1: // Second element is white knights
                        dBoard[j] = 'N';
                        break;
                    case 2: // Third element is white bishops
                        dBoard[j] = 'B';
                        break;
                    case 3: // Fourth element is white rooks
                        dBoard[j] = 'R';
                        break;
                    case 4: // Fifth element is white queens
                        dBoard[j] = 'Q';
                        break;
                    case 5: // Sixth element is white king
                        dBoard[j] = 'K';
                        break;
                    case 6: // Seventh element is black pawns
                        dBoard[j] = 'p';
                        break;
                    case 7: // Eighth element is black knights
                        dBoard[j] = 'n';
                        break;
                    case 8: // Ninth element is black bishops
                        dBoard[j] = 'b';
                        break;
                    case 9: // Tenth element is black rooks
                        dBoard[j] = 'r';
                        break;
                    case 10: // Eleventh element is black queens
                        dBoard[j] = 'q';
                        break;
                    case 11: // Twelfth element is black king
                        dBoard[j] = 'k';
                        break;
                    default: // This is impossible
                        break;
                }
            }
        }
    }

    return dBoard;
}

/** Print the board to the console
 *
 * This function will print the board to the console in a human readable format.
 */
void Board::printBoard() const
{
    const char *dBoard = getDisplayBoard();

    // Display files on top and bottom
    std::cout << "  a b c d e f g h  " << std::endl;

    for (int i = 7; i >= 0; --i) // Rank
    {
        std::cout << i + 1 << " ";

        for (int j = 0; j < 8; ++j) // File
        {
            std::cout << dBoard[(i * 8) + j];
            std::cout << " ";
        }

        std::cout << std::endl;
    }

    std::cout << "  a b c d e f g h  " << std::endl;

    delete[] dBoard;
}

/** Move a piece from one location to another
 *
 * This function will move a piece from one location to another while also updating
 * anything referencing the old location.
 *
 * @param from Location of the piece to move
 * @param to Location to move the piece to
 * @param piece Which piece was moved
 */
void Board::movePiece(int from, int to, int piece) {}
