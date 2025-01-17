# Viking
## Overview
Viking is an intermediate UCI chess engine that can play against humans or other engines. Like other chess engines, Viking is a command line program and does not include a graphical user interface. Viking communicates with existing chess GUIs using the Universal Chess Interface (UCI). I personally use the CuteChess GUI, but other options exist.
## Description
The engine has three main components: move generation, evaluation, and search. Move generation is the process of generating all legal moves for a given board position. Evaluation assigns a score to a board position which describes the chances of a player winning. Search chooses the next move by looking ahead at different move sequences and using the evaluation function to determine the best move.

Move generation is accurate and has been tested using Perft (performance test, move path enumeration), which traverses the move generation tree and counts the leaf nodes at a given depth. These values are then compared to predetermined values (such as those obtained by established chess engines such as Stockfish) to confirm accuracy. Move generation has been tested in this manner using a few different board positions up to depths between 4-6.

The engine currently uses a fairly simple evaluation function, considering both the material value and the strength of the positions of the pieces. For instance, central pawns are valued more highly than pawns on the perimeter.

Search uses alpha-beta pruning, which builds upon the minimax algorithm. Minimax considers both the moves available to a player as well as the subsequent moves that the opponent may make in response. In particular, it considers the best opponent responses to the player's moves and selects the move that leads to the best outocme assuming that the opponent makes the best moves available to them. Alpha-beta pruning is an optimization on the minimax algorithm that reduces the search space without overlooking any potentially better move. Search now uses a technique called iterative deepening, in which the program begins with a search of depth 1 and then repeats the search with an incremented depth until no more time is allocated. This is an effective strategy for time-management. It also offers performance benefits when combined with move ordering. Move ordering has not been implemented yet, but is listed in the "Next Steps" section below.

The engine in its current form provides a solid opponent for an intermediate player like myself. I hope to continue to improve the engine-- see the "Next Steps" section below. I would also like to have the engine play against other engines in order to estimate its Elo strength.

## Using Viking
Clone this repository and navigate to the "src" directory. Run "cmake ." then "make viking". This will create the executable called "viking". Remember that this is a command line program. To play a game, install a chess GUI of your choice.

## Next Steps
Below I list some improvements that I hope to implement in the future.
### Move Generation
- Further optimization to improve time performance.
### Evaluation
- Improve the evaluation function to consider additional positional factors like game phase and doubled/isolated/passed pawns.
- Explore [NNUE](https://www.chessprogramming.org/NNUE) (Efficiently Updatable Neural Networks) for evaluation. Top chess engines have began to employ neural networks for evaluation in the last five years, resulting in major performance improvements.
### Search
This is the current largest area for improvement. The current search is simple and a variety of further techniques can be implemented to improve performance. These include but are not limited to:
- [Null move pruning](https://www.chessprogramming.org/Null_Move_Pruning)
- [Move ordering](https://www.chessprogramming.org/Move_Ordering)
- [Principal variation](https://www.chessprogramming.org/Principal_Variation)
- [Pondering](https://www.chessprogramming.org/Pondering)
- Multi-threading

## Credit
- The [Chess Programming wiki](chessprogramming.org) is a comprehensive resource for all matters of chess programming. It was referenced extensively for this project.
- [Stockfish](https://github.com/official-stockfish/Stockfish)
- The open-source chess engine [Deepov](https://github.com/RomainGoussault/Deepov), by Romain Goussault, was lightly referenced as an example for how certain chess programming techniques can be implemented in C++.