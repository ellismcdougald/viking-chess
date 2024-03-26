/*
 * MoveGenerator class.
 */

#ifndef MOVE_GENERATOR_HPP // GUARD
#define MOVE_GENERATOR_HPP

#include "globals.hpp"
#include "Move.hpp"
#include "Board.hpp"

class MoveGenerator {
public:
  // Constructor:
  MoveGenerator();

  // Generate legal moves:
  std::vector<Move> generate_legal_moves(Board &board, Color color);

  // Pseudo-legal moves:
  std::vector<Move> generate_pseudo_legal_moves(Board &board, Color color);
  void add_pseudo_legal_pawn_moves(Board &board, Color color, std::vector<Move> &moves);
  void add_pseudo_legal_knight_moves(Board &board, Color color, std::vector<Move> moves);
  void add_pseudo_legal_bishop_moves(Board &board, Color color, std::vector<Move> moves);
  void add_pseudo_legal_rook_moves(Board &board, Color color, std::vector<Move> moves);
  void add_pseudo_legal_queen_moves(Board &board, Color color, std::vector<Move> moves);
  void add_pseudo_legal_king_moves(Board &board, Color color, std::vector<Move> moves);
  void add_pseudo_legal_piece_moves(Board &board, Color color, Piece piece, std::vector<Move> &moves);
  void add_pseudo_legal_en_passant_moves(Board &board, Color color, std::vector<Move> &moves);

  // Move types:
  void add_quiet_moves(); // TODO: parameters
  void add_double_pawn_push_moves(); // TODO: parameters
  void add_capture_moves(); // TODO: parameters
  void add_promotion_moves(); // TODO: parameters
  void add_promotion_capture_moves(); // TODO: parameters
  void add_en_passant_moves(); // TODO: parameters
  void add_castle_moves(); // TODO: parameters

  void add_moves(bitboard origin, bitboard all_destinations, char flag, std::vector<Move> &moves);
  void add_promotion_moves(bitboard origin, bitboard all_destinations, bool capture, std::vector<Move> &moves);
};

#endif
