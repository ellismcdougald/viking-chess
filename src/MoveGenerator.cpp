#ifndef MOVE_GENERATOR_CPP // GUARD
#define MOVE_GENERATOR_CPP // GUARD

#include "MoveGenerator.hpp"

MoveGenerator::MoveGenerator() {}

std::vector<Move> MoveGenerator::generate_pseudo_legal_moves(Board &board, Color color) {
  std::vector<Move> pseudo_legal_moves;
  add_pseudo_legal_pawn_moves(board, color, pseudo_legal_moves);
  add_pseudo_legal_piece_moves(board, color, KNIGHT, pseudo_legal_moves);
  add_pseudo_legal_piece_moves(board, color, BISHOP, pseudo_legal_moves);
  add_pseudo_legal_piece_moves(board, color, ROOK, pseudo_legal_moves);
  add_pseudo_legal_piece_moves(board, color, QUEEN, pseudo_legal_moves);
  add_pseudo_legal_piece_moves(board, color, KING, pseudo_legal_moves);
  return pseudo_legal_moves;
}

// Needs update to consider promotion moves
void MoveGenerator::add_pseudo_legal_pawn_moves(Board &board, Color color, std::vector<Move> &moves) {
  bitboard moving_pawns = board.get_piece_positions(PAWN, color);
  bitboard other_pieces = board.get_all_piece_positions(color);
  bitboard opposing_pieces = board.get_all_piece_positions(negate_color(color));
  bitboard current_position, capture_squares, single_push_squares, double_push_squares;
  for(bitboard mask = 1; mask > 0; mask <<= 1) {
    current_position = moving_pawns & mask;
    if(current_position) {
      single_push_squares = board.get_pawn_single_push(current_position, color) & ~opposing_pieces & ~other_pieces;
      add_moves(current_position, single_push_squares, 0, moves);
      double_push_squares = board.get_pawn_double_push(current_position, color) & ~opposing_pieces & ~other_pieces;
      add_moves(current_position, double_push_squares, 1, moves);
      capture_squares = board.get_piece_attacks(PAWN, current_position, color) & opposing_pieces;
      add_moves(current_position, capture_squares, 4, moves);
    }
  }
}

void MoveGenerator::add_pseudo_legal_piece_moves(Board &board, Color color, Piece piece, std::vector<Move> &moves) {
  bitboard moving_pieces = board.get_piece_positions(piece, color);
  bitboard other_pieces = board.get_all_piece_positions(color);
  bitboard opposing_pieces = board.get_all_piece_positions(negate_color(color));

  bitboard current_position, destination_squares, quiet_squares, capture_squares;
  for(bitboard mask = 1; mask > 0; mask <<= 1) {
    current_position = moving_pieces & mask;
    if(current_position) {
      destination_squares = board.get_piece_attacks(piece, current_position, color) & ~other_pieces;
      quiet_squares = destination_squares & ~opposing_pieces;
      add_moves(current_position, quiet_squares, 0, moves);
      capture_squares = destination_squares & opposing_pieces;
      add_moves(current_position, quiet_squares, 4, moves);
    }
  }
}

void MoveGenerator::add_moves(bitboard origin, bitboard all_destinations, char flag, std::vector<Move> &moves) {
  bitboard current_destination;
  for(bitboard mask = 1; mask > 0; mask <<= 1) {
    current_destination = all_destinations & mask;
    if(current_destination) {
      Move move(origin, current_destination, flag);
      moves.push_back(move);
    }
  }
}

#endif
