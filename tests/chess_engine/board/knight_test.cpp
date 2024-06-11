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

using namespace chessengine;
using namespace chessengine::board;

bool testKnightMovement(std::string fen, std::string square, std::vector<std::string> possibleMoves) {
    ChessGame game;
    try {
        game.createFromFEN(fen);
    } catch (std::exception &e) {
        std::cerr << "Error testing knight movement: " << e.what() << std::endl;
        return false;
    }

    std::vector<uint64_t> expectedMoves;
    for (auto move: possibleMoves) {
        expectedMoves.push_back(ChessBoard::getSquareFromAlgebraic(move));
    }

    uint64_t moves = 0;
    Knight *knight = dynamic_cast<Knight *>(game.getPiece(ChessBoard::getSquareFromAlgebraic(square)));
    if (knight == nullptr) {
        std::cerr << "Error testing knight movement: Could not find knight at square " << square << std::endl;
        return false;
    }

    game.pregenLegalMoves();

    std::vector<std::string> errorMoves;
    knight->getLegalMoves(moves);
    for (int i = 0; i < 64; ++i) {
        if (moves & (1ull << i)) {
            // Try to find the resulting expected move
            auto val = std::find(expectedMoves.begin(), expectedMoves.end(), i);
            if (val == expectedMoves.end()) {
                errorMoves.push_back(ChessBoard::toAlgebraic(i));
            } else {
                expectedMoves.erase(val);
            }
        }
    }

    if (!errorMoves.empty()) {
        std::cerr << "Error testing knight movement: Unexpected squares found: ";
        for (auto move: errorMoves) {
            std::cerr << move << " ";
        }
        std::cerr << std::endl;
    }

    if (!expectedMoves.empty()) {
        std::cerr << "Error testing knight movement: Expected squares not found: ";
        for (auto move: expectedMoves) {
            std::cerr << ChessBoard::toAlgebraic(move) << " ";
        }
        std::cerr << std::endl;
    }

    if (!errorMoves.empty() or !expectedMoves.empty()) {
        return false;
    }

    return true;
}

TEST(KnightTest, TestKnightMovement) {}

TEST(KnightTest, TestKnightGetType) { EXPECT_EQ(Knight(true, nullptr, 0).getType(), PieceType::KNIGHT); }

TEST(KnightTest, TestKnightGetAttacks) {
    ChessGame game;
    ASSERT_NO_THROW(game.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12"));

    auto knight = dynamic_cast<Knight *>(game.getPiece(6));
    ASSERT_NE(knight, nullptr);

    uint64_t attacks = 0;
    knight->getAttacks(attacks);

    // TODO: Add expected attacks
    // EXPECT_EQ(attacks, );
}

TEST(KnightTest, TestKnightGetLegalMoves) {
    EXPECT_TRUE(testKnightMovement("8/6k1/4P3/q1PPn3/1N1B4/2KP1Nr1/3n4/4B1Q1 w - - 0 1", "f3",
                                   {"e5", "d2", "h2", "g5", "h4"}));

    EXPECT_TRUE(testKnightMovement("8/6k1/4P3/q1PPn3/1N1B4/2KP1Nr1/3n4/4B1Q1 w - - 0 1", "e5", {}));

    EXPECT_TRUE(testKnightMovement("8/6k1/4P3/q1PPn3/1N1B4/2KP1Nr1/3n4/4B1Q1 w - - 0 1", "b4", {}));

    EXPECT_TRUE(testKnightMovement("7q/b2r2N1/1N1N1b2/4N1k1/2NK1Nq1/2b1N3/1N6/b5b1 w - - 0 1", "g7",
                                   {"e8", "e6", "f5", "h5"}));
    EXPECT_TRUE(testKnightMovement("7q/b2r2N1/1N1N1b2/4N1k1/2NK1Nq1/2b1N3/1N6/b5b1 w - - 0 1", "b6", {}));
    EXPECT_TRUE(testKnightMovement("7q/b2r2N1/1N1N1b2/4N1k1/2NK1Nq1/2b1N3/1N6/b5b1 w - - 0 1", "d6", {}));
    EXPECT_TRUE(testKnightMovement("7q/b2r2N1/1N1N1b2/4N1k1/2NK1Nq1/2b1N3/1N6/b5b1 w - - 0 1", "e5", {}));
    EXPECT_TRUE(
            testKnightMovement("7q/b2r2N1/1N1N1b2/4N1k1/2NK1Nq1/2b1N3/1N6/b5b1 w - - 0 1", "c4", {"a5", "a3", "d2"}));
    EXPECT_TRUE(testKnightMovement("7q/b2r2N1/1N1N1b2/4N1k1/2NK1Nq1/2b1N3/1N6/b5b1 w - - 0 1", "f4", {}));
    EXPECT_TRUE(testKnightMovement("7q/b2r2N1/1N1N1b2/4N1k1/2NK1Nq1/2b1N3/1N6/b5b1 w - - 0 1", "e3", {}));
    EXPECT_TRUE(
            testKnightMovement("7q/b2r2N1/1N1N1b2/4N1k1/2NK1Nq1/2b1N3/1N6/b5b1 w - - 0 1", "b2", {"a4", "d1", "d3"}));

    EXPECT_TRUE(testKnightMovement("7q/b2r2N1/1N1N1b2/4N1k1/r1NK1Nq1/2b1N3/1N6/b5b1 w - - 0 1", "c4", {}));

    EXPECT_TRUE(testKnightMovement("7q/b2r2N1/1N1N1b2/4N1k1/r1NK1Nq1/2b1N3/1N1N4/b2r2b1 w - - 0 1", "d2", {}));
}
