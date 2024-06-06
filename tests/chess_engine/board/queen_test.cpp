/**
 * @file queen_test.cpp
 * @author Matthew Brown
 * @brief Unit tests for the queen class
 */
#include "chess_engine/board/queen.h"
#include "chess_engine/board/chess_board.h"
#include "chess_engine/chess_game.h"
#include "gtest/gtest.h"

TEST(QueenTest, TestQueenMovement) {}

TEST(QueenTest, TestQueenGetType) { EXPECT_EQ(Queen(true, nullptr, 0).getType(), PieceType::QUEEN); }

TEST(QueenTest, TestQueenGetAttacks)
{
    ChessGame game;
    ASSERT_NO_THROW(game.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12"));

    auto queen = dynamic_cast<Queen *>(game.getPiece(4));
    ASSERT_NE(queen, nullptr);

    uint64_t attacks = 0;
    queen->getAttacks(attacks);

    // TODO: Add expected attacks
    // EXPECT_EQ(attacks, );
}

TEST(QueenTest, TestQueenGetLegalMoves)
{
    ChessBoard board;
    ASSERT_NO_THROW(board.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12",
                                        nullptr, nullptr));
}
