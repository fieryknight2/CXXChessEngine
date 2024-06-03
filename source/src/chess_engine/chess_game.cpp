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

/** Get the number of pieces in the game
 *
 * @return The number of pieces in the game
 */
int ChessGame::getPieceCount() const { return m_pieceCount; }

/** Get the pieces in the game
 *
 * @return The pieces in the game
 */
Piece **ChessGame::getPieces() const { return m_pieceInformation; }

/** Get a piece from the game
 *
 * @param square The square of the piece
 * @return The piece at the square
 */
Piece *ChessGame::getPiece(uint64_t square) const
{
    if (!m_pieceInformation or m_pieceCount == 0)
    {
        return nullptr;
    }

    for (int j = 0; j < m_pieceCount; ++j)
    {
        if (m_pieceInformation[j]->getSquare() == square)
        {
            return m_pieceInformation[j];
        }
    }

    return nullptr;
}

/** Get the white king
 *
 * @return A reference to the white king
 */
Piece *ChessGame::getWhiteKing() const
{
    if (!m_pieceInformation or m_pieceCount == 0)
    {
        // TODO: Implement more checks / validations
        return nullptr;
    }

    return m_whiteKing;
}

/** Get the black king
 *
 * @return A reference to the black king
 */
Piece *ChessGame::getBlackKing() const
{
    if (!m_pieceInformation or m_pieceCount == 0)
    {
        return nullptr;
    }

    return m_blackKing;
}

/** Reset the board and piece information */
void ChessGame::resetGame()
{
    m_board.resetBoard();

    if (m_pieceCount)
    {
        m_pieceCount = 0;
        delete[] m_pieceInformation;

        m_pieceInformation = nullptr;
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

    m_pieceCount = m_board.board.getTotalValue().getBitCount();
    m_pieceInformation = new Piece *[m_pieceCount];
    for (int j = 0, elem = 0; j < 12; ++j)
    {
        for (int k = 0; k < 64; ++k)
        {
            if (m_board.board.data[j].value & (0b1ull << k))
            {
                switch (j)
                {
                    case 0: // First element is white pawns
                        m_pieceInformation[elem] = new Pawn(WHITE, &m_board, k);
                        break;
                    case 1: // Second element is white knights
                        m_pieceInformation[elem] = new Knight(WHITE, &m_board, k);
                        break;
                    case 2: // Third element is white bishops
                        m_pieceInformation[elem] = new Bishop(WHITE, &m_board, k);
                        break;
                    case 3: // Fourth element is white rooks
                        m_pieceInformation[elem] = new Rook(WHITE, &m_board, k);
                        break;
                    case 4: // Fifth element is white queens
                        m_pieceInformation[elem] = new Queen(WHITE, &m_board, k);
                        break;
                    case 5: // Sixth element is white king
                        m_pieceInformation[elem] = new King(WHITE, &m_board, k);
                        m_whiteKing = m_pieceInformation[elem];
                        break;
                    case 6: // Seventh element is black pawns
                        m_pieceInformation[elem] = new Pawn(BLACK, &m_board, k);
                        break;
                    case 7: // Eighth element is black knights
                        m_pieceInformation[elem] = new Knight(BLACK, &m_board, k);
                        break;
                    case 8: // Ninth element is black bishops
                        m_pieceInformation[elem] = new Bishop(BLACK, &m_board, k);
                        break;
                    case 9: // Tenth element is black rooks
                        m_pieceInformation[elem] = new Rook(BLACK, &m_board, k);
                        break;
                    case 10: // Eleventh element is black queens
                        m_pieceInformation[elem] = new Queen(BLACK, &m_board, k);
                        break;
                    case 11: // Twelfth element is black king
                        m_pieceInformation[elem] = new King(BLACK, &m_board, k);
                        m_blackKing = m_pieceInformation[elem];
                        break;
                    default:
                        break; // This is impossible
                }

                ++elem;
            }
        }
    }

    for (int j = 0; j < m_pieceCount; ++j)
    {
        m_pieceInformation[j]->setKing(true, m_whiteKing);
        m_pieceInformation[j]->setKing(false, m_blackKing);
    }
}

/** Get the FEN string for the game
 *
 *
 * @return The FEN string
 */
std::string ChessGame::getFEN() const { return m_board.getFEN(m_halfMoveClock, m_fullMoveClock); }
