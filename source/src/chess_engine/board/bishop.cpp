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
 * bishop.cpp - <Brief description>
 * @author Matthew Brown
 * @date 05/27/2024
 *****************************************************************************/
#include "chess_engine/board/bishop.h"

/** Make a move on the board
 *
 * @param to Location to move the piece to
 */
void Bishop::makeMove(int to) {
    // TODO: Implement
}

/** Get the type of the piece
 *
 * @return Type of the piece
 */
char Bishop::getType() const { return PieceType::BISHOP; }

/** Get the legal moves for the piece
 *
 * @param moves Pointer to a 64-bit integer to store the legal moves
 */
void Bishop::getLegalMoves(uint64_t &moves) const {
    // TODO: Implement
}

/** Get the possible attacks for the piece
 *
 * @param attacks Pointer to a 64-bit integer to store the legal attacks
 */
void Bishop::getAttacks(uint64_t &attacks) const {
    unsigned int index = m_location;
    uint64_t totalValue = m_board->board.getTotalValue().value;

    while (index > 7 and index % 8 > 0) {
        // Bottom Right
        index -= 9;
        attacks |= 1ull << index;

        if (totalValue & (1ull << index)) {
            break;
        }
    }

    index = m_location;
    while (index > 7 and index % 8 < 7) {
        // Bottom Left
        index -= 7;
        attacks |= 1ull << index;

        if (totalValue & (1ull << index)) {
            break;
        }
    }

    index = m_location;
    while (index < 57 and index % 8 > 0) {
        // Top Left
        index += 7;
        attacks |= 1ull << index;

        if (totalValue & (1ull << index)) {
            break;
        }
    }

    index = m_location;
    while (index < 57 and index % 8 < 7) {
        // Top Right
        index += 9;
        attacks |= 1ull << index;

        if (totalValue & (1ull << index)) {
            break;
        }
    }
}
