#ifndef UCI_CPP // GUARD
#define UCI_CPP // GUARD

#include "UCI.hpp"
#include <iostream>
#include <sstream>      // std::istringstream
#include <string>       // std::string



// Constructor:
Uci::Uci() : move_gen(), board(), search(), eval() {}

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

/*
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
    } else if(current_input == "print") {
      board.print();
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
    std::cin >> next_string;
    while(next_string != "\n") {
      Move move = get_move_from_str(next_string);
      if(move.is_null()) continue;
      board.execute_move(move);

      std::cin >> next_string;
    }
  }
  std::cout << "done\n";
}
*/


void Uci::main_loop() {
  std::string line, token;

  while(std::getline(std::cin, line)) {
    
    std::istringstream line_stream(line);
    line_stream >> std::skipws >> token;

    if(token == "position") {
      handle_position(line_stream);
    } else if(token == "print") {
      board.print();
    } else if(token == "go") {
      // TODO: give search its own thread
      search.alpha_beta_max_root(-10000, 10000, 5, board, move_gen, eval);
      std::cout << search.get_best_move().to_uci_notation() << "\n";
    }
  }
}


void Uci::handle_position(std::istringstream& stream) {
  std::string token;
  stream >> token;
  
  if(token == "startpos") {
    board.clear();
    board.initialize_board_starting_position();
  } else {
    return;
  }

  stream >> token;
  if(token == "moves") {
    while(stream >> token) {
      Move move = get_move_from_str(token);
      if(move.is_null()) continue;
      board.execute_move(move);
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
