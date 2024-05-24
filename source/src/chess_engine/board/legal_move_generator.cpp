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
 * legal_move_generator.cpp - Constants used in the program
 * @author Matthew Brown
 * @date 05/21/2024
 *****************************************************************************/
#include "chess_engine/board/move_generator.h"
#include "chess_engine/constants.h"

namespace
{

enum KingDirection
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT, // Diagonal
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
    SOMEWHERE_ELSE
};

}

/** Generates all legal moves on the board for the given color
 *
 * Loops through every piece on the board and returns all possible
 * legal moves for the given color.
 *
 * @param legal_moves A list of moves to add to
 * @param board List of all pieces and their locations on the board
 * @param color The color of pieces to generate legal moves for
 * @return All possible legal moves for the given color
 */
void generate_legal_moves(std::stack<std::pair<int, int>> *legal_moves, int *board, bool color) {}


/** Generates all legal moves on the board for the given piece
 *
 * Determines which function to call based on the piece type, it may
 * be more efficient to call the appropriate function directly.
 *
 * @param legal_moves A list of moves to add to
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @return All possible legal moves for the given piece
 */
void generate_legal_moves(std::stack<int> *legal_moves, const int *board, int piece) {}

/** Generate the legal moves for a given pawn
 *
 * The pawn can move forward one square if it is not blocked, and it can
 * capture an enemy piece one space forward to its left or right. It can also move
 * forward two spaces if on its starting square. Though it isn't handled here, a pawn
 * can also promote at the end of the board.
 *
 * @param legalMoves A list of moves to add to
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @param kingLoc The location of the King (optional)
 * @param enPassantSquare Square where en passant is possible (optional)
 * @return A stack of all legal moves for the given piece
 */
void legal_pawn_moves(std::stack<int> *legalMoves, const int *board, int piece, int kingLoc, int enPassantSquare)
{
    // Validation
    if (piece < 7 or piece > 56 or board[piece] == EMPTY)
    {
        return;
    }

    // King location
    if (kingLoc == -1)
    {
        // Find the king location manually
        for (int i = 0; i < 64; i++)
        {
            if (board[i] == KING)
            {
                kingLoc = i;
                break;
            }
        }
    }

    KingDirection direction = SOMEWHERE_ELSE;
    int index = piece;

    // Locate direction to the king for efficiency
    // Position of the pawn: (xp, yp) where yp is piece / 8 and xp is piece % 8
    // Position of the king: (xk, yk) where yk is kingLoc / 8 and xk is kingLoc % 8
    // Vector math to find the direction, d = yp - yk / xp - xk
    // Determine if the king is on a line requires (xp - xk) == 0, or d = 1, -1, or 0
    // TODO: Determine if I want to simplify this and remove direction
    if (piece / 8 - kingLoc / 8 < 0 and piece % 8 - kingLoc % 8 == 0)
    {
        // Infinity or vector is vertical
        direction = DOWN;
    }
    else if (piece / 8 - kingLoc / 8 > 0 and piece % 8 - kingLoc % 8 == 0)
    {
        direction = UP;
    }
    else if (piece / 8 - kingLoc / 8 == 0 and piece % 8 - kingLoc % 8 > 0)
    {
        direction = RIGHT;
    }
    else if (piece / 8 - kingLoc / 8 == 0 and piece % 8 - kingLoc % 8 < 0)
    {
        direction = LEFT;
    }
    else if (piece / 8 - kingLoc / 8 == piece % 8 - kingLoc % 8)
    {
        direction = UP_LEFT;
    }
    else if (piece / 8 - kingLoc / 8 == piece % 8 - kingLoc % 8)
    {
        direction = DOWN_RIGHT;
    }
    else if (piece / 8 - kingLoc / 8 == -(piece % 8 - kingLoc % 8) and piece % 8 - kingLoc % 8 < 0)
    {
        direction = DOWN_LEFT;
    }
    else if (-(piece / 8 - kingLoc / 8) == piece % 8 - kingLoc % 8 and piece / 8 - kingLoc / 8 < 0)
    {
        direction = UP_RIGHT;
    }

    bool canMove = true;
    const int sign = board[piece] / abs(board[piece]);
    // Rank min from rook is piece / 8 * 8
    // Process pins
    if (direction == RIGHT)
    {
        while (index < piece / 8 * 8 + 7)
        {
            index += 1;
            if (board[index] == -sign * ROOK or board[index] == -sign * QUEEN)
            {
                // Can't move forward
                canMove = false;
                break;
            }
            if (board[index] != EMPTY)
            {
                break;
            }
        }
    }
    else if (direction == LEFT)
    {
        while (index - 1 >= piece / 8 * 8)
        {
            index -= 1;
            if (board[index] == -sign * ROOK or board[index] == -sign * QUEEN)
            {
                // Can't move forward
                canMove = false;
                break;
            }
            if (board[index] != EMPTY)
            {
                break;
            }
        }
    }
    else if (direction == DOWN_RIGHT)
    {
        while (index + 9 < 64 and index % 8 != 7)
        {
            index += 9;

            if (board[index] == -sign * BISHOP or board[index] == -sign * QUEEN)
            {
                // Can't move forward
                canMove = false;
                break;
            }
            if (board[index] != EMPTY)
            {
                break;
            }
        }
    }
    else if (direction == DOWN_LEFT)
    {
        while (index + 7 < 64 and index % 8 != 0)
        {
            index += 7;

            if (board[index] == -sign * BISHOP or board[index] == -sign * QUEEN)
            {
                // Can't move forward
                canMove = false;
                break;
            }
            if (board[index] != EMPTY)
            {
                break;
            }
        }
    }
    else if (direction == UP_LEFT)
    {
        while (index - 9 >= 0 and index % 8 != 0)
        {
            index -= 9;

            if (board[index] == -sign * BISHOP or board[index] == -sign * QUEEN)
            {
                // Can't move forward
                canMove = false;
                break;
            }
            if (board[index] != EMPTY)
            {
                break;
            }
        }
    }
    else if (direction == UP_RIGHT)
    {
        while (index - 7 >= 0 and index % 8 != 7)
        {
            index -= 7;

            if (board[index] == -sign * BISHOP or board[index] == -sign * QUEEN)
            {
                // Can't move forward
                canMove = false;
                break;
            }
            if (board[index] != EMPTY)
            {
                break;
            }
        }
    }

    // Normal movement (1 or 2 squares forward)
    if (canMove)
    {
        if (board[piece] > 0)
        { // White color
            // Normal movement applies
            if (board[piece + 8] == EMPTY)
            { // Normal move
                legalMoves->push(piece + 8);
            }

            // Possible double move on first move
            if (piece > 7 and piece < 16 and board[piece + 16] == EMPTY)
            {
                legalMoves->push(piece + 16);
            }
        }
        else
        { // Black color
            // Normal movement applies
            if (board[piece - 8] == EMPTY)
            {
                legalMoves->push(piece - 8);
            }
            if (piece > 47 and piece < 56 and board[piece - 16] == EMPTY)
            {
                legalMoves->push(piece - 16);
            }
        }
    }

    // Attacks and en passant:
    if (!(direction == LEFT and !canMove) and !(direction == RIGHT and !canMove))
    {
        if (direction == UP)
        {
            // Verify we are not pinned
            while (index >= 8 and index % 8 != 0)
            {
                index -= 8;
                if (board[index] == -sign * ROOK or board[index] == -sign * QUEEN)
                {
                    // Can't capture left or right
                    return;
                }
                if (board[index] != EMPTY)
                {
                    break;
                }
            }
        }
        else if (direction == DOWN)
        {
            // Verify we are not pinned
            while (index < 56 and index % 8 != 7)
            {
                index += 8;
                if (board[index] == -sign * ROOK or board[index] == -sign * QUEEN)
                {
                    return;
                }
                if (board[index] != EMPTY)
                {
                    break;
                }
            }
        }

        // Left capture
        if (!(direction == UP_RIGHT and !canMove) and !(direction == DOWN_LEFT and !canMove))
        {
            if (board[piece] > 0 and piece % 8 > 0 and (board[piece + 7] < 0 or piece + 7 == enPassantSquare))
            { // White pawn
                legalMoves->push(piece + 9);
            }
            else if (board[piece] < 0 and piece % 8 < 7 and (board[piece - 7] > 0 or piece - 7 == enPassantSquare))
            { // Black pawn
                legalMoves->push(piece - 9);
            }
        }

        // Right capture
        if (!(direction == UP_LEFT and !canMove) and !(direction == DOWN_RIGHT and !canMove))
        {
            if (board[piece] > 0 and piece % 8 < 7 and board[piece - 7] < 0)
            {
                // White pawn
                legalMoves->push(piece + 7); // Left side
            }
            else if (board[piece] < 0 and piece % 8 > 0 and board[piece + 7] > 0)
            {
                // Black pawn
                legalMoves->push(piece - 7); // Right side
            }
        }
    }
}

/** Generate the legal moves for a given knight
 *
 * The knight can move in an L shape in any direction, jumping over
 * pieces as it goes.
 *
 * @param legalMoves A list of moves to add to
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @param kingLoc The location of the King (optional)
 * @return A stack of all legal moves for the given piece
 */
void legal_knight_moves(std::stack<int> *legalMoves, const int *board, int piece, int kingLoc)
{
    // Knights are simple because if they are pinned, they can't move
    // Validation
    if (board[piece] == EMPTY)
    {
        return; // Avoid div by zero
    }

    // King location
    if (kingLoc == -1)
    {
        // Find the king location manually
        for (int i = 0; i < 64; i++)
        {
            if (board[i] == KING)
            {
                kingLoc = i;
                break;
            }
        }
    }

    int index = piece;
    bool canMove = true;
    const int sign = board[piece] / abs(board[piece]);
    // Process pins
    if (piece / 8 - kingLoc / 8 < 0 and piece % 8 - kingLoc % 8 == 0)
    {
        // Direction is down
        while (index < 56 and index % 8 != 7)
        {
            index += 8;
            if (board[index] == -sign * ROOK or board[index] == -sign * QUEEN)
            {
                // Can't move forward
                canMove = false;
                break;
            }
            if (board[index] != EMPTY)
            {
                break;
            }
        }
    }
    else if (piece / 8 - kingLoc / 8 > 1 and piece % 8 - kingLoc % 8 == 0)
    {
        // Direction is up
        while (index >= 8 and index % 8 != 0)
        {
            index -= 8;
            if (board[index] == -sign * ROOK or board[index] == -sign * QUEEN)
            {
                return;
            }
            if (board[index] != EMPTY)
            {
                break;
            }
        }
    }
    else if (piece / 8 - kingLoc / 8 == 0 and piece % 8 - kingLoc % 8 > 0)
    {
        // Direction is right
        while (index < piece / 8 * 8 + 7)
        {
            index += 1;
            if (board[index] == -sign * ROOK or board[index] == -sign * QUEEN)
            {
                // Can't move forward
                canMove = false;
                break;
            }

            if (board[index] != EMPTY)
            {
                break;
            }
        }
    }
    else if (piece / 8 - kingLoc / 8 == 0 and piece % 8 - kingLoc % 8 < 0)
    {
        // Direction is left
        while (index - 1 >= piece / 8 * 8)
        {
            index -= 1;
            if (board[index] == -sign * ROOK or board[index] == -sign * QUEEN)
            {
                // Can't move forward
                canMove = false;
                break;
            }
            if (board[index] != EMPTY)
            {
                break;
            }
        }
    }
    else if (piece / 8 - kingLoc / 8 == piece % 8 - kingLoc % 8)
    {
        // Direction is up left
        while (index - 9 >= 0 and index % 8 != 0)
        {
            index -= 9;

            if (board[index] == -sign * BISHOP or board[index] == -sign * QUEEN)
            {
                // Can't move forward
                canMove = false;
                break;
            }
            if (board[index] != EMPTY)
            {
                break;
            }
        }
    }
    else if (piece / 8 - kingLoc / 8 == piece % 8 - kingLoc % 8)
    {
        // Direction is down right
    }
    else if (piece / 8 - kingLoc / 8 == -(piece % 8 - kingLoc % 8) and piece % 8 - kingLoc % 8 < 0)
    {
        // Direction is down left
        while (index + 7 < 64 and index % 8 != 0)
        {
            index += 7;

            if (board[index] == -sign * BISHOP or board[index] == -sign * QUEEN)
            {
                // Can't move forward
                canMove = false;
                break;
            }
            if (board[index] != EMPTY)
            {
                break;
            }
        }
    }
    else if (-(piece / 8 - kingLoc / 8) == piece % 8 - kingLoc % 8 and piece / 8 - kingLoc / 8 < 0)
    {
        // Direction is up right
        while (index - 7 >= 0 and index % 8 != 7)
        {
            index -= 7;

            if (board[index] == -sign * BISHOP or board[index] == -sign * QUEEN)
            {
                // Can't move forward
                canMove = false;
                break;
            }
            if (board[index] != EMPTY)
            {
                break;
            }
        }
    }

    // Make moves
    if (canMove)
    {
        // Bottom Far
        if (piece / 8 > 1)
        {
            // C++ automatically converts int / int to int, no integer division necessary
            if (piece % 8 > 0 and board[piece - 17] * -sign >= 0)
            {
                // validate right close
                legalMoves->push(piece - 17);
            }
            if (piece % 8 < 7 and board[piece - 15] * -sign >= 0)
            {
                // validate left close
                legalMoves->push(piece - 15);
            }
        }
        // Bottom Close
        if (piece / 8 > 0)
        {
            if (piece % 8 > 1 and board[piece - 10] * -sign >= 0)
            {
                // validate right far
                legalMoves->push(piece - 10);
            }
            if (piece % 8 < 6 and board[piece - 6] * -sign >= 0)
            {
                // validate left far
                legalMoves->push(piece - 6);
            }
        }
        // Top Close
        if (piece / 8 < 7)
        {
            if (piece % 8 > 1 and board[piece + 6] * -sign >= 0)
            {
                // validate right far
                legalMoves->push(piece + 6);
            }
            if (piece % 8 < 6 and board[piece + 10] * -sign >= 0)
            {
                // validate left far
                legalMoves->push(piece + 10);
            }
        }
        // Top Far
        if (piece / 8 < 6)
        {
            if (piece % 8 > 0 and board[piece + 15] * -sign >= 0)
            {
                // validate right close
                legalMoves->push(piece + 15);
            }
            if (piece % 8 < 7 and board[piece + 17] * -sign >= 0)
            {
                // validate left close
                legalMoves->push(piece + 17);
            }
        }
    }
}


/** Generate the legal moves for a given bishop
 *
 * The bishop can move diagonally in all four directions
 *
 * @param legal_moves A list of moves to add to
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @param kingLoc The location of the King (optional)
 * @return A stack of all legal moves for the given piece
 */
void legal_bishop_moves(std::stack<int> *legal_moves, const int *board, int piece, int kingLoc) {}

/** Generate the legal moves for a given rook
 *
 * The rook can move horizontally or vertically in any direction
 *
 * @param legal_moves A list of moves to add to
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @param kingLoc The location of the King (optional)
 * @return A stack of all legal moves for the given piece
 */
void legal_rook_moves(std::stack<int> *legal_moves, const int *board, int piece, int kingLoc) {}

/** Generate the legal moves for a given queen
 *
 * The queen can move in the combined directions of a rook and a bishop
 *
 * @param legal_moves A list of moves to add to
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @param kingLoc The location of the King (optional)
 * @return A stack of all legal moves for the given piece
 */
void legal_queen_moves(std::stack<int> *legal_moves, const int *board, int piece, int kingLoc) {}

/** Generate the legal moves for a given king
 *
 * The king can move one square in any direction
 *
 * @param legal_moves A list of moves to add to
 * @param board List of all pieces and their locations on the board
 * @param piece The piece to generate legal moves for
 * @param kingLoc The location of the King (optional)
 * @return A stack of all legal moves for the given piece
 */
void legal_king_moves(std::stack<int> *legal_moves, const int *board, int piece, int kingLoc) {}
