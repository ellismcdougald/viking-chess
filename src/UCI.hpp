/*
 * Handles Universal Chess Interface functions.
 */

#ifndef UCI_HPP // GUARD
#define UCI_HPP // GUARD

#include "Board.hpp"
#include "MoveGenerator.hpp"
#include "Evaluation.hpp"
#include "Search.hpp"

class Uci {
public:
  // Constructor:
  Uci();

  // Main loop:
  void main_loop();
private:
  Board *board_ptr;
  MoveGenerator move_gen;
  Board board;
  Search search;
  Evaluation eval;

  
  void handle_position(std::istringstream& stream);
  Move get_move_from_str(std::string move_str);
  
};

#endif
