/**
 * @file bishop_test.cpp
 * @author Matthew Brown
 * @brief Unit tests for the bishop class
 */
#include "chess_engine/board/bishop.h"
#include "chess_engine/board/chess_board.h"
#include "chess_engine/chess_game.h"
#include "gtest/gtest.h"

TEST(BishopTest, TestBishopMovement) {}

TEST(BishopTest, TestBishopGetType) { EXPECT_EQ(Bishop(true, nullptr, 0).getType(), PieceType::BISHOP); }

TEST(BishopTest, TestBishopGetAttacks)
{
    std::cout << "Testing Bishop::getAttacks" << std::endl;
    ChessGame game;
    ASSERT_NO_THROW(game.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12"));

    auto something = game.getPiece(27);
    if (something == nullptr)
    {
        std::cout << "Something is null" << std::endl;
    }
    auto bishop = dynamic_cast<Bishop *>(game.getPiece(27));
    ASSERT_NE(bishop, nullptr);

    uint64_t attacks = 0;
    bishop->getAttacks(attacks);

    // TODO: Add expected attacks
    // EXPECT_EQ(attacks, );
}

TEST(BishopTest, TestBishopGetLegalMoves)
{
    ChessBoard board;
    ASSERT_NO_THROW(board.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12",
                                        nullptr, nullptr));
}