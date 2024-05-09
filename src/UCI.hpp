/*
 * Handles Universal Chess Interface functions.
 */

#ifndef UCI_HPP // GUARD
#define UCI_HPP // GUARD

#include "Board.hpp"
#include "MoveGenerator.hpp"

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

  
  void handle_position();
  Move get_move_from_str(std::string move_str);
  
};

#endif
