# chess-engine

# Description

This is a player-vs-computer chess game written in C++. It is playable from the command line. The player enters their moves in long algebraic notation e.x. "d2d4". The computer then selects and plays its move in response. The board is printed to the console after each move.

The bulk of the project is a simple chess engine to make move decisions for the computer. There are three main components: move generation, evaluation, and search. Move generation is the process of generating all legal moves for a given board position. Evaluation assigns a score to a board position which describes the chances of a player winning. Search chooses the next move by looking ahead at different move sequences and using the evaluation function to determine the best move.

Move generation is accurate and has been tested using Perft (performance test, move path enumeration), which traverses the move generation tree and counts the leaf nodes at a given depth. These values are then compared to predetermined values (such as those obtained by established chess engines such as Stockfish) to confirm accuracy. Move generation has been tested in this manner using a few different board positions up to depths between 4-6.

This engine currently uses the most simple evaluation function: piece values. A pawn is worth one point, knights and bishops are worth three points, rooks are worth five points, and queens are worth nine points. There is a great deal of room for improvement with regards to this evaluation function, with the most obvious of potential improvements being the consideration of piece position. As any chess player knows, a pawn or knight in the centre of the board is generally more valuable than one on the edge of the board, but the current simple evaluation function draws no distinction. Advanced chess engines like Stockfish will naturally use more sophisticated evaluation techniques.

Search uses alpha-beta pruning, which builds upon the minimax algorithm. Minimax considers both the moves available to a player as well as the subsequent moves that the opponent may make in response. In particular, it considers the best opponent responses to the player's moves and selects the move that leads to the best outocme assuming that the opponent makes the best moves available to them. Alpha-beta pruning is an optimization on the minimax algorithm that reduces the search space without overlooking any potentially better move.

The engine makes a decent opponent for a low-intermediate chess player like myself. It only considers piece value, so it doesn't have much strategic acumen, but it protects pieces well and plays a conservative game that makes it hard to find a breakthrough.

# Install And Run

A simple way to run the program is to compile with g++. You will need to make sure that you have g++ installed.

1. Clone the repository and navigate to the created directory

```
git clone https://github.com/ellismcdougald/chess-engine.git
cd chess-engine
```

2. Compile main.cpp with g++

```
g++ src/main.cpp -o main.cpp src/Game.cpp src/Board.cpp src/Move.cpp src/MoveGenerator.cpp src/Evaluation.cpp src/Search.cpp
```

3. Run the main executable

```
./main
```

4. Play in the command line. See the example game below.

# Example game

See [example.txt](https://github.com/ellismcdougald/chess-engine/blob/main/example.txt) for an example game.

# Future improvements

As this is a simple implementation, there are numerious improvements that could be implemented. I list a few below that I may revisit in the future.

- Improved evaluation function
- Universal Chess Interface support (which would allow the engine to be used with chess GUIs)
- [Negamax](https://www.chessprogramming.org/Negamax) search
- Faster move generation techniques such as [magic bitboards](https://www.chessprogramming.org/Magic_Bitboards#How_it_works)

# Credit

- The [Chess Programming wiki](chessprogramming.org) is a comprehensive resource for all matters of chess programming. It was referenced extensively for this project.
- The chess engine [Deepov](https://github.com/RomainGoussault/Deepov), by Romain Goussault, was lightly referenced as an example for how certain chess programming techniques can be implemented in C++.
