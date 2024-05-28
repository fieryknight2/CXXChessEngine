/**
 * @file board_rep_test.cpp
 * @author Matthew Brown
 * @brief Unit tests for the board representation class.
 */
#include "chess_engine/board/board_rep.h"
#include <gtest/gtest.h>

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
    Board board;
    EXPECT_NO_THROW(board.createFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0"));
    EXPECT_EQ(board.getFEN(), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0");
    // board.printBoard();

    EXPECT_NO_THROW(
            board.createFromFEN("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2", nullptr, nullptr));
    EXPECT_EQ(board.getFEN(), "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 0 0");
    // board.printBoard();
}

TEST(BoardRepTest, GetFEN)
{
    Board board;
    // Manually set the board
    // TODO: Implement
    // EXPECT_EQ(board.getFEN(), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0");
}

TEST(BoardRepTest, GetFENWithHalfMoveClock)
{
    Board board;
    int halfMoveClock = 0;
    EXPECT_NO_THROW(board.createFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 4 0", &halfMoveClock));
    EXPECT_EQ(board.getFEN(halfMoveClock), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 4 0");
}

TEST(BoardRepTest, GetFENWithCastlingRights)
{
    Board board;
    EXPECT_NO_THROW(board.createFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w Kq - 0 0"));
    EXPECT_EQ(board.getFEN(), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w Kq - 0 0");
}

TEST(BoardRepTest, GetFENWithFullMoveClock)
{
    Board board;
    int fullMoveClock = 0;
    EXPECT_NO_THROW(
            board.createFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 5", nullptr, &fullMoveClock));
    EXPECT_EQ(board.getFEN(0, fullMoveClock), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 5");
}

TEST(BoardRepTest, GetFENWithEnPassantSquare)
{
    Board board;
    EXPECT_NO_THROW(board.createFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq a7 0 0"));
    EXPECT_EQ(board.getFEN(), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq a7 0 0");
}

TEST(BoardRepTest, GetFENWithEverything)
{
    Board board;
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
    Board board;
    board.pieces[5] = 0x0001f0000000ff00;
    board.printBoard();

    std::cout << std::endl;

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
