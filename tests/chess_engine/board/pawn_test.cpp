/**
 * @file pawn_test.cpp
 * @author Matthew Brown
 * @brief Unit tests for the pawn class
 */
#include "chess_engine/board/pawn.h"
#include "chess_engine/board/chess_board.h"
#include "chess_engine/chess_game.h"
#include "gtest/gtest.h"
#include "low_level_test_functions.h"

bool testPawnMovement(std::string fen, std::string square, std::vector<std::string> possibleMoves) {
    ChessGame game;
    try {
        game.createFromFEN(fen);
    } catch (std::exception &e) {
        std::cerr << "Error testing pawn movement: " << e.what() << std::endl;
        return false;
    }

    std::vector<uint64_t> expectedMoves;
    for (auto move: possibleMoves) {
        expectedMoves.push_back(ChessBoard::getSquareFromAlgebraic(move));
    }

    uint64_t moves = 0;
    Piece *pawn = game.getPiece(ChessBoard::getSquareFromAlgebraic(square));
    if (pawn == nullptr or pawn->getType() != PieceType::PAWN) {
        std::cerr << "Error testing pawn movement: " << square << std::endl;
        return false;
    }

    game.pregenLegalMoves();

    std::vector<std::string> errorMoves;
    pawn->getLegalMoves(moves);
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


TEST(PawnTest, TestPawnMovement) {}

TEST(PawnTest, TestPawnGetAttacks) {
    ChessGame game;
    ASSERT_NO_THROW(game.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12"));

    auto pawn = dynamic_cast<Pawn *>(game.getPiece(9));
    ASSERT_NE(pawn, nullptr);

    uint64_t attacks = 0;
    pawn->getAttacks(attacks);

    EXPECT_EQ(attacks, (0b1ull << 16) | (0b1ull << 18));
}

TEST(PawnTest, TestPawnGetLegalMoves) {
    EXPECT_TRUE(testPawnMovement("k3q3/1bq4q/8/3PPP2/rPnpK1Pq/3PPP2/4N3/1q2q3 w - - 0 1", "d3", {}));
    EXPECT_TRUE(testPawnMovement("k3q3/1bq4q/8/3PPP2/rPnpK1Pq/3PPP2/4N3/1q2q3 w - - 0 1", "e3", {"d4"}));
    EXPECT_TRUE(testPawnMovement("k3q3/1bq4q/8/3PPP2/rPnpK1Pq/3PPP2/4N3/1q2q3 w - - 0 1", "f3", {"f4"}));
    EXPECT_TRUE(testPawnMovement("k3q3/1bq4q/8/3PPP2/rPnpK1Pq/3PPP2/4N3/1q2q3 w - - 0 1", "b4", {"b5"}));
    EXPECT_TRUE(testPawnMovement("k3q3/1bq4q/8/3PPP2/rPnpK1Pq/3PPP2/4N3/1q2q3 w - - 0 1", "d5", {}));
    EXPECT_TRUE(testPawnMovement("k3q3/1bq4q/8/3PPP2/rPnpK1Pq/3PPP2/4N3/1q2q3 w - - 0 1", "e5", {"e6"}));
    EXPECT_TRUE(testPawnMovement("k3q3/1bq4q/8/3PPP2/rPnpK1Pq/3PPP2/4N3/1q2q3 w - - 0 1", "f5", {}));
    EXPECT_TRUE(testPawnMovement("k3q3/1bq4q/8/3PPP2/rPnpK1Pq/3PPP2/4N3/1q2q3 w - - 0 1", "g4", {}));

    EXPECT_TRUE(testPawnMovement("K3QQQ1/1BQ4Q/5B2/3ppp2/R1npk1pp/3ppp1Q/4N3/1Q2Q3 w - - 0 1", "d3", {}));
    EXPECT_TRUE(testPawnMovement("K3QQQ1/1BQ4Q/5B2/3ppp2/R1npk1pp/3ppp1Q/4N3/1Q2Q3 w - - 0 1", "e3", {}));
    EXPECT_TRUE(testPawnMovement("K3QQQ1/1BQ4Q/5B2/3ppp2/R1npk1pp/3ppp1Q/4N3/1Q2Q3 w - - 0 1", "f3", {"f2", "e2"}));
    EXPECT_TRUE(testPawnMovement("K3QQQ1/1BQ4Q/5B2/3ppp2/R1npk1pp/3ppp1Q/4N3/1Q2Q3 w - - 0 1", "d4", {}));
    EXPECT_TRUE(testPawnMovement("K3QQQ1/1BQ4Q/5B2/3ppp2/R1npk1pp/3ppp1Q/4N3/1Q2Q3 w - - 0 1", "g4", {"h3", "g3"}));
    EXPECT_TRUE(testPawnMovement("K3QQQ1/1BQ4Q/5B2/3ppp2/R1npk1pp/3ppp1Q/4N3/1Q2Q3 w - - 0 1", "h4", {}));
    EXPECT_TRUE(testPawnMovement("K3QQQ1/1BQ4Q/5B2/3ppp2/R1npk1pp/3ppp1Q/4N3/1Q2Q3 w - - 0 1", "d5", {}));
    EXPECT_TRUE(testPawnMovement("K3QQQ1/1BQ4Q/5B2/3ppp2/R1npk1pp/3ppp1Q/4N3/1Q2Q3 w - - 0 1", "e5", {}));
    EXPECT_TRUE(testPawnMovement("K3QQQ1/1BQ4Q/5B2/3ppp2/R1npk1pp/3ppp1Q/4N3/1Q2Q3 w - - 0 1", "f5", {}));
}
