/**
 * @file bishop_test.cpp
 * @author Matthew Brown
 * @brief Unit tests for the bishop class
 */
#include "chess_engine/board/bishop.h"
#include "chess_engine/board/chess_board.h"
#include "chess_engine/chess_game.h"
#include "gtest/gtest.h"

using namespace chessengine;
using namespace chessengine::board;

TEST(BishopTest, TestBishopMovement) {}

TEST(BishopTest, TestBishopGetType) { EXPECT_EQ(Bishop(true, nullptr, 0).getType(), PieceType::BISHOP); }

TEST(BishopTest, TestBishopGetAttacks)
{
    ChessGame game;
    ASSERT_NO_THROW(game.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12"));

    auto bishop = dynamic_cast<Bishop *>(game.getPiece(19));
    ASSERT_NE(bishop, nullptr);
    EXPECT_EQ(bishop->getColor(), true);
    EXPECT_EQ(bishop->getType(), 'b');

    uint64_t attacks = 0;
    bishop->getAttacks(attacks);

    // TODO: Add expected attacks
    // EXPECT_EQ(attacks, );
}

TEST(BishopTest, TestBishopGetLegalMoves) {}
