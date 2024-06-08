Legal Move Generation
=====================

This section will cover how I generate legal moves for the pieces on the board. Importantly,
these move generators don't address if the king is already in check. I plan to implement
that while creating the general legal move generator in the ChessGame class or maybe while
working on the engine.

*General*

Legal move generation requires a few more things than normal move generation, which
would just iterate through all possible directions/moves for a piece and add them to a list.
Legal move generation has to check if the piece is pinned to the king before it is allowed to move,
and if it is pinned, which directions the piece may still go.

Validating pins requires somewhat hard to read code in my eyes so I hope to explain how it works
here. 

To validate a pin, 4 possible directions need to be addressed, up and down, left and right
and both diagonal directions. The code will then check for each direction to discover if their
is a possible pin, this may mean checking for a rook or a queen or checking for a bishop or a queen
depending on which direction is checked. If a potential pinning piece is discovered, the code must
then check to see if there is a piece between itself and its king to determine if it is actually pinned.

Code for determining which direction the king is from the piece is explained as follows. For reference:
   m_location % 8 is the column of the piece or the x coordinate
   m_location / 8 is the row of the piece or the y coordinate

**Up and Down**

.. code-block:: c++
  
    // Up and Down
    // Requires a check for if the columns of the king and piece are the same
    if (m_location % 8 == king_location % 8)
    {
        // Potential pin because the king and piece are on the same file

        // Check the ranks of the piece and king to determine which direction the king is
        if (m_location / 8 > king_location / 8)
        {
            // The king is below the pawn, act accordingly
        }
        else
        {
            // The king is above the pawn, act accordingly
        }
    }

**Left and Right**

.. code-block:: c++

	// Left and Right
	// Requires a check for if the rows of the king and piece are the same
	if (m_location / 8 == king_location / 8)
	{
		// Potential pin because the king and piece are on the same rank

		// Check the columns of the piece and king to determine which direction the king is
		if (m_location % 8 > king_location % 8)
		{
			// The king is to the right of the pawn, act accordingly
		}
		else
		{
			// The king is to the left of the pawn, act accordingly
		}
	}

**Diagonal**

.. code-block

	// Diagonal
	// Requires a check for if the absolute difference 
	// between the columns and rows of the king and piece are the same

    // Top left to the bottom right
    if ((m_location / 8 - king_location / 8) == (m_location % 8 - king_location % 8)) {
        if (m_location % 8 < king_location % 8) {
            // King is to the bottom right
        }
        else {
            // King is to the top left
        }
    }

    // Top right to the bottom left          Note the negative sign:
    if ((m_location / 8 - king_location / 8) == -(m_location % 8 - king_location % 8)) {
        if (m_location % 8 > king_location % 8) {
            // King is to the bottom left
        }
        else {
            // King is to the top right
        }
    }

.. toctree::
   :maxdepth: 2

   board_representation
   pieces/pawn
   pieces/knight
   pieces/bishop
   pieces/rook
   pieces/queen
   pieces/king
