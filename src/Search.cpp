#ifndef SEARCH_CPP // GUARD
#define SEARCH_CPP // GUARD

#include "Search.hpp"
#include <algorithm>
#include <random>

// Constructor:
Search::Search() : best_move(0, 0, -1) {}

// Getters:
Move Search::get_best_move() {
  return best_move;
}

// Root:
int Search::alpha_beta_max_root(int alpha, int beta, int depth_left, Board &board, MoveGenerator &move_gen, Evaluation &eval) {
  if(depth_left == 0) return eval.evaluate(board);

  MoveList moves = move_gen.generate_legal_moves(board, board.get_turn_color());
  if(moves.size() == 0) {
    Move null_move(0, 0, 0);
    best_move = null_move;
    return 0;
  } else {
    best_move = moves[0];
  }
  
  int score;
  for(int i = 0; i < moves.size(); i++) {
    board.execute_move(moves[i]);
    score = alpha_beta_min(alpha, beta, depth_left - 1, board, move_gen, eval);
    board.undo_move(moves[i]);
    if(score >= beta) {
      return beta;
    }
    if(score > alpha) {
      best_move = moves[i];
      alpha = score;
    }
  }
  return alpha;
}

// Alpha beta:
int Search::alpha_beta_max(int alpha, int beta, int depth_left, Board &board, MoveGenerator &move_gen, Evaluation &eval) {
  if(depth_left == 0) return eval.evaluate(board);

  MoveList moves = move_gen.generate_legal_moves(board, board.get_turn_color());
  int score;
  for(int i = 0; i < moves.size(); i++) {
    board.execute_move(moves[i]);
    score = alpha_beta_min(alpha, beta, depth_left - 1, board, move_gen, eval);
    board.undo_move(moves[i]);
    if(score >= beta) {
      return beta;
    }
    if(score > alpha) {
      alpha = score;
    }
  }
  return alpha;
}

int Search::alpha_beta_min(int alpha, int beta, int depth_left, Board &board, MoveGenerator &move_gen, Evaluation &eval) {
  if(depth_left == 0) return -eval.evaluate(board);

  MoveList moves = move_gen.generate_legal_moves(board, board.get_turn_color());
  int score;
  for(int i = 0; i < moves.size(); i++) {
    board.execute_move(moves[i]);
    score = alpha_beta_max(alpha, beta, depth_left - 1, board, move_gen, eval);
    board.undo_move(moves[i]);
    if(score <= alpha) return alpha;
    if(score < beta) beta = score;
  }
  return beta;
}

#endif // GUARD
