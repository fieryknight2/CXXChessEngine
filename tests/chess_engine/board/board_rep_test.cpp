/**
 * @file board_rep_test.cpp
 * @author Matthew Brown
 * @brief Unit tests for the board representation class.
 */
#include <gtest/gtest.h>
#include "chess_engine/board/chess_board.h"

using namespace chessengine::board;
using namespace chessengine;

TEST(BitboardTest, GetBitCount)
{
    Bitboard bb(0xffffffffffffffff);
    EXPECT_EQ(bb.getBitCount(), 64);

    bb = 0xff;
    EXPECT_EQ(bb.getBitCount(), 8);

    bb = 0b11;
    EXPECT_EQ(bb.getBitCount(), 2);
}

TEST(BoardRepTest, CreateFromFEN)
{
    ChessBoard board;
    EXPECT_NO_THROW(board.createFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0"));
    EXPECT_EQ(board.getFEN(), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0");
    // board.printBoard();

    EXPECT_NO_THROW(
            board.createFromFEN("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2", nullptr, nullptr));
    EXPECT_EQ(board.getFEN(), "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 0 0");
    // board.printBoard();

    EXPECT_NO_THROW(board.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12",
                                        nullptr, nullptr));
    EXPECT_EQ(board.getFEN(), "r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 0 0");
}

TEST(BoardRepTest, GetFENWithHalfMoveClock)
{
    ChessBoard board;
    int halfMoveClock = 0;
    EXPECT_NO_THROW(board.createFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 4 0", &halfMoveClock));
    EXPECT_EQ(board.getFEN(halfMoveClock), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 4 0");
}

TEST(BoardRepTest, GetFENWithCastlingRights)
{
    ChessBoard board;
    EXPECT_NO_THROW(board.createFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w Kq - 0 0"));
    EXPECT_EQ(board.getFEN(), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w Kq - 0 0");
}

TEST(BoardRepTest, GetFENWithFullMoveClock)
{
    ChessBoard board;
    int fullMoveClock = 0;
    EXPECT_NO_THROW(
            board.createFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 5", nullptr, &fullMoveClock));
    EXPECT_EQ(board.getFEN(0, fullMoveClock), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 5");
}

TEST(BoardRepTest, GetFENWithEnPassantSquare)
{
    ChessBoard board;
    EXPECT_NO_THROW(board.createFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq a7 0 0"));
    EXPECT_EQ(board.getFEN(), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq a7 0 0");
}

TEST(BoardRepTest, GetFENWithEverything)
{
    ChessBoard board;
    int fullMoveClock = 0;
    int halfMoveClock = 0;
    EXPECT_NO_THROW(board.createFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq e4 5 5", &halfMoveClock,
                                        &fullMoveClock));
    EXPECT_EQ(board.getFEN(halfMoveClock, fullMoveClock), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq e4 5 5");
}

TEST(BoardRepTest, PrintBoard)
{
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << " -          Tests for printing the board            - " << std::endl;
    std::cout << "  Results should look like an initial chess position" << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    ChessBoard board;

    EXPECT_NO_THROW(board.createFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"));
    board.printBoard();

    std::cout << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << " -                 Except this one                  - " << std::endl;
    std::cout << "------------------------------------------------------\n" << std::endl;

    // Random test position
    EXPECT_NO_THROW(board.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12",
                                        nullptr, nullptr));
    board.printBoard();

    std::cout << "\n------------------------------------------------------" << std::endl;
}

// TODO: Move to game test file
#include "chess_engine/chess_game.h"

TEST(ChessGameTest, GetPiece)
{
    ChessGame game;
    ASSERT_NO_THROW(game.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12"));

    EXPECT_EQ(game.getPieceCount(), 30);

    ASSERT_NE(game.getPiece(7), nullptr);
    EXPECT_EQ(game.getPiece(7)->getType(), PieceType::ROOK);
    EXPECT_EQ(game.getPiece(7)->getColor(), WHITE);

    EXPECT_NE(game.getPiece(1), nullptr);
}
