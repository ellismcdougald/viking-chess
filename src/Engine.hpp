/*
 * Engine interface.
 */

#include "Board.hpp"
#include "Evaluation.hpp"
#include "MoveGenerator.hpp"
#include "Search.hpp"

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
  bool set_position(std::string fen_str);

  /*
   * Plays the given move on the board.
   * Move should be given in long algebraic notation e.g. e2e4, e1g1, e7e8q
   */
  bool play_move(std::string move_str);

  /*
   * Finds the best engine move.
   */
  void search_best_move();

  inline void show_board() { board.print(); }

  unsigned get_time_for_move();

  // Setters:
  inline void set_white_time(unsigned wtime) {
    white_time = wtime;
    time_set = true;
  }
  inline void set_black_time(unsigned btime) {
    black_time = btime;
    time_set = true;
  }
  inline void set_white_increment(unsigned winc) {
    white_increment = winc;
    time_set = true;
  }
  inline void set_black_increment(unsigned binc) {
    black_increment = binc;
    time_set = true;
  }
  inline void set_moves_to_go(unsigned movestogo) {
    moves_to_go = movestogo;
    time_set = true;
  }

private:
  Board board;
  MoveGenerator move_gen;
  Search search;
  Evaluation eval;

  unsigned time_divider;

  // all in ms
  unsigned white_time;
  unsigned black_time;
  unsigned white_increment; // increment per move
  unsigned black_increment;
  unsigned moves_to_go; // moves to go until next time control
  bool time_set;
};

#endif // GUARD
