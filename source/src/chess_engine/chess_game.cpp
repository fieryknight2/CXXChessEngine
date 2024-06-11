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
 * chess_game.cpp - Implementation of chess game methods
 * @author Matthew Brown
 * @date 06/02/2024
 *****************************************************************************/
#include "chess_engine/chess_game.h"

#include "chess_engine/board/bishop.h"
#include "chess_engine/board/king.h"
#include "chess_engine/board/knight.h"
#include "chess_engine/board/pawn.h"
#include "chess_engine/board/queen.h"
#include "chess_engine/board/rook.h"

using namespace chessengine;

// For debugging
#include <iostream>

/** Get the number of pieces in the game
 *
 * @return The number of pieces in the game
 */
uint64_t ChessGame::getPieceCount() const { return m_pieceInformation.size(); }

/** Get the pieces in the game
 *
 * @return The pieces in the game
 */
std::vector<board::Piece *> ChessGame::getPieces() const { return m_pieceInformation; }

/** Get a piece from the game
 *
 * @param square The square of the piece
 * @return The piece at the square
 */
board::Piece *ChessGame::getPiece(uint64_t square) const
{
    if (m_pieceInformation.empty())
    {
        return nullptr;
    }

    for (int j = 0; j < m_pieceInformation.size(); ++j)
    {
        if (m_pieceInformation[j]->getSquare() == square)
        {
            return m_pieceInformation[j];
        }
    }

    return nullptr;
}

/** Generate all possible attacks for the black pieces */
void ChessGame::generateBlackAttacks()
{
    m_board.board.blackAttacks = 0;
    for (auto &piece: m_pieceInformation)
    {
        if (piece->getColor() == board::BLACK)
        {
            piece->getAttacks(m_board.board.blackAttacks.value);
        }
    }
}


/** Generate all possible attacks for the white pieces */
void ChessGame::generateWhiteAttacks()
{
    m_board.board.whiteAttacks = 0;
    for (auto &piece: m_pieceInformation)
    {
        if (piece->getColor() == board::WHITE)
        {
            piece->getAttacks(m_board.board.whiteAttacks.value);
        }
    }
}

/** Generate necessary information for legal move generation
 *
 * Must be called before generating legal moves for any piece
 */
void ChessGame::pregenLegalMoves()
{
    m_board.board.allPieces = m_board.board.getTotalValue();
    m_board.board.getWhitePieces(m_board.board.whitePieces);
    m_board.board.getBlackPieces(m_board.board.blackPieces);

    generateWhiteAttacks();
    generateBlackAttacks();

    m_board.board.genMoveInfo = true;
}

/** Get the white king
 *
 * @return A reference to the white king
 */
board::Piece *ChessGame::getWhiteKing() const
{
    if (m_pieceInformation.empty() or m_whiteKing == nullptr)
    {
        return nullptr;
    }

    return m_whiteKing;
}

/** Get the black king
 *
 * @return A reference to the black king
 */
board::Piece *ChessGame::getBlackKing() const
{
    if (m_pieceInformation.empty() or m_blackKing == nullptr)
    {
        return nullptr;
    }

    return m_blackKing;
}

/** Reset the board and piece information */
void ChessGame::resetGame()
{
    m_board.resetBoard();

    if (!m_pieceInformation.empty())
    {
        for (auto &elem: m_pieceInformation)
        {
            delete elem;
            elem = nullptr;
        }

        m_pieceInformation.clear();
    }
}


/** Create a new game from a FEN string
 *
 * @param fen The FEN string
 */
void ChessGame::createFromFEN(const std::string &fen) noexcept(false)
{
    resetGame();

    m_board.createFromFEN(fen);

    for (int j = 0; j < 12; ++j)
    {
        for (int i = 0; i < 64; ++i)
        {
            int vsqr = i; // (i / 8) * 8 + (7 - i % 8);
            int sqr = i;

            if (m_board.board.data[j].value & 0b1ull << vsqr)
            {
                using namespace board;
                switch (j)
                {
                    case 0: // First element is white pawns
                        m_pieceInformation.push_back(new WhitePawn(&m_board, sqr));
                        break;
                    case 1: // Second element is white knights
                        m_pieceInformation.push_back(new Knight(WHITE, &m_board, sqr));
                        break;
                    case 2: // Third element is white bishops
                        m_pieceInformation.push_back(new Bishop(WHITE, &m_board, sqr));
                        break;
                    case 3: // Fourth element is white rooks
                        m_pieceInformation.push_back(new Rook(WHITE, &m_board, sqr));
                        break;
                    case 4: // Fifth element is white queens
                        m_pieceInformation.push_back(new Queen(WHITE, &m_board, sqr));
                        break;
                    case 5: // Sixth element is white king
                        m_pieceInformation.push_back(new King(WHITE, &m_board, sqr));
                        m_whiteKing = m_pieceInformation.back();
                        break;
                    case 6: // Seventh element is black pawns
                        m_pieceInformation.push_back(new BlackPawn(&m_board, sqr));
                        break;
                    case 7: // Eighth element is black knights
                        m_pieceInformation.push_back(new Knight(BLACK, &m_board, sqr));
                        break;
                    case 8: // Ninth element is black bishops
                        m_pieceInformation.push_back(new Bishop(BLACK, &m_board, sqr));
                        break;
                    case 9: // Tenth element is black rooks
                        m_pieceInformation.push_back(new Rook(BLACK, &m_board, sqr));
                        break;
                    case 10: // Eleventh element is black queens
                        m_pieceInformation.push_back(new Queen(BLACK, &m_board, sqr));
                        break;
                    case 11: // Twelfth element is black king
                        m_pieceInformation.push_back(new King(BLACK, &m_board, sqr));
                        m_blackKing = m_pieceInformation.back();
                        break;
                    default:
                        break; // This is impossible
                }
            }
        }
    }

    if (m_whiteKing == nullptr or m_blackKing == nullptr)
    {
        throw std::runtime_error("Could not find kings in the FEN string");
        return;
    }

    for (auto &j: m_pieceInformation)
    {
        j->setKing(m_whiteKing);
        j->setKing(m_blackKing);
    }
}

/** Get the FEN string for the game
 *
 *
 * @return The FEN string
 */
std::string ChessGame::getFEN() const { return m_board.getFEN(m_halfMoveClock, m_fullMoveClock); }

ChessGame::~ChessGame()
{
    if (!m_pieceInformation.empty())
    {
        for (auto &elem: m_pieceInformation)
        {
            delete elem;
            elem = nullptr;
        }

        m_pieceInformation.clear();
    }
}
