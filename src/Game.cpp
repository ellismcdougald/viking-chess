#ifndef GAME_CPP // GUARD
#define GAME_CPP // GUARD

#include "Game.hpp"

Game::Game() : board(), move_gen(), search(), eval() {
  colors[0] = "White";
  colors[1] = "Black";
  board.initialize_board_starting_position();
}

void Game::run_game() {
  bool keep_playing = true;
  while (keep_playing) {
    if (board.get_turn_color() == WHITE) {
      keep_playing = make_turn_user();
    } else {
      keep_playing = make_turn_engine();
    }
  }

  if (board.is_checked(board.get_turn_color())) {
    std::cout << "Checkmate!. " << colors[negate_color(board.get_turn_color())]
              << " wins." << std::endl;
  } else {
    std::cout << "Stalemate. It's a tie." << std::endl;
  }
}

bool Game::make_turn_user() {
  std::string user_move;

  std::cout << colors[board.get_turn_color()] << ": It is your turn.\n";
  board.print();

  MoveList legal_moves =
      move_gen.generate_legal_moves(board, board.get_turn_color());
  if (legal_moves.size() == 0) {
    std::cout << "no legal moves\n";
    return false;
  }

  while (true) {
    std::cout << "Enter a legal move (i.e. d2d4): ";
    std::cin >> user_move;
    Move move = get_move_from_str(user_move, legal_moves);

    if (move.is_null()) {
      std::cout << "Not a legal move. ";
    } else {
      board.execute_move(move);
      break;
    }
  }

  board.print();

  std::cout << std::endl;

  return true;
}

bool Game::make_turn_engine() {
  search.alpha_beta_max_root(-10000, 10000, 5, board, move_gen, eval);
  Move engine_move = search.get_best_move();
  if (engine_move.is_null()) {
    return false;
  }
  std::cout << colors[board.get_turn_color()] << ": Engine plays move ";
  engine_move.print();
  std::cout << std::endl << std::endl;
  board.execute_move(engine_move);

  return true;
}

Move Game::get_move_from_str(std::string move_str, MoveList &legal_moves) {
  for (int i = 0; i < legal_moves.size(); i++) {
    if (move_str == legal_moves[i].to_uci_notation()) {
      return legal_moves[i];
    }
  }
  Move move(0, 0, 0);
  return move;
}

void Game::set_board_position(std::string fen_str) {
  board.clear();
  board.initialize_fen(fen_str);
}

void Game::print_board() { board.print(); }

#endif // GUARD
