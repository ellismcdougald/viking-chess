#ifndef UCI_CPP // GUARD
#define UCI_CPP // GUARD

#include "UCI.hpp"
#include <iostream>

// Constructor:
Uci::Uci() {}

// Main loop:
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
    } else if(strncmp(input_line.c_str(), position_str.c_str(), position_str.size())) {
      std::cout << "position!" << std::endl;
      // TODO: handle position
    } else if(input_line == "ucinewgame") {
      // TODO create new game
    } else if(strncmp(input_line.c_str(), go_str.c_str(), go_str.size())) {
      // TODO handle go
    }
  }
}

#endif
