#ifndef UCI_CPP // GUARD
#define UCI_CPP // GUARD

#include "UCI.hpp"
#include <iostream>

// Constructor:
Uci::Uci() : move_gen(), board() {}

// Main loop:
/*
void Uci::main_loop() {
  std::string input_line;
  std::string position_str = "position";
  std::string go_str = "go";
  while(1) {
    std::cin >> input_line;
    if(input_line == "uci") {
      std::cout << "id name EM77 0.0" << std::endl;
      std::cout << "id author Ellis McDougald" << std::endl;
      std::cout << "uciok" << std::endl;
    } else if(input_line == "isready") {
      std::cout << "readyok" << std::endl;
    } else if(input_line.compare(0, position_str.length(), position_str)) {
      std::cout << "position!" << std::endl;
    }
  }
}
*/
void Uci::main_loop() {
  std::string current_input;
  while(1) {
    std::cin >> current_input;
    if(current_input == "uci") {
      std::cout << "id name EM77 0.0" << std::endl;
      std::cout << "id author Ellis McDougald" << std::endl;
      std::cout << "uciok" << std::endl;
    } else if(current_input == "isready") {
      std::cout << "readyok" << std::endl;
    } else if(current_input == "position") {
      handle_position();
    }
  }
}

void Uci::handle_position() {
  std::string position_type;
  std::cin >> position_type;
  if(position_type == "startpos") {
    board.clear();
    board.initialize_board_starting_position();
  }

  std::string next_string;
  std::cin >> next_string;
  if(next_string == "moves") {
    while(std::cin >> next_string) {
      Move move = get_move_from_str(next_string);
      move.print();
    }
  }
}

Move Uci::get_move_from_str(std::string move_str) {
  std::vector<Move> legal_moves = move_gen.generate_legal_moves(board, board.get_turn_color());
  for(int i = 0; i < legal_moves.size(); i++) {
    if(move_str == legal_moves[i].to_uci_notation()) return legal_moves[i];
  }
  Move move(0, 0, 0);
  return move;
}

#endif
