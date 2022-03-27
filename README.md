# Not-Carlsen
Successor of the Not-Magnus chess engine, now written in C(arlsen).

------

## Current Features
- FEN board initialization

------

## Devlog
3/27/22 v0.0.3
> Defined bitboard constants for all squares, files, and ranks.
>
> Defined bit attack maps for knights, bishops, and rooks from all squares.

3/26/22 v0.0.2
> Implemented complete board initialization.

3/22/22 v0.0.1
> Began writing board representation "class".
> 
> Given a FEN string, function will pull information regarding turn, castling rights, en passant squares, halfmove clock, and fullmove number. Bitboard parsing not yet implemented.
