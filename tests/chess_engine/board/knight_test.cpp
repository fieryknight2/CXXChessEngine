/**
 * @file knight_test.cpp
 * @author Matthew Brown
 * @brief Unit tests for the knight class
 */
#include "chess_engine/board/knight.h"

#include <low_level_test_functions.h>

#include "chess_engine/board/chess_board.h"
#include "chess_engine/chess_game.h"
#include "gtest/gtest.h"

TEST(KnightTest, TestKnightMovement) {}

TEST(KnightTest, TestKnightGetType) { EXPECT_EQ(Knight(true, nullptr, 0).getType(), PieceType::KNIGHT); }

TEST(KnightTest, TestKnightGetAttacks)
{
    ChessGame game;
    ASSERT_NO_THROW(game.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12"));

    auto knight = dynamic_cast<Knight *>(game.getPiece(6));
    ASSERT_NE(knight, nullptr);

    uint64_t attacks = 0;
    knight->getAttacks(attacks);

    // TODO: Add expected attacks
    // EXPECT_EQ(attacks, );
}

TEST(KnightTest, TestKnightGetLegalMoves)
{
    ChessGame board;
    ASSERT_NO_THROW(board.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12"));
    uint64_t moves = 0;
    auto square = ChessBoard::getSquareFromAlgebraic("f6");
    auto knight = dynamic_cast<Knight *>(board.getPiece(square));
    ASSERT_NE(knight, nullptr);

    knight->getLegalMoves(moves);

    // std::cout << "------------------------------------------------------" << std::endl;
    // std::cout << " -        Printing legal moves for knight           -\n";
    // std::cout << "------------------------------------------------------\n" << std::endl;
    // print_uint64_t_comp(moves, board.getBoard()->board.data[PieceLoc::BLACK_KNIGHT].value & (1ull << square), " v");

    // board.getBoard()->board.data[PieceLoc::BLACK_KNIGHT].value |= moves;
    // std::cout << "------------------------------------------------------" << std::endl;
    // std::cout << " -     Printing board with legal moves made         -\n";
    // std::cout << "------------------------------------------------------\n" << std::endl;
    // board.getBoard()->printBoard();
}
