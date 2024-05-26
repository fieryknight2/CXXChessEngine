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
bool Board::createFromFEN(const std::string &fen, int *halfMoveClock, int *fullMoveClock)
{
    // Reset the board
    for (int i = 0; i < 32; ++i)
    {
        board[i] = 0;
    }

    // Get the board info
    int r = 7, c = -1;
    int i = 0; // We need the final result of the index
    for (; i < fen.size(); i++)
    {
        c++;
        if (fen[i] == ' ')
        {
            break; // Finished with board info
        }

        if (fen[i] == '/')
        {
            c = -1;
            r--; // Decrement the row counter
            continue;
        }

        if (r < 0 or c > 7)
        {
            // Something went wrong
            return false;
        }

        if (fen[i] > '0' and fen[i] < '9')
        {
            c += fen[i] - '0' - 1;
            continue;
        }

        if (r * 4 + c / 2 >= 32)
        {
            throw std::runtime_error("Ran out of bounds while creating board from FEN");
        }

        // Everything else:
        if (c % 2 == 0) // First square
        {
            switch (fen[i])
            {
                case 'p':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_A) | PIECE_BLACK_PAWN << 4;
                    break;
                case 'n':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_A) | PIECE_BLACK_KNIGHT << 4;
                    break;
                case 'b':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_A) | PIECE_BLACK_BISHOP << 4;
                    break;
                case 'r':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_A) | PIECE_BLACK_ROOK << 4;
                    break;
                case 'q':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_A) | PIECE_BLACK_QUEEN << 4;
                    break;
                case 'k':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_A) | PIECE_BLACK_KING << 4;
                    break;
                case 'P':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_A) | PIECE_WHITE_PAWN << 4;
                    break;
                case 'N':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_A) | PIECE_WHITE_KNIGHT << 4;
                    break;
                case 'B':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_A) | PIECE_WHITE_BISHOP << 4;
                    break;
                case 'R':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_A) | PIECE_WHITE_ROOK << 4;
                    break;
                case 'Q':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_A) | PIECE_WHITE_QUEEN << 4;
                    break;
                case 'K':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_A) | PIECE_WHITE_KING << 4;
                    break;
                default:
                    break; // Something went wrong
            }
        }
        else // Second square
        {
            switch (fen[i])
            {
                case 'p':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_B) | PIECE_BLACK_PAWN;
                    break;
                case 'n':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_B) | PIECE_BLACK_KNIGHT;
                    break;
                case 'b':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_B) | PIECE_BLACK_BISHOP;
                    break;
                case 'r':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_B) | PIECE_BLACK_ROOK;
                    break;
                case 'q':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_B) | PIECE_BLACK_QUEEN;
                    break;
                case 'k':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_B) | PIECE_BLACK_KING;
                    break;
                case 'P':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_B) | PIECE_WHITE_PAWN;
                    break;
                case 'N':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_B) | PIECE_WHITE_KNIGHT;
                    break;
                case 'B':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_B) | PIECE_WHITE_BISHOP;
                    break;
                case 'R':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_B) | PIECE_WHITE_ROOK;
                    break;
                case 'Q':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_B) | PIECE_WHITE_QUEEN;
                    break;
                case 'K':
                    board[r * 4 + c / 2] |= (board[r * 4 + c / 2] & SQUARE_B) | PIECE_WHITE_KING;
                    break;
                default:
                    break; // Something went wrong
            }
        }
    }

    // Set the board information
    if (fen.size() <= ++i)
    {
        return false;
    }

    if (fen[i] == 'w' or fen[i] == '-')
    {
        boardInfo = 0b00010000;
    }
    else
    {
        boardInfo = 0;
    }
    i += 2;
    ;

    for (int j = 0; j < 4; ++j, ++i)
    {
        if (fen.size() <= i)
        {
            return false;
        }

        if (fen[i] == 'k')
        {
            boardInfo |= (boardInfo & CASTLING_BLACK_KING_SIDE) | CASTLING_BLACK_KING_SIDE;
        }
        else if (fen[i] == 'q')
        {
            boardInfo |= (boardInfo & CASTLING_BLACK_QUEEN_SIDE) | CASTLING_BLACK_QUEEN_SIDE;
        }
        else if (fen[i] == 'K')
        {
            boardInfo |= (boardInfo & CASTLING_WHITE_KING_SIDE) | CASTLING_WHITE_KING_SIDE;
        }
        else if (fen[i] == 'Q')
        {
            boardInfo |= (boardInfo & CASTLING_WHITE_QUEEN_SIDE) | CASTLING_WHITE_QUEEN_SIDE;
        }

        if (fen[i] == ' ')
        {
            break;
        }
        if (j == 3)
        {
            ++i;
        }
    }

    if (fen[i] == '-')
    {
    }
    else if (fen[i] >= 'a' and fen[i] <= 'h')
    {
        enPassantSquare = (fen[i] - 'a') << 4;
    }

    if (fen.size() <= ++i)
    {
        return false;
    }

    if (fen[i] >= '1' and fen[i] < '9')
    {
        enPassantSquare |= (fen[i] - '1') & 0x0f;
        ++i;
    }


    if (fen.size() <= ++i)
    {
        return false;
    }

    std::stringstream ss;
    while (fen[i] >= '0' and fen[i] <= '9')
    {
        ss << fen[i];

        ++i;
        if (fen.size() <= i)
        {
            return false;
        }
    }
    if (halfMoveClock)
    {
        (*halfMoveClock) = std::stoi(ss.str());
    }

    if (fen.size() <= ++i)
    {
        return false;
    }

    ss = std::stringstream();
    while (fen.size() >= i and fen[i] > '0' and fen[i] < '9')
    {
        ss << fen[i];
        ++i;
    }
    if (fullMoveClock)
    {
        (*fullMoveClock) = std::stoi(ss.str());
    }

    return true;
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
std::string Board::getFEN(int halfMoveClock, int fullMoveClock) const
{
    // Start with the board info
    std::stringstream fen;
    int emptySquares = 0;
    for (int i = 7; i >= 0; --i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if ((i * 4) + j >= 32)
            {
                throw std::runtime_error("Ran out of bounds while creating board from FEN");
            }

            // first square is 0b0000xxxx (bitmask is SQUARE_A)
            if ((board[(i * 4) + j] & SQUARE_A) == EMPTY)
            {
                ++emptySquares;
            }
            else if (emptySquares > 0)
            {
                fen << emptySquares;
                emptySquares = 0;
            }

            if ((board[(i * 4) + j] & SQUARE_B) == EMPTY)
            {
                ++emptySquares;
            }
            else if (emptySquares > 0)
            {
                fen << emptySquares;
                emptySquares = 0;
            }

            // Check for piece values
            switch ((board[(i * 4) + j] & SQUARE_A) >> 4)
            {
                case PIECE_WHITE_PAWN:
                    fen << 'P';
                    break;
                case PIECE_WHITE_KNIGHT:
                    fen << 'N';
                    break;
                case PIECE_WHITE_BISHOP:
                    fen << 'B';
                    break;
                case PIECE_WHITE_ROOK:
                    fen << 'R';
                    break;
                case PIECE_WHITE_QUEEN:
                    fen << 'Q';
                    break;
                case PIECE_WHITE_KING:
                    fen << 'K';
                    break;
                case PIECE_BLACK_PAWN:
                    fen << 'p';
                    break;
                case PIECE_BLACK_KNIGHT:
                    fen << 'n';
                    break;
                case PIECE_BLACK_BISHOP:
                    fen << 'b';
                    break;
                case PIECE_BLACK_ROOK:
                    fen << 'r';
                    break;
                case PIECE_BLACK_QUEEN:
                    fen << 'q';
                    break;
                case PIECE_BLACK_KING:
                    fen << 'k';
                    break;
                default:
                    break;
            }

            switch (board[(i * 4) + j] & SQUARE_B)
            {
                case PIECE_WHITE_PAWN:
                    fen << 'P';
                    break;
                case PIECE_WHITE_KNIGHT:
                    fen << 'N';
                    break;
                case PIECE_WHITE_BISHOP:
                    fen << 'B';
                    break;
                case PIECE_WHITE_ROOK:
                    fen << 'R';
                    break;
                case PIECE_WHITE_QUEEN:
                    fen << 'Q';
                    break;
                case PIECE_WHITE_KING:
                    fen << 'K';
                    break;
                case PIECE_BLACK_PAWN:
                    fen << 'p';
                    break;
                case PIECE_BLACK_KNIGHT:
                    fen << 'n';
                    break;
                case PIECE_BLACK_BISHOP:
                    fen << 'b';
                    break;
                case PIECE_BLACK_ROOK:
                    fen << 'r';
                    break;
                case PIECE_BLACK_QUEEN:
                    fen << 'q';
                    break;
                case PIECE_BLACK_KING:
                    fen << 'k';
                    break;
                default:
                    break;
            }
        }

        if (emptySquares > 0)
        {
            fen << emptySquares;
        }
        emptySquares = 0;

        if (i)
        {
            fen << '/';
        }
    }


    fen << ' ';
    if (((boardInfo & SIDE_TO_MOVE_MASK) >> 4) == 1)
    {
        fen << 'w';
    }
    else
    {
        fen << 'b';
    }
    fen << ' ';

    const uint8_t castlingRights = boardInfo & 0b00001111;
    if (castlingRights == 0)
    {
        fen << '-';
    }
    if (castlingRights & CASTLING_WHITE_KING_SIDE)
    {
        fen << 'K';
    }
    if (castlingRights & CASTLING_WHITE_QUEEN_SIDE)
    {
        fen << 'Q';
    }
    if (castlingRights & CASTLING_BLACK_KING_SIDE)
    {
        fen << 'k';
    }
    if (castlingRights & CASTLING_BLACK_QUEEN_SIDE)
    {
        fen << 'q';
    }

    fen << ' ';

    if (enPassantSquare == 0xff)
    {
        fen << '-';
    }
    else
    {
        // Get the en passant square
        switch ((enPassantSquare & 0xf0) >> 4)
        {
            case 0x00:
                fen << 'a';
                break;
            case 0x01:
                fen << 'b';
                break;
            case 0x02:
                fen << 'c';
                break;
            case 0x03:
                fen << 'd';
                break;
            case 0x04:
                fen << 'e';
                break;
            case 0x05:
                fen << 'f';
                break;
            case 0x06:
                fen << 'g';
                break;
            case 0x07:
                fen << 'h';
                break;
            default:
                // Error
                break;
        }
        switch (enPassantSquare & 0x0f)
        {
            case 0x00:
                fen << 1;
                break;
            case 0x01:
                fen << 2;
                break;
            case 0x02:
                fen << 3;
                break;
            case 0x03:
                fen << 4;
                break;
            case 0x04:
                fen << 5;
                break;
            case 0x05:
                fen << 6;
                break;
            case 0x06:
                fen << 7;
                break;
            case 0x07:
                fen << 8;
                break;
            default:
                // Error
                break;
        }
    }

    // Use arguments for halfMoveClock and fullMoveClock
    fen << ' ' << halfMoveClock << ' ' << fullMoveClock;

    return fen.str();
}


/** Print the board to the console
 *
 * This function will print the board to the console in a human readable format.
 */
void Board::printBoard() const
{
    // Display files on top and bottom
    std::cout << "  a b c d e f g h  " << std::endl;

    for (int i = 7; i >= 0; --i)
    {
        std::cout << i + 1 << " ";

        for (int j = 0; j < 4; j++) // Each row only contains 4 chars
        {
            if (i * j >= 32 or (i * 4) + j >= 32)
            {
                throw std::runtime_error("Ran out of bounds while printing board");
            }

            // first square is 0bxxxx0000 (bitmask is SQUARE_A)
            switch ((board[(i * 4) + j] & SQUARE_A) >> 4)
            {
                case PIECE_WHITE_PAWN:
                    std::cout << "P";
                    break;
                case PIECE_WHITE_KNIGHT:
                    std::cout << "N";
                    break;
                case PIECE_WHITE_BISHOP:
                    std::cout << "B";
                    break;
                case PIECE_WHITE_ROOK:
                    std::cout << "R";
                    break;
                case PIECE_WHITE_QUEEN:
                    std::cout << "Q";
                    break;
                case PIECE_WHITE_KING:
                    std::cout << "K";
                    break;
                case PIECE_BLACK_PAWN:
                    std::cout << "p";
                    break;
                case PIECE_BLACK_KNIGHT:
                    std::cout << "n";
                    break;
                case PIECE_BLACK_BISHOP:
                    std::cout << "b";
                    break;
                case PIECE_BLACK_ROOK:
                    std::cout << "r";
                    break;
                case PIECE_BLACK_QUEEN:
                    std::cout << "q";
                    break;
                case PIECE_BLACK_KING:
                    std::cout << "k";
                    break;
                default: // Empty
                    std::cout << "*";
            }

            std::cout << " ";

            // second square is 0b0000xxxx (bitmask is SQUARE_B)
            switch (board[(i * 4) + j] & SQUARE_B)
            {
                case PIECE_WHITE_PAWN:
                    std::cout << "P";
                    break;
                case PIECE_WHITE_KNIGHT:
                    std::cout << "N";
                    break;
                case PIECE_WHITE_BISHOP:
                    std::cout << "B";
                    break;
                case PIECE_WHITE_ROOK:
                    std::cout << "R";
                    break;
                case PIECE_WHITE_QUEEN:
                    std::cout << "Q";
                    break;
                case PIECE_WHITE_KING:
                    std::cout << "K";
                    break;
                case PIECE_BLACK_PAWN:
                    std::cout << "p";
                    break;
                case PIECE_BLACK_KNIGHT:
                    std::cout << "n";
                    break;
                case PIECE_BLACK_BISHOP:
                    std::cout << "b";
                    break;
                case PIECE_BLACK_ROOK:
                    std::cout << "r";
                    break;
                case PIECE_BLACK_QUEEN:
                    std::cout << "q";
                    break;
                case PIECE_BLACK_KING:
                    std::cout << "k";
                    break;
                default:
                    std::cout << "*"; // Empty
            }

            std::cout << " ";
        }

        std::cout << std::endl;
    }

    std::cout << "  a b c d e f g h  " << std::endl;
}
