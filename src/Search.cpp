#ifndef SEARCH_CPP // GUARD
#define SEARCH_CPP // GUARD

#include "Search.hpp"
#include <algorithm>
#include <random>

// Constructor:
Search::Search() : best_move(0, 0, -1) {}

// Getters:
Move Search::get_best_move() { return best_move; }

// Root:
int Search::alpha_beta_max_root(int alpha, int beta, int depth_left,
                                Board &board, MoveGenerator &move_gen,
                                Evaluation &eval) {
  if (depth_left == 0) {
    return eval.evaluate(board);
  }

  MoveList moves = move_gen.generate_legal_moves(board, board.get_turn_color());
  if (moves.size() == 0) {
    Move null_move(0, 0, 0);
    best_move = null_move;
    return 0;
  } else {
    best_move = moves[0];
  }

  int score;
  for (int i = 0; i < moves.size(); i++) {
    board.execute_move(moves[i]);
    score = alpha_beta_min(alpha, beta, depth_left - 1, board, move_gen, eval);
    board.undo_move(moves[i]);
    if (score >= beta) {
      return beta;
    }
    if (score > alpha) {
      best_move = moves[i];
      alpha = score;
    }
  }
  return alpha;
}

int Search::alpha_beta_max_root(int alpha, int beta, int depth_left,
                                Board &board, MoveGenerator &move_gen,
                                Evaluation &eval, unsigned time_limit) {
  if (depth_left == 0) {
    return eval.evaluate(board);
  }

  std::chrono::time_point<std::chrono::high_resolution_clock> start_time =
      std::chrono::high_resolution_clock::now();

  MoveList moves = move_gen.generate_legal_moves(board, board.get_turn_color());
  if (moves.size() == 0) {
    Move null_move(0, 0, 0);
    best_move = null_move;
    return 0;
  } else {
    best_move = moves[0];
  }

  int score;
  for (int i = 0; i < moves.size(); i++) {
    std::chrono::time_point<std::chrono::high_resolution_clock> current_time =
        std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(current_time -
                                                              start_time);
    if (elapsed_time.count() > 0.75 * time_limit) {
      return alpha;
    }

    board.execute_move(moves[i]);
    score = alpha_beta_min(alpha, beta, depth_left - 1, board, move_gen, eval);
    board.undo_move(moves[i]);
    if (score >= beta) {
      return beta;
    }
    if (score > alpha) {
      best_move = moves[i];
      alpha = score;
    }
  }
  return alpha;
}

// Alpha beta:
int Search::alpha_beta_max(int alpha, int beta, int depth_left, Board &board,
                           MoveGenerator &move_gen, Evaluation &eval) {
  if (depth_left == 0) {
    return eval.evaluate(board);
  }

  MoveList moves = move_gen.generate_legal_moves(board, board.get_turn_color());
  int score;
  for (int i = 0; i < moves.size(); i++) {
    board.execute_move(moves[i]);
    score = alpha_beta_min(alpha, beta, depth_left - 1, board, move_gen, eval);
    board.undo_move(moves[i]);
    if (score >= beta) {
      return beta;
    }
    if (score > alpha) {
      alpha = score;
    }
  }
  return alpha;
}

int Search::alpha_beta_min(int alpha, int beta, int depth_left, Board &board,
                           MoveGenerator &move_gen, Evaluation &eval) {
  if (depth_left == 0) {
    return -eval.evaluate(board);
  }

  MoveList moves = move_gen.generate_legal_moves(board, board.get_turn_color());
  int score;
  for (int i = 0; i < moves.size(); i++) {
    board.execute_move(moves[i]);
    score = alpha_beta_max(alpha, beta, depth_left - 1, board, move_gen, eval);
    board.undo_move(moves[i]);
    if (score <= alpha) {
      return alpha;
    }
    if (score < beta) {
      beta = score;
    }
  }
  return beta;
}

// Negamax:
int Search::negamax(int depth, Board &board, MoveGenerator &move_gen,
                    Evaluation &eval) {
  if (depth == 0) {
    return eval.evaluate(board);
  }
  int best_score = -999999;
  int score = 0;
  MoveList moves = move_gen.generate_legal_moves(board, board.get_turn_color());
  for (int i = 0; i < moves.size(); i++) {
    board.execute_move(moves[i]);
    score = -negamax(depth - 1, board, move_gen, eval);
    board.undo_move(moves[i]);
    if (score > best_score) {
      best_score = score;
    }
  }
  return best_score;
}

int Search::negamax_root(int depth, Board &board, MoveGenerator &move_gen,
                         Evaluation &eval) {
  int best_score = -999999;
  MoveList moves = move_gen.generate_legal_moves(board, board.get_turn_color());
  for (int i = 0; i < moves.size(); i++) {
    board.execute_move(moves[i]);
    int score = -negamax(depth, board, move_gen, eval);
    board.undo_move(moves[i]);

    if (score > best_score) {
      best_score = score;
      best_move = moves[i];
    }
  }
  return best_score;
}

// Iterative Deepening:
int Search::negamax_id(int depth, int alpha, int beta, Board &board,
                       MoveGenerator &move_gen, Evaluation &eval) {
  if (depth == 0) {
    ++nodes_evaluated;
    return eval.evaluate(board) * (board.get_turn_color() == WHITE ? 1 : -1);
  }

  int previous_alpha = alpha;

  // use tt if possible
  uint64_t position_zkey = board.get_zkey();
  TTEntry tt_entry = t_table.probe_entry(position_zkey, depth);
  if (tt_entry.get_type() == TTEntryType::Value::EXACT) {
    return tt_entry.get_score();
  } else if (tt_entry.get_type() == TTEntryType::Value::UPPER &&
             tt_entry.get_score() <= alpha) {
    return alpha;
  } else if (tt_entry.get_type() == TTEntryType::Value::LOWER &&
             tt_entry.get_score() >= beta) {
    return beta;
  }

  int best_score = -999999;
  MoveList moves = move_gen.generate_legal_moves(board, board.get_turn_color());
  Move local_best_move;
  for (int i = 0; i < moves.size(); i++) {
    board.execute_move(moves[i]);
    int score = -negamax_id(depth - 1, -beta, -alpha, board, move_gen, eval);
    board.undo_move(moves[i]);

    if (score >= beta) {
      t_table.set_entry(position_zkey, depth, TTEntryType::Value::LOWER,
                        moves[i], score);
      return beta;
    }
    if (score > best_score) {
      best_score = score;
      local_best_move = moves[i];

      if (score > alpha) {
        alpha = score;
      }
    }
  }

  if (alpha > previous_alpha) {
    t_table.set_entry(position_zkey, depth, TTEntryType::Value::EXACT,
                      local_best_move, best_score);
  } else {
    t_table.set_entry(position_zkey, depth, TTEntryType::Value::UPPER,
                      local_best_move, alpha);
  }

  return alpha;
}

int Search::negamax_root_iterative_deepening(unsigned time_limit, Board &board,
                                             MoveGenerator &move_gen,
                                             Evaluation &eval) {
  unsigned search_depth = 1;

  // start the clock
  std::chrono::high_resolution_clock::time_point start_time =
      std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point current_time;
  unsigned time_passed;

  nodes_evaluated = 0;

  while (true) {

    std::cout << "starting search depth " << search_depth << std::endl;

    int alpha = -999999;
    int beta = -alpha;
    int score = 0;

    uint64_t position_zkey = board.get_zkey();
    TTEntry tt_entry = t_table.probe_entry(position_zkey, search_depth);

    if (tt_entry.get_type() == TTEntryType::Value::EXACT) { // TT hit
      best_move = tt_entry.get_best_move();
      alpha = tt_entry.get_score();
    } else { // TT miss
      MoveList moves =
          move_gen.generate_legal_moves(board, board.get_turn_color());
      for (int i = 0; i < moves.size(); i++) {
        /*
        // check the clock
        current_time = std::chrono::high_resolution_clock::now();
        time_passed =
        std::chrono::duration_cast<std::chrono::milliseconds>(current_time -
        start_time).count(); if (time_passed > time_limit) { return alpha;
        }
        */

        board.execute_move(moves[i]);
        int score =
            -negamax_id(search_depth - 1, -beta, -alpha, board, move_gen, eval);
        board.undo_move(moves[i]);

        /*
        std::cout << "move ";
        moves[i].print();
        std::cout << std::endl;
        std::cout << "score: " << score << " vs alpha " << alpha << std::endl;
        */

        if (score > alpha) {
          alpha = score;
          best_move = moves[i];
          // std::cout << "new best move ";
          // best_move.print();
          // std::cout << std::endl;
        }
      }

      t_table.set_entry(position_zkey, search_depth, TTEntryType::Value::EXACT,
                        best_move, alpha);

      // check the clock
      current_time = std::chrono::high_resolution_clock::now();
      time_passed = std::chrono::duration_cast<std::chrono::milliseconds>(
                        current_time - start_time)
                        .count();
      if (time_passed > 0.25 * time_limit) {
        return alpha;
      }
    }

    ++search_depth;

    // check the clock
    current_time = std::chrono::high_resolution_clock::now();
    time_passed = std::chrono::duration_cast<std::chrono::milliseconds>(
                      current_time - start_time)
                      .count();

    // send info
    std::cout << "info";
    std::cout << " depth " << search_depth;
    std::cout << " score cp " << alpha;
    std::cout << " nodes " << nodes_evaluated;
    std::cout << " nps " << (float)nodes_evaluated / time_passed * 1000;
    std::cout << " time " << time_passed;
    std::cout << std::endl;

    if (time_passed > 0.5 * time_limit) {
      return alpha;
    }
  }
}

#endif // GUARD
