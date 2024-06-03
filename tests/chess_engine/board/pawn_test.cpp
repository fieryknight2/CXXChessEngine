/**
 * @file pawn_test.cpp
 * @author Matthew Brown
 * @brief Unit tests for the pawn class
 */
#include "chess_engine/board/pawn.h"
#include "chess_engine/board/chess_board.h"
#include "chess_engine/chess_game.h"
#include "gtest/gtest.h"

TEST(PawnTest, TestPawnMovement) {}

TEST(PawnTest, TestPawnGetType) { EXPECT_EQ(Pawn(true, nullptr, 0).getType(), PieceType::PAWN); }

TEST(PawnTest, TestPawnGetAttacks)
{
    ChessGame game;
    ASSERT_NO_THROW(game.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12"));

    auto pawn = dynamic_cast<Pawn *>(game.getPiece(9));
    ASSERT_NE(pawn, nullptr);

    uint64_t attacks = 0;
    pawn->getAttacks(attacks);

    EXPECT_EQ(attacks, (0b1ull << 16) | (0b1ull << 18));
}

TEST(PawnTest, TestPawnGetLegalMoves)
{
    ChessBoard board;
    ASSERT_NO_THROW(board.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12",
                                        nullptr, nullptr));
}
