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

.. doxygenclass:: ChessBoard
    :members: