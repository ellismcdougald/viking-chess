/*
 * Search class.
 */

#ifndef SEARCH_HPP // GUARD
#define SEARCH_HPP // GUARD

#include "MoveGenerator.hpp"
#include "Evaluation.hpp"
#include "Board.hpp"
#include "MoveList.hpp"
#include "TTable.hpp"

class Search {
public:
  // Constructor:
  Search();

  // Getters:
  Move get_best_move();

  // Root:
  int alpha_beta_max_root(int alpha, int beta, int depth_left, Board &board, MoveGenerator &move_gen, Evaluation &eval);
  int alpha_beta_max_root(int alpha, int beta, int depth_left, Board &board, MoveGenerator &move_gen, Evaluation &eval, unsigned time_limit);
  
  // Alpha beta:
  int alpha_beta_max(int alpha, int beta, int depth_left, Board &board, MoveGenerator &move_gen, Evaluation &eval);
  int alpha_beta_min(int alpha, int beta, int depth_left, Board &board, MoveGenerator &move_gen, Evaluation &eval);
private:
  Move best_move;

  // Negamax:
  int negamax(int depth, Board& board, MoveGenerator& move_gen, Evaluation& eval);
  int negamax_root(int depth, Board& board, MoveGenerator& move_gen, Evaluation &eval);

  // Iterative Deepening:
  int negamax_id(int depth, int alpha, int beta, Board& board, MoveGenerator& move_gen, Evaluation &eval);
  int negamax_root_iterative_deepening(unsigned time_limit, Board& board, MoveGenerator& move_gen, Evaluation &eval);
  // TODO implement iterative deepening with time management

private:
  TTable t_table;
  unsigned nodes_evaluated;
};

#endif // GUARD
