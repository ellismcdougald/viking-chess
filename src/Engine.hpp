/*
 * Engine interface.
 */

#include "Board.hpp"
#include "MoveGenerator.hpp"
#include "Search.hpp"
#include "Evaluation.hpp"

#ifndef ENGINE_HPP // GUARD
#define ENGINE_HPP // GUARD

class Engine {
public:
  Engine();

  /*
   * Starts a new game.
   */
  void start_new_game(); // TODO

  /*
   * Sets up the position described in fen on the board
   * Returns true if position set up successfully, false otherwise
   */
  bool set_position(std::string fen_str); // TODO

  /*
   * Plays the given move on the board.
   * Move should be given in long algebraic notation e.g. e2e4, e1g1, e7e8q
   */
  bool play_move(std::string move_str); // TODO

private:
  Board board;
  MoveGenerator move_gen;
  Search search;
  Evaluation eval;
};

#endif // GUARD
