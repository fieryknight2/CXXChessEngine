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
 * chess_game.h - Class definition for a chess game
 * @author Matthew Brown
 * @date 6/02/2024
 *****************************************************************************/
#pragma once

#include <string>
#include <vector>

#include "chess_engine/board/chess_board.h"
#include "chess_engine/board/piece.h"

namespace chessengine {

/** Chess Game
 *
 * This class represents a chess game.
 * It is a collection of chess boards.
 *
 * @author Matthew Brown
 * @date 6/02/2024
 */
class ChessGame {
    /* Stored information on all pieces */
    std::vector<board::Piece *> m_pieceInformation;

    board::Piece *m_whiteKing = nullptr;
    board::Piece *m_blackKing = nullptr;

    /* Game information */
    int m_halfMoveClock = 0; // This keeps track of the 50 move rule
    int m_fullMoveClock = 0;

    // std::vector<ChessMove> m_moveHistory;

    board::ChessBoard m_board;

public:
    [[nodiscard]] uint64_t getPieceCount() const;
    [[nodiscard]] std::vector<board::Piece *> getPieces() const;
    [[nodiscard]] board::Piece *getPiece(uint64_t square) const;

    void pregenLegalMoves();
    void generateWhiteAttacks();
    void generateBlackAttacks();

    // Getters
    [[nodiscard]] board::Piece *getWhiteKing() const;
    [[nodiscard]] board::Piece *getBlackKing() const;

    void resetGame();

    void createFromFEN(const std::string &fen) noexcept(false);
    [[nodiscard]] std::string getFEN() const;

    [[nodiscard]] int getHalfMoveClock() const { return m_halfMoveClock; }
    [[nodiscard]] int getFullMoveClock() const { return m_fullMoveClock; }

    [[nodiscard]] board::ChessBoard *getBoard() { return &m_board; }

    ~ChessGame();
};

} // namespace chessengine
