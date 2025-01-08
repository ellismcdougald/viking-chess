/*
 * MoveGenerator class.
 */

#ifndef MOVE_GENERATOR_HPP // GUARD
#define MOVE_GENERATOR_HPP

#include "globals.hpp"
#include "Move.hpp"
#include "Board.hpp"
#include "MoveList.hpp"

#include <array>

class MoveGenerator {
public:
  // Constructor:
  MoveGenerator();

  // Generate legal moves:
  MoveList generate_legal_moves(Board &board, Color color);

  // Pseudo-legal moves:
  MoveList generate_pseudo_legal_moves(Board &board, Color color);
  void add_pseudo_legal_pawn_moves(Board &board, Color color, MoveList& moves);
  void add_pseudo_legal_knight_moves(Board &board, Color color, MoveList& movess);
  void add_pseudo_legal_bishop_moves(Board &board, Color color, MoveList& moves);
  void add_pseudo_legal_rook_moves(Board &board, Color color, MoveList& moves);
  void add_pseudo_legal_queen_moves(Board &board, Color color, MoveList& moves);
  void add_pseudo_legal_king_moves(Board &board, Color color, MoveList& moves);
  void add_pseudo_legal_piece_moves(Board &board, Color color, Piece piece, MoveList& moves);
  void add_pseudo_legal_en_passant_moves(Board &board, Color color, MoveList& moves);

  void add_legal_castle_moves(Board &board, Color color, MoveList& moves);
  void add_legal_kingside_castle_move(Board &board, Color color, MoveList& moves);
  void add_legal_queenside_castle_move(Board &board, Color color, MoveList& moves);

  // Move types:
  void add_quiet_moves(); // TODO: parameters
  void add_double_pawn_push_moves(); // TODO: parameters
  void add_capture_moves(); // TODO: parameters
  void add_promotion_moves(); // TODO: parameters
  void add_promotion_capture_moves(); // TODO: parameters
  void add_en_passant_moves(); // TODO: parameters
  void add_castle_moves(); // TODO: parameters

  // Helpers:
  void add_moves(bitboard origin, bitboard all_destinations, char flag, MoveList& moves);
  void add_promotion_moves(bitboard origin, bitboard all_destinations, bool capture, MoveList& moves);

  // Debug:
  uint64_t perft(int depth, Board &board, Color color);
  std::array<uint64_t, 3> detailed_perft(int depth, Board &board, Color color);
  uint64_t divide(int depth, Board &board, Color color);
  uint64_t fast_perft(int depth, Board &board);
  uint64_t pl_perft(int depth, Board& board);
};

#endif
