/****************************************************************************
 * MIT License
 * Copyright (c) 2024 Matthew
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * attack_generator.cpp - Constants used in the program
 * @author Matthew Brown
 * @date 05/21/2024
 *****************************************************************************/
#include "chess_engine/board/move_generator.h"
#include "chess_engine/constants.h"


/** Generates all legal moves on the board for the given piece
 *
 * Determines which function to call based on the piece type, it may
 * be more efficient to call the appropriate function directly.
 *
 * @param attacks Stacks to add attacks too
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @return All possible legal moves for the given piece
 */
void get_attacks(std::stack<int> *attacks, const int *board, const int piece) {
    switch (board[piece]) {
        case WHITE_PAWN: // White pawn
            get_pawn_attacks(attacks, true, piece);
            break;
        case BLACK_PAWN: // Black pawn
            get_pawn_attacks(attacks, false, piece);
            break;
        case WHITE_KNIGHT: // White knight
        case BLACK_KNIGHT: // Black knight
            get_knight_attacks(attacks, piece);
            break;
        case WHITE_BISHOP: // White bishop
        case BLACK_BISHOP: // Black bishop
            get_bishop_attacks(attacks, board, piece);
            break;
        case WHITE_ROOK: // White rook
        case BLACK_ROOK: // Black rook
            get_rook_attacks(attacks, board, piece);
            break;
        case WHITE_QUEEN: // White queen
        case BLACK_QUEEN: // Black queen
            get_queen_attacks(attacks, board, piece);
            break;
        case WHITE_KING: // White king
        case BLACK_KING: // Black king
            get_king_attacks(attacks, piece);
            break;
        case EMPTY: // Empty square
        default:
            break;
    }
}


/** Generates all legal moves on the board for the given pawn
 *
 * See documentation for legal_pawn_moves() for more information
 * Pawn attacks don't depend on the board but does depend on the color
 *
 * @param attacks Stacks to add attacks too
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @return All possible legal moves for the given piece
 */
void get_pawn_attacks(std::stack<int> *attacks, const int *board, const int piece) {
    // Remember piece % 8 is the file
    // piece // 8 is the rank
    // Pawns aren't allowed on the last rank
    if (!attacks or piece < 8 or piece > 55) {
        return;
    }

    if (board[piece] < 0) { // Black pawn
        if (piece % 8 > 0) {
            attacks->push(piece - 9); // Left side (white perspective)
        }
        if (piece % 8 < 7) {
            attacks->push(piece - 7); // Right side
        }
    } else { // White pawn
        if (piece % 8 > 0) {
            attacks->push(piece + 7); // Right side
        }
        if (piece % 8 < 7) {
            attacks->push(piece + 9); // Left side
        }
    }
}

/** Generates all legal moves on the board for the given pawn
 *
 * See documentation for legal_pawn_moves() for more information
 * Pawn attacks don't depend on the board but does depend on the color
 * This version allows you to specify the color of the pawn
 *
 * @param attacks Stacks to add attacks too
 * @param color Color of the pawn. True for White; false for Black
 * @param piece The piece to generate legal moves for
 * @return All possible legal moves for the given piece
 */
void get_pawn_attacks(std::stack<int> *attacks, bool color, int piece) {
    if (!attacks or piece < 8 or piece > 55) {
        return;
    }

    if (color) { // Black pawn
        if (piece % 8 > 0) {
            attacks->push(piece - 9); // Left side (white perspective)
        }
        if (piece % 8 < 7) {
            attacks->push(piece - 7); // Right side
        }
    } else { // White pawn
        if (piece % 8 > 0) {
            attacks->push(piece + 7); // Right side
        }
        if (piece % 8 < 7) {
            attacks->push(piece + 9); // Left side
        }
    }
}

/** Generates all legal moves on the board for the given knight
 *
 * The knight only attacks the 8 possible squares and doesn't require the
 * board to be passed in.
 *
 * @param attacks Stacks to add attacks too
 * @param piece The piece to generate legal moves for
 * @return All possible legal moves for the given piece
 */
void get_knight_attacks(std::stack<int> *attacks, int piece) {
    // Code ripped out of my python implementation
    if (piece / 8 > 1) { // C++ automatically converts int / int to int, no integer division necessary
        // validate bottom far
        if (piece % 8 > 0) {
            // validate right close
            attacks->push(piece - 17);
        }
        if (piece % 8 < 7) {
            // validate left close
            attacks->push(piece - 15);
        }
    }

    if (piece / 8 > 0) {
        // validate bottom close
        if (piece % 8 > 1) {
            // validate right far
            attacks->push(piece - 10);
        }
        if (piece % 8 < 6) {
            // validate left far
            attacks->push(piece - 6);
        }
    }

    if (piece / 8 < 7) {
        // validate top close
        if (piece % 8 > 1) {
            // validate right far
            attacks->push(piece + 6);
        }
        if (piece % 8 < 6) {
            // validate left far
            attacks->push(piece + 10);
        }
    }

    if (piece / 8 < 6) {
        // validate top far
        if (piece % 8 > 0) {
            // validate right close
            attacks->push(piece + 15);
        }
        if (piece % 8 < 7) {
            // validate left close
            attacks->push(piece + 17);
        }
    }
}


/** Generates all legal moves on the board for the given bishop
 *
 * See documentation for legal_bishop_moves() for more information
 *
 * @param attacks Stacks to add attacks too
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @return All possible legal moves for the given piece
 */
void get_bishop_attacks(std::stack<int> *attacks, const int *board, int piece) {
    int index = piece;

    while (index - 9 >= 0 and index % 8 != 0) {
        // Bottom Right
        index -= 9;
        attacks->push(index);

        if (board[index] != EMPTY) {
            break;
        }
    }

    index = piece;
    while (index - 7 >= 0 and index % 8 != 7) {
        // Bottom Left
        index -= 7;
        attacks->push(index);

        if (board[index] != EMPTY) {
            break;
        }
    }

    index = piece;
    while (index + 7 < 64 and index % 8 != 0) {
        // Top Left
        index += 7;
        attacks->push(index);

        if (board[index] != EMPTY) {
            break;
        }
    }

    index = piece;
    while (index + 9 < 64 and index % 8 != 7) {
        // Top Right
        index += 9;
        attacks->push(index);

        if (board[index] != EMPTY) {
            break;
        }
    }
}

/** Generates all legal moves on the board for the given rook
 *
 * See documentation for legal_rook_moves() for more information
 *
 * @param attacks Stacks to add attacks too
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @return All possible legal moves for the given piece
 */
void get_rook_attacks(std::stack<int> *attacks, const int *board, int piece) {
    int index = piece;
    const int rank_min = (piece / 8) * 8;

    while (index - 8 >= 0) {
        // Left
        index -= 8;
        attacks->push(index);

        if (board[index] != EMPTY) {
            break;
        }
    }

    index = piece;
    while (index - 1 >= rank_min) {
        // Right
        index -= 1;
        attacks->push(index);

        if (board[index] != EMPTY) {
            break;
        }
    }

    index = piece;
    while (index < rank_min + 7) {
        // Left
        index += 1;
        attacks->push(index);

        if (board[index] != EMPTY) {
            break;
        }
    }

    index = piece;
    while (index + 8 < 64) {
        // Right
        index += 8;
        attacks->push(index);

        if (board[index] != EMPTY) {
            break;
        }
    }
}

/** Generates all legal moves on the board for the given queen
 *
 * See documentation for legal_queen_moves() for more information
 *
 * @param attacks Stacks to add attacks too
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @return All possible legal moves for the given piece
 */
void get_queen_attacks(std::stack<int> *attacks, const int *board, int piece) {
    int index = piece;
    const int rank_min = (piece / 8) * 8;

    // Rook Code
    while (index - 8 >= 0) {
        // Left
        index -= 8;
        attacks->push(index);

        if (board[index] != EMPTY) {
            break;
        }
    }

    index = piece;
    while (index - 1 >= rank_min) {
        // Right
        index -= 1;
        attacks->push(index);

        if (board[index] != EMPTY) {
            break;
        }
    }

    index = piece;
    while (index < rank_min + 7) {
        // Left
        index += 1;
        attacks->push(index);

        if (board[index] != EMPTY) {
            break;
        }
    }

    index = piece;
    while (index + 8 < 64) {
        // Right
        index += 8;
        attacks->push(index);

        if (board[index] != EMPTY) {
            break;
        }
    }


    // Bishop Code
    index = piece;
    while (index - 9 >= 0 and index % 8 != 0) {
        // Bottom Right
        index -= 9;
        attacks->push(index);

        if (board[index] != EMPTY) {
            break;
        }
    }

    index = piece;
    while (index - 7 >= 0 and index % 8 != 7) {
        // Bottom Left
        index -= 7;
        attacks->push(index);

        if (board[index] != EMPTY) {
            break;
        }
    }

    index = piece;
    while (index + 7 < 64 and index % 8 != 0) {
        // Top Left
        index += 7;
        attacks->push(index);

        if (board[index] != EMPTY) {
            break;
        }
    }

    index = piece;
    while (index + 9 < 64 and index % 8 != 7) {
        // Top Right
        index += 9;
        attacks->push(index);

        if (board[index] != EMPTY) {
            break;
        }
    }
}

/** Generates all legal moves on the board for the given king
 *
 * See documentation for legal_king_moves() for more information
 *
 * @param attacks Stacks to add attacks too
 * @param piece The piece to generate legal moves for
 * @return All possible legal moves for the given piece
 */
void get_king_attacks(std::stack<int> *attacks, int piece) {
    if (piece > 7) {
        // validate bottom
        if (piece % 8 > 0) {
            attacks->push(piece - 9); // bottom right corner
        }

        attacks->push(piece - 8); // bottom

        if (piece % 8 < 7) {
            attacks->push(piece - 7); // bottom left corner
        }
    }

    if (piece % 8 > 0) {
        // validate right
        attacks->push(piece - 1);
    }

    if (piece % 8 < 7) {
        // validate left
        attacks->push(piece + 1);
    }

    // validate top
    if (piece < 56) {
        if (piece % 8 > 0) {
            attacks->push(piece + 7); // top right corner
        }

        attacks->push(piece + 8); // top

        if (piece % 8 < 7) {
            attacks->push(piece + 9); // top left corner
        }
    }
}
