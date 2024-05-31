Welcome to ChessEngine's documentation!
=======================================

This a chess engine written in C++ and is for educational purposes only.
I sincerely doubt I will be able to make this a strong engine, but I intend
to make it strong enough to beat beginners and hopefully me eventually.

Board Representation
====================

The board is represented in using a series of bitboards. Attacks
will be represented using a bitboard and maybe a list, I'm not sure yet.

.. toctree::
   :caption: Chess Board:

   board/board_representation
   board/board_docs

Engine Function
===============

It may be a while before I get around to writing the engine, as I will
need the board representation to be complete.

GUI Connection Methods
======================

These are planned for the future, and will allow the engine to be connected to
any popular GUI that implements the UCI protocol.

.. toctree::
   :maxdepth: 5
   :caption: Other Stuff:

   board/old
