Board Representation
====================

For a long while, I've been trying to avoid using bitboards. But I've given up avoiding
them so I will now use them.

**Bitboards**

Bitboards are a standard way of representing a chess board using a single
64-bit integer. They represent whether a piece occupies a square or does not.
The standard representation for a chess board involves twelve integers, one for
each piece type and color.

**Other Representations**

A different approach I've been thinking of using but I've decided won't work:
32 int8_t (chars) to represent the board. This would mean each char represents two
pieces and their colors.

**Board Representation**

I've decided to use a 64-bit integer to represent the board. This is because it
will be the easiest and most efficient way to work with the board. The board is represented
with 12 bitboards, one for each piece type and color. The first 6 bitboard represents
the white pieces and the last 6 bitboard represents the black pieces.

**Direction and Bitoard Structure**
The reason I've wanted to avoid bitboards is because of the difficulty of
getting the directions and values correct for a beginning programmer like me.

Theoretical Board:

+---+---+---+---+---+---+---+---+---+
|   | A | B | C | D | E | F | G | H |
+---+---+---+---+---+---+---+---+---+
| 8 | r | n | b | q | k | b | n | r |
+---+---+---+---+---+---+---+---+---+
| 7 | p | p | p | p | p | p | p | p |
+---+---+---+---+---+---+---+---+---+
| 6 |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+
| 5 |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+
| 4 |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+
| 3 |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+
| 2 | P | P | P | P | P | P | P | P |
+---+---+---+---+---+---+---+---+---+
| 1 | R | N | B | Q | K | B | N | R |
+---+---+---+---+---+---+---+---+---+

Actual Board:

+---+---+---+---+---+---+---+---+---+
| 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
+---+---+---+---+---+---+---+---+---+
| 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
+---+---+---+---+---+---+---+---+---+
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
+---+---+---+---+---+---+---+---+---+
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
+---+---+---+---+---+---+---+---+---+
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
+---+---+---+---+---+---+---+---+---+
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
+---+---+---+---+---+---+---+---+---+
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
+---+---+---+---+---+---+---+---+---+
| 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
+---+---+---+---+---+---+---+---+---+
| 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
+---+---+---+---+---+---+---+---+---+

Ideally, the first board square would be A1 and increase from left to right,
unfortunately, the start square for a bitboard would be H1 decreasing from right to left.
The resulting plan currently is to follow the bitboard representation, example code:
To iterate through the board, use

.. code-block:: c++
    :linenos:

    for (int i = 0; i < 64; i++)
    {
        // Access a square with a mask
        unsigned int mask = 1 << i;
        uint64_t square = board & mask;
        if (square)
        {
            // There is a piece on square i
        }

        //
    }

To use rows and columns, use (note not tested yet)

.. code-block:: c++
    :linenos:

    for (int r = 0; r < 8; r++)
    {
        // Note that to print a row, we need to iterate from 7 to 0
        // or flip the direction that c is going (c = 7; c >= 0; --c)
        for (int c = 0; c < 8; c++)
        {
            // Access a square with a mask
            unsigned int mask = 1 << (r * 8 + c);

            uint64_t square = board & mask;
            if (square)
            {
                // There is a piece on square (c, r)
            }
        }
    }

**Move Representation**

My first idea for representing possible moves is based on
the idea that a Queen has a maximum possible twenty-seven moves but I'll probably stick
with the standard bitboard representation for now.

**Piece Representation**

TODO: Figure out

**Notes**

Why I'm looking to use the minimum amount of memory. In general, the functions using these
representations are going to be run hundreds of thousands of times while analyzing a position, so they
need to be as fast as possible.

.. toctree::
    :maxdepth: 1

    board_docs