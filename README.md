# Not-Carlsen
Successor of the Not-Magnus chess engine, now written in C(arlsen). Whereas Not-Magnus's goal was to learn the popular algorithims and techniques in modern chess engines, this engine will efficently implement them. Thus, the goal of this engine is simply to be strong while providing me an opportunity to solidify my C programming skills.

Special thanks to:
- github.com/nkarve for their magic bitboard generation.
- Peter Jones for their guide on legal move generation.

------

## Use
Compile with the makefile:

> mingw32-make

Not-Carlsen uses the [Universal Chess Interface (UCI)](http://wbec-ridderkerk.nl/html/UCIProtocol.html) protocol. Alongside the standard commands, the engine supports:
- #### go perft x
  Prints out the divided perft results for the initialized position for depth x.

------

## Current Features
- FEN board initialization
- UCI communication protocol
- Magic bitboard legal move generator (92 million nps)
- Principal variation search (PVS)
- Fail soft alpha-beta negamax
- Quiescence search
- Lockless transposition table
- Iterative deepening
- MVV-LVA move ordering
- Null move pruning
- Late move reduction
- Delta pruning
- Static exchange evaluation (SEE)
- Time manager
- Material score evaluation
- PSQT evaluation
- Tapered evaluation
- Threefold repetition hashtable

------

## Devlog
7/21/22 v1.6.2
> Rolled back PV changes as it was causing weird evaluation history issues.

7/19/22 v1.6.1
> Modified the transposition table for lockless multithreaded access.
>
> Switched to OpenMP from Pthreads for multithreading as Pthreads seems to struggle with the search functions.
>
> Fixed bugs involving time searched being rounded to the nearest second and transposition entries incorrectly being overridden.

7/18/22 v1.6
> Attempted several things to prevent overflow in quiescence search: delta pruning, transposition table access, and static exchange evaluation (SEE). With SEE, overflow seems to have been greatly minimized.
>
> Updated the PV line to spit out less nonsense. Move sequences of actual moves are longer, but still some issues that need to be ironed out.

7/16/22 v1.5
> Switched negamax to principal variation search. Tournament results give an elo difference of 108.4 +/- 658.1, in favor of PVS.
>
> Added move ordering and depth limiting factor to try to limit quiescence search to prevent stack overflow. More testing required.
>
> Added stalemate detection.

7/15/22 v1.4
> Added null move pruning and late move reduction.

7/14/22 v1.3
> Added quiescence search.
>
> Tests with MTD(f) have been unsuccessful. Compared with normal negamax, tournament results give an elo difference of 173.5 +/- 274.1, in favor of negamax.
>
> Added custom free() function for stacks to properly free every node instead of just the head.

7/11/22 v1.2
> Added PSQT and tapered evaluation. For now, this will be all the evaluation features, focusing on a higher depth paradigm.
>
> Switched multithreading frameworks from OpenMP to Pthreads to take in UCI input while a search is running.
>
> Fixed bug involving bad moves being played due to an incomplete search from running out of time.

7/8/22 v1.1
> Adapted the repetition hashtable interface to a transposition table.
>
> This allowed me to add iterative deepening and a time manager as well.
>
> Implemented a move ordering scheme.

7/7/22 v1.0
> Implemented the Universal Chess Interface (UCI) engine-to-GUI communication protocol.
>
> Quickly put together a basic negamax and material evaluation function. Engine officially able to play chess!

7/6/22 v0.4.5
> Using compiler optimizations discovered in the makefile process, perft speeds was increased to 52 million nps for the starting position and 92 million nps for Kiwipete.
>
> Fixed bug where a black king in double check was incorrectly allowed to castle.
>
> Increased speed allows me to test higher depth perfts. Passed all of Steven Edwards's (Chess Programming Wiki) challenge positions.

7/5/22 v0.4.4
> Added a makefile.
>
> Started adding in UCI commands.

6/30/22 v0.4.3
> Started saving the square the king is on rather than bit scanning it for every operation.
>
> Stopping move generation optimizations for now. Lower bound at ~22 million nps for positions like the starting one. Upper bound at ~40 million nps for positions like Kiwipete.

6/27/22 v0.4.2
> Minor pinmask generation optimizations.
>
> Added Kogge-Stone setwise sliding piece move generation to attempt to speed up attackmask generation. Strangely the algorithim seems slower, and requires additional castling checks, so rolling back changes.

6/23/22 v0.4.1
> Completely replaced pseudolegal move generator with the legal one.
>
> Fixed all known perft errors. Focusing on optimizations before further testing as lack of speed makes testing difficult on high depths.
>
> Switching to perft bulk counting adjusts speed to 24 million nps.

6/22/22 v0.4
> Successfully implemented a legal move generator. Optimizations and bug fixes still need to be made, but I am extremely happy with the speed at which I was able to implement this considering my previous attempt failed after a few days worth of effort. The coming updates will focus on speeding up this generator and squashing perft mismatches.

6/21/22 v0.3
> Added threefold repetition and 50-move rule detection.

6/15/22 v0.2.6
> Added zobrist hash to the position.

6/10/22 v0.2.5
> Continuing to squash perft bugs:
>
> Duplicate moves caused by an improper last move flag in the pseudo-legal move list due to a reliance on default uninitialized values.
>
> Missing castling moves for black as the move legality was checking for the existence of white rooks instead of black.
>
> Undefined behavior due to oversight where promotion moves that were also captures were not being properly considered captures.
>
> Undefined behavior due to knight promotions mistakingly being marked 'K' instead of 'N'.
>
> Several positions still have errors, but default position has no errors up to depth 7 (3.2 billion nodes). First speed test clocks in at ~6.5 million nodes per second.

6/8/22 v0.2.4
> Fixed major perft bugs by using a non-static pseudo-legal move array. In recurisve perft calls, said array was erroneously being changed mid-call such that the array would be different after a recursive call and keep the changes after the sub-function finished executing.
> 
> Perft errors reduced to ~10%.

6/7/22 v0.2.3
> Fixed bug with move generation where the victim piece in captures was incorrectly tagged due to it being checked after the attacker square was updated.
>
> Continuing to run into error where all "perft 1" numbers match the unit tests, but deeper depths give results larger than what they should be.

6/6/22 v0.2.2
> Started perft testing with the move generator. This determines the accuracy of the move generation as well as the speed at different depths.
>
> Added function to determine if king is in check.

6/5/22 v0.2.1
> Changed make/unmake to make/copy for move pushing and popping.

6/2/22 v0.2
> Implemented a pseudolegal move generator and move stack.
>
> Changed pawn move generator from setwise to individual.

5/9/22 v0.1.4
> Added pawn move (single push, double push, capture, and en passant) wrapper functions.

4/30/22 v0.1.3
> Added wrapper functions for the move generation of all pieces besides pawns.
>
> Board structure now includes a "mailbox" representation of the board to easily determine what piece is on a given square.

4/27/22 v0.1.2
> Implemented sliding move generation using magic bitboards. Credit to github.com/nkarve.

3/27/22 v0.1.1
> Defined bitboard constants for all squares, files, and ranks.
>
> Defined bit attack maps for knights, bishops, and rooks from all squares.

3/26/22 v0.1
> Implemented complete board initialization.

3/22/22 v0.0.1
> Began writing board representation "class".
> 
> Given a FEN string, function will pull information regarding turn, castling rights, en passant squares, halfmove clock, and fullmove number. Bitboard parsing not yet implemented.
