/**
 * @file rook_test.cpp
 * @author Matthew Brown
 * @brief Unit tests for the rook class
 */
#include "chess_engine/board/rook.h"
#include "chess_engine/board/chess_board.h"
#include "chess_engine/chess_game.h"
#include "gtest/gtest.h"

TEST(RookTest, TestRookMovement) {}

TEST(RookTest, TestRookGetType) { EXPECT_EQ(Rook(true, nullptr, 0).getType(), PieceType::ROOK); }

TEST(RookTest, TestRookGetAttacks)
{
    ChessGame game;
    ASSERT_NO_THROW(game.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12"));

    auto rook = dynamic_cast<Rook *>(game.getPiece(0));
    ASSERT_NE(rook, nullptr);

    uint64_t attacks = 0;
    rook->getAttacks(attacks);

    // TODO: Add expected attacks
    // EXPECT_EQ(attacks, );
}

TEST(RookTest, TestRookGetLegalMoves)
{
    ChessBoard board;
    ASSERT_NO_THROW(board.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12",
                                        nullptr, nullptr));
}
