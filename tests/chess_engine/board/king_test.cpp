/**
 * @file rook_test.cpp
 * @author Matthew Brown
 * @brief Unit tests for the rook class
 */
#include "chess_engine/board/king.h"
#include "chess_engine/board/chess_board.h"
#include "chess_engine/chess_game.h"
#include "gtest/gtest.h"
#include "low_level_test_functions.h"

void print_attacks(uint64_t value) {
    for (int i = 0; i < 64; ++i) {
        if (i % 4 == 0) {
            std::cout << " ";
        }
        if (i % 8 == 0) {
            std::cout << "\n";
        }

        if (value & (1ull << i)) {
            std::cout << "1";
        } else {
            std::cout << "0";
        }
    }
    std::cout << std::endl;
}

bool testKingMovement(std::string fen, std::string square, std::vector<std::string> possibleMoves) {
    ChessGame game;
    try {
        game.createFromFEN(fen);
    } catch (std::exception &e) {
        std::cerr << "Error testing king movement: " << e.what() << std::endl;
        return false;
    }

    std::vector<uint64_t> expectedMoves;
    for (auto move: possibleMoves) {
        expectedMoves.push_back(ChessBoard::getSquareFromAlgebraic(move));
    }

    uint64_t moves = 0;
    King *king = dynamic_cast<King *>(game.getPiece(ChessBoard::getSquareFromAlgebraic(square)));
    if (king == nullptr) {
        std::cerr << "Error testing king movement: Could not find king at square " << square << std::endl;
        return false;
    }

    Bitboard attacks;
    for (auto piece: game.getPieces()) {
        if (piece->getColor() != king->getColor()) {
            // std::cout << "Piece: " << piece->getType() << " " << ChessBoard::toAlgebraic(piece->getSquare())
            //           << std::endl;
            piece->getAttacks(attacks.value);
        }
    }

    std::vector<std::string> errorMoves;
    king->getLegalMoves(moves, attacks.value); // Most important line of the function lol
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
        std::cerr << "Error testing king movement: Unexpected squares found: ";
        for (auto move: errorMoves) {
            std::cerr << move << " ";
        }
        std::cerr << std::endl;
    }

    if (!expectedMoves.empty()) {
        std::cerr << "Error testing king movement: Expected squares not found: ";
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

TEST(KingTest, TestKingMovement) {}

TEST(KingTest, TestKingGetType) { EXPECT_EQ(King(true, nullptr, 0).getType(), PieceType::KING); }

TEST(KingTest, TestKingGetAttacks) {
    ChessGame game;
    ASSERT_NO_THROW(game.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12"));

    auto king = dynamic_cast<King *>(game.getPiece(1));
    ASSERT_NE(king, nullptr);

    uint64_t attacks = 0;
    king->getAttacks(attacks);

    // TODO: Add expected attacks
    // EXPECT_EQ(attacks, );
}

TEST(KingTest, TestKingGetLegalMoves) {
    ChessBoard board;
    ASSERT_NO_THROW(board.createFromFEN("r2q1rk1/2p1bppp/p2p1n2/1p2P3/4P1b1/1nP1BN2/PP3PPP/RN1QR1K1 w - - 1 12",
                                        nullptr, nullptr));

    EXPECT_TRUE(testKingMovement("7k/1b3n2/8/8/3K4/8/2q5/8 w - - 0 1", "d4", {"e3"}));
    EXPECT_TRUE(testKingMovement("7k/1b3n2/8/8/2RK4/8/2q5/8 w - - 0 1", "d4", {"e3", "c5"}));
    EXPECT_TRUE(testKingMovement("7k/1b3n2/8/8/2RK4/b7/8/8 w - - 0 1", "d4", {"c3", "d3", "e3"}));
    EXPECT_TRUE(testKingMovement("7k/1b3n2/8/8/3K4/8/2q5/8 w - - 0 1", "d4", {"e3"}));
}
