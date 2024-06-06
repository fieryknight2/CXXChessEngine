/**
 * @file rook_test.cpp
 * @author Matthew Brown
 * @brief Unit tests for the rook class
 */
#include "chess_engine/board/king.h"
#include "chess_engine/board/chess_board.h"
#include "chess_engine/chess_game.h"
#include "gtest/gtest.h"

TEST(KingTest, TestKingMovement) {}

TEST(KingTest, TestKingGetType) { EXPECT_EQ(King(true, nullptr, 0).getType(), PieceType::KING); }

TEST(KingTest, TestKingGetAttacks)
{
    ChessGame game;
    ASSERT_NO_THROW(game.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12"));

    auto king = dynamic_cast<King *>(game.getPiece(1));
    ASSERT_NE(king, nullptr);

    uint64_t attacks = 0;
    king->getAttacks(attacks);

    // TODO: Add expected attacks
    // EXPECT_EQ(attacks, );
}

TEST(KingTest, TestKingGetLegalMoves)
{
    ChessBoard board;
    ASSERT_NO_THROW(board.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12",
                                        nullptr, nullptr));
}
