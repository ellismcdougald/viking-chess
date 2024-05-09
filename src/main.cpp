#include "UCI.hpp"
#include "Board.hpp"
#include "MoveGenerator.hpp"


int main() {
  Uci interface;
  interface.main_loop();
  return 0;
}


/*
int main() {
  Uci interface;
  Board board;
  MoveGenerator move_gen;

  board.initialize_board_starting_position();
  std::vector<Move> moves = move_gen.generate_legal_moves(board, WHITE);
}
*/
