/*
 * UCI interface implementation.
 */

#include "Uci.hpp"
#include <iostream>
#include <sstream>
#include <thread>

#ifndef UCI_CPP // GUARD
#define UCI_CPP // GUARD

Uci::Uci() {}

void Uci::loop() {
  std::string line;
  std::string token;

  while (std::getline(std::cin, line)) {
    std::istringstream input(line);
    token.clear();
    input >> std::skipws >> token;

    if (token == "uci") {
      std::cout << "id name ellis-engine" << std::endl;
      std::cout << "id author Ellis McDougald" << std::endl;
      // TODO: optional options
      std::cout << "uciok" << std::endl;
    } else if(token == "isready") {
      std::cout << "readyok" << std::endl;
    } else if (token == "position") {
      input >> token;
      if (token == "startpos") {
	std::string start_pos_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	engine.set_position(start_pos_fen);
      } else if (token == "fen") {
	input >> token;
	engine.set_position(token);
      }

      input >> token;
      if(token == "moves") {
	while(input >> token) {
	  engine.play_move(token);
	}
      }
    } else if (token == "show") {
      engine.show_board();
    } else if (token == "go") {
      unsigned val;
      while (input >> token) {
	input >> val;
	if (token == "wtime") engine.set_white_time(val);
	else if (token == "btime") engine.set_black_time(val);
	else if (token == "winc") engine.set_white_increment(val);
	else if (token == "binc") engine.set_black_increment(val);
	else if (token == "movestogo") engine.set_moves_to_go(val);
      }
      // start search on another thread
      std::thread search_thread([this]() { search(); });
      search_thread.detach();
    }
  }
}

#endif // GUARD
