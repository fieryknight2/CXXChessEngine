Board Representation
====================

For a long while, I've been trying to avoid using bitboards, because I
believe they are difficult to work with, but more importantly I believe
there are better representations. I have given up that view for now.

**Bitboards**

Bitboards are a standard way of representing a chess board using a single
64-bit integer. They represent whether a piece occupies a square or does not.
The standard representation for a chess board involves twelve integers, one for
each piece type and color. This means the minimum amount of memory required
to represent a chess board is 64 * 12 = 768 bits.

**Other Representations**

A different approach I've been thinking of is using
32 int8_t (chars) to represent the board. This would mean each char represents two
pieces and their colors. The total amount of memory required would be 32 * 8 = 256 bits
4 bits is enough information to represent 8 types of pieces, and since there are 6 pieces
and 2 colors, only 1 bit is wasted.

**Board Representation**

The board is represented from 1, a to 8, h. The direction is down left.
A would be equal to 0, b would be equal to 1, and so on until h would be equal to 7.
Memory representation of the board is as follows:

+---+---+---+---+---+---+---+---+---+
|   | a | b | c | d | e | f | g | h |
+---+---+---+---+---+---+---+---+---+
| 0 | x | x | x | x | x | x | x | x |
+---+---+---+---+---+---+---+---+---+
| 1 | x | x | x | x | x | x | x | x |
+---+---+---+---+---+---+---+---+---+
| 2 | x | x | x | x | x | x | x | x |
+---+---+---+---+---+---+---+---+---+
| 3 | x | x | x | x | x | x | x | x |
+---+---+---+---+---+---+---+---+---+
| 4 | x | x | x | x | x | x | x | x |
+---+---+---+---+---+---+---+---+---+
| 5 | x | x | x | x | x | x | x | x |
+---+---+---+---+---+---+---+---+---+
| 6 | x | x | x | x | x | x | x | x |
+---+---+---+---+---+---+---+---+---+
| 7 | x | x | x | x | x | x | x | x |
+---+---+---+---+---+---+---+---+---+

**Move Representation**

My first idea for representing possible moves is based on
the idea that a Queen has a maximum possible twenty-seven moves. given a required
6 bits to represent a number between 0 and 64, then 27 * 6 = 162 bits is enough
to represent all possible moves. Unfortunately you have to grab a power of two
so the minimum here would be something like 27 * 8 = 204 bits and the bitboard
representation for possible moves maxes out at 64 bits which is significantly smaller
though somewhat more complex to work with. So results look like I'll have to stick with the
standard bitboard representation for now.

**Piece Representation**

I'll probably represent individual pieces as either a combined int16_t or two separate
int8_ts. This will allow representation piece type and location in the minimum amount of space.

**Notes**

Why I'm looking to use the minimum amount of memory. In general, the functions using these
representations are going to be run hundreds of thousands of times while analyzing a position. They
need to be

.. doxygenstruct:: Board
    :members: