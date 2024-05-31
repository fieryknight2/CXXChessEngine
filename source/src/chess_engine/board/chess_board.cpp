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
#include "chess_engine/board/chess_board.h"
#include "chess_engine/ChessError.h"
#include "chess_engine/board/bishop.h"
#include "chess_engine/board/king.h"
#include "chess_engine/board/knight.h"
#include "chess_engine/board/pawn.h"
#include "chess_engine/board/queen.h"
#include "chess_engine/board/rook.h"

#include <iostream>
#include <sstream>
#include <string>

/** Get a square from a string in algebraic notation
 *
 * @param square String representation of the square
 * @return Square number
 */
uint64_t ChessBoard::getSquareFromAlgebraic(const std::string &square)
{
    if (square.size() != 2)
    {
        throw ChessError("Invalid square size");
    }

    uint64_t squareNumber;

    // First character is the file
    if (square[0] >= 'a' and square[0] <= 'h')
    {
        squareNumber = square[0] - 'a';
    }
    else
    {
        throw ChessError("Invalid square notation");
    }

    // Second character is the rank
    if (square[1] >= '1' and square[1] <= '8')
    {
        squareNumber += 8 * (square[1] - '1');
    }
    else
    {
        throw ChessError("Invalid square notation");
    }

    return squareNumber;
}

std::string ChessBoard::toAlgebraic(uint64_t square)
{
    if (square >= 64)
    {
        throw ChessError("Invalid square");
    }
    std::string squareString;

    // First character is the file
    // Sometimes I hate C++ and linting...
    squareString = static_cast<char>(square % 8) + 'a'; // NOLINT(*-narrowing-conversions)

    // Second character is the rank
    squareString += static_cast<char>(square / 8) + '1'; // NOLINT(*-narrowing-conversions)

    return squareString;
}

/** Reset the board to the starting position */
void ChessBoard::resetBoard()
{
    // Reset the board
    if (pieceCount)
    {
        pieceCount = 0;
        delete[] pieceInformation;
        pieceInformation = nullptr;
    }

    for (auto &board: m_board.data)
    {
        board.value = 0;
    }

    for (bool &castlingRight: castlingRights)
    {
        castlingRight = false;
    }

    enPassantSquare = 65; // No en passant square
    whiteToMove = true;
}

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
void ChessBoard::createFromFEN(const std::string &fen, int *halfMoveClock, int *fullMoveClock)
{
    // First reset the board
    resetBoard();

    // Process the FEN string
    uint64_t i = 0; // We need the leftover value
    int r = 7, c = 0;
    for (; i < fen.size(); ++i)
    {
        if (fen[i] == ' ')
        {
            break;
        }

        if (fen[i] == '/')
        {
            --r;
            c = 0;
            continue;
        }
        if (c > 7 or r < 0) // file index out of bounds
        {
            throw ChessError("Ran out of bounds while processing FEN");
        }


        if (fen[i] > '0' and fen[i] < '9')
        {
            c += fen[i] - '0';
            continue;
        }

        // (8 * r) + c is the index, so shift 1 bit that much to write the bit
        uint64_t shifted = 0b1ull << (8 * r + c);
        switch (fen[i])
        {
            case 'P':
                m_board.data[0].value |= shifted;
                break;
            case 'N':
                m_board.data[1].value |= shifted;
                break;
            case 'B':
                m_board.data[2].value |= shifted;
                break;
            case 'R':
                m_board.data[3].value |= shifted;
                break;
            case 'Q':
                m_board.data[4].value |= shifted;
                break;
            case 'K':
                m_board.data[5].value |= shifted;
                break;
            case 'p':
                m_board.data[6].value |= shifted;
                break;
            case 'n':
                m_board.data[7].value |= shifted;
                break;
            case 'b':
                m_board.data[8].value |= shifted;
                break;
            case 'r':
                m_board.data[9].value |= shifted;
                break;
            case 'q':
                m_board.data[10].value |= shifted;
                break;
            case 'k':
                m_board.data[11].value |= shifted;
                break;
            default:
                throw ChessError("Invalid piece " + std::to_string(fen[i]) + " in FEN");
        }
        ++c;
    }

    pieceCount = m_board.getTotalValue().getBitCount();
    pieceInformation = new Piece *[pieceCount];
    for (int j = 0, elem = 0; j < 12; ++j)
    {
        for (int k = 0; k < 64; ++k)
        {
            if (m_board.data[j].value & (0b1ull << k))
            {
                switch (j)
                {
                    case 0: // First element is white pawns
                        pieceInformation[elem] = new Pawn(WHITE, &m_board, k);
                        break;
                    case 1: // Second element is white knights
                        pieceInformation[elem] = new Knight(WHITE, &m_board, k);
                        break;
                    case 2: // Third element is white bishops
                        pieceInformation[elem] = new Bishop(WHITE, &m_board, k);
                        break;
                    case 3: // Fourth element is white rooks
                        pieceInformation[elem] = new Rook(WHITE, &m_board, k);
                        break;
                    case 4: // Fifth element is white queens
                        pieceInformation[elem] = new Queen(WHITE, &m_board, k);
                        break;
                    case 5: // Sixth element is white king
                        pieceInformation[elem] = new King(WHITE, &m_board, k);
                        m_whiteKing = pieceInformation[elem];
                        break;
                    case 6: // Seventh element is black pawns
                        pieceInformation[elem] = new Pawn(BLACK, &m_board, k);
                        break;
                    case 7: // Eighth element is black knights
                        pieceInformation[elem] = new Knight(BLACK, &m_board, k);
                        break;
                    case 8: // Ninth element is black bishops
                        pieceInformation[elem] = new Bishop(BLACK, &m_board, k);
                        break;
                    case 9: // Tenth element is black rooks
                        pieceInformation[elem] = new Rook(BLACK, &m_board, k);
                        break;
                    case 10: // Eleventh element is black queens
                        pieceInformation[elem] = new Queen(BLACK, &m_board, k);
                        break;
                    case 11: // Twelfth element is black king
                        pieceInformation[elem] = new King(BLACK, &m_board, k);
                        m_blackKing = pieceInformation[elem];
                        break;
                    default:
                        break; // This is impossible
                }

                ++elem;
            }
        }
    }
    for (int j = 0; j < pieceCount; ++j)
    {
        if (pieceInformation[j]->getColor() == WHITE)
        {
            pieceInformation[j]->setKing(m_whiteKing);
        }
        else // Black
        {
            pieceInformation[j]->setKing(m_blackKing);
        }
    }


    // Process the rest of the information
    if (fen.size() <= ++i)
    {
        throw ChessError("Invalid FEN string length");
    }

    switch (fen[i])
    {
        case 'w':
            whiteToMove = true;
            break;
        case 'b':
            whiteToMove = false;
            break;
        default:
            throw ChessError("Invalid player turn in FEN string");
    }

    i += 2;
    if (fen.size() <= i)
    {
        throw ChessError("Invalid FEN string length while parsing castling rights");
    }
    if (fen[i] != '-')
    {
        // Castling rights
        for (int j = 0; j < 4; ++j, ++i)
        {
            if (fen.size() <= i)
            {
                throw ChessError("Invalid FEN string length while parsing castling rights");
            }

            if (fen[i] == ' ' and j != 0)
            {
                if (fen[i] == '-')
                {
                    ++i;
                }

                break;
            }
            if (fen[i] == ' ' and j == 0)
            {
                throw ChessError("Invalid white space in FEN string");
            }

            switch (fen[i])
            {
                case 'K':
                    castlingRights[0] = true;
                    break;
                case 'Q':
                    castlingRights[1] = true;
                    break;
                case 'k':
                    castlingRights[2] = true;
                    break;
                case 'q':
                    castlingRights[3] = true;
                    break;
                default:
                    throw ChessError("Invalid castling option in FEN string");
            }
        }
    }
    else
    {
        ++i;
    }

    // En passant square
    ++i;
    if (fen.size() <= i)
    {
        throw ChessError("Invalid FEN string length while parsing en passant square");
    }

    if (fen[i] == '-')
    {
        enPassantSquare = 65; // No en passant square
    }
    else if (fen.size() < i + 1)
    {
        throw ChessError("Invalid FEN string length while parsing en passant square");
    }
    else
    {
        enPassantSquare = getSquareFromAlgebraic(fen.substr(i, 2));
        ++i;
    }

    ++i;
    // Half move clock and full move clock
    if (fen.size() <= ++i)
    {
        throw ChessError("Invalid FEN string length while parsing half move clock");
    }
    while (fen[i] >= '0' and fen[i] <= '9')
    {
        if (halfMoveClock)
        {
            *halfMoveClock = std::stoi(fen.substr(i, 1));
        }
        ++i;
        if (fen.size() <= i)
        {
            throw ChessError("Invalid FEN string length while parsing half move clock");
        }
    }

    ++i;
    if (fen.size() <= i)
    {
        throw ChessError("Invalid FEN string length while parsing full move clock");
    }
    while (fen[i] >= '0' and fen[i] <= '9')
    {
        if (fullMoveClock)
        {
            *fullMoveClock = std::stoi(fen.substr(i, 1));
        }

        ++i;
        if (fen.size() <= i)
        {
            return; // We're done
        }
    }

    // something went wrong
    throw ChessError("Invalid full move clock in FEN string");
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
std::string ChessBoard::getFEN(int halfMoveClock, int fullMoveClock) const
{
    std::string fen;

    // First process the board
    std::string board = getDisplayBoard();
    for (int i = 7; i >= 0; --i)
    {
        int emptySquares = 0;
        for (int j = 0; j < 8; ++j)
        {
            if (board[i * 8 + j] == '*')
            {
                ++emptySquares;
            }
            else
            {
                if (emptySquares)
                {
                    fen += std::to_string(emptySquares);
                    emptySquares = 0;
                }

                fen += board[i * 8 + j];
            }
        }

        if (emptySquares)
        {
            fen += std::to_string(emptySquares);
        }
        if (i != 0)
        {
            fen += "/";
        }
    }

    // Who to move?
    if (whiteToMove)
    {
        fen += " w ";
    }
    else
    {
        fen += " b ";
    }

    // Castling rights
    if (!(castlingRights[0] + castlingRights[1] + castlingRights[2] + castlingRights[3]))
    {
        fen += "-";
    }
    else
    {
        if (castlingRights[0])
        {
            fen += "K";
        }
        if (castlingRights[1])
        {
            fen += "Q";
        }
        if (castlingRights[2])
        {
            fen += "k";
        }
        if (castlingRights[3])
        {
            fen += "q";
        }
    }

    // En passant square
    if (enPassantSquare == 65)
    {
        fen += " - ";
    }
    else
    {
        fen += " " + toAlgebraic(enPassantSquare) + " ";
    }

    // Half move clock and full move clock
    fen += std::to_string(halfMoveClock) + " " + std::to_string(fullMoveClock);

    return fen;
}


/** Get the a visible representation of the board
 *
 * This function will return a string of characters that represent the current
 * state of the board. The string will be 64 characters long.
 *
 * @return String representation of the board
 */
char *ChessBoard::getDisplayBoard() const
{
    auto *dBoard = new char[64];
    for (int i = 0; i < 64; dBoard[i++] = '*')
        ; // Fill the board with empty squares

    // Generate display board
    for (int i = 0; i < 12; ++i)
    {
        for (uint64_t j = 0; j < 64; ++j)
        {
            // 1 << j is the bit that represents the square
            // Initialize and apply the bit mask
            if (uint64_t val = m_board.data[i].value & (0b1ull << j); val >> j)
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
void ChessBoard::printBoard() const
{
    const char *dBoard = getDisplayBoard();

    // Display files on top and bottom
    std::cout << "  a b c d e f g h  " << std::endl;

    for (int i = 7; i >= 0; --i) // Rank
    {
        std::cout << i + 1 << " ";

        for (int j = 0; j < 8; ++j) // File
        {
            std::cout << dBoard[i * 8 + j];
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
void ChessBoard::movePiece(int from, int to, int piece) {}

/** Retrieve a pointer to the white king
 *
 * @return Pointer to the white king
 */
Piece *ChessBoard::getWhiteKing() const { return m_whiteKing; }

/** Retrieve a pointer to the black king
 *
 * @return Pointer to the black king
 */
Piece *ChessBoard::getBlackKing() const { return m_blackKing; }
