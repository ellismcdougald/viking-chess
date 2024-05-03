#ifndef SEARCH_CPP // GUARD
#define SEARCH_CPP // GUARD

#include "Search.hpp"

// Constructor:
Search::Search() {}

// Alpha beta:
int Search::alpha_beta_max(int alpha, int beta, int depth_left, Board &board, MoveGenerator &move_gen, Evaluation &eval) {
  if(depth_left == 0) return eval.evaluate(board);

  std::vector<Move> moves = move_gen.generate_legal_moves(board, board.get_turn_color());
  int score;
  for(Move move : moves) {
    board.execute_move(move);
    score = alpha_beta_min(alpha, beta, depth_left - 1, board, move_gen, eval);
    board.undo_move(move);
    if(score >= beta) return beta;
    if(score > alpha) alpha = score;
  }
  return alpha;
}

int Search::alpha_beta_min(int alpha, int beta, int depth_left, Board &board, MoveGenerator &move_gen, Evaluation &eval) {
  if(depth_left == 0) return -eval.evaluate(board);

  std::vector<Move> moves = move_gen.generate_legal_moves(board, board.get_turn_color());
  int score;
  for(Move move : moves) {
    board.execute_move(move);
    score = alpha_beta_max(alpha, beta, depth_left - 1, board, move_gen, eval);
    board.undo_move(move);
    if(score <= alpha) return alpha;
    if(score < beta) beta = score;
  }
  return beta;
}

#endif // GUARD
