#ifndef GAME_HPP // GUARD
#define GAME_HPP // GUARD

#include "Board.hpp"
#include "Evaluation.hpp"
#include "MoveGenerator.hpp"
#include "Search.hpp"

class Game {
public:
  // Constructor:
  Game();

  // Game:
  void run_game();
  bool make_turn_user();
  bool make_turn_engine();

  // Other:
  void set_board_position(std::string fen_str);
  void print_board();

private:
  Board board;
  MoveGenerator move_gen;
  Search search;
  Evaluation eval;

  std::array<std::string, 2> colors;

  Move get_move_from_str(std::string move_str, MoveList &legal_moves);
};

#endif
