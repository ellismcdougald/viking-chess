#ifndef MOVE_GENERATOR_CPP // GUARD
#define MOVE_GENERATOR_CPP // GUARD

#include "MoveGenerator.hpp"

MoveGenerator::MoveGenerator() {}

void MoveGenerator::add_pseudo_legal_pawn_moves(Board &board, Color color, std::vector<Move> &moves) {
  bitboard moving_pawns = board.get_piece_positions(PAWN, color);
  bitboard opposing_pieces = board.get_all_piece_positions(negate_color(color));
  bitboard current_position, capture_squares, single_push_squares, double_push_squares;
  for(bitboard mask = 1; mask > 0; mask <<= 1) {
    current_position = moving_pawns & mask;
    if(current_position) {
      bitboard single_push_squares = board.get_pawn_single_push(current_position, color) & ~opposing_pieces;
      add_moves(current_position, single_push_squares, 0, moves);
      bitboard double_push_squares = board.get_pawn_double_push(current_position, color) & ~opposing_pieces;
      add_moves(current_position, double_push_squares, 1, moves);
      bitboard capture_squares = board.get_piece_attacks(PAWN, current_position, color) & opposing_pieces;
      add_moves(current_position, capture_squares, 4, moves);
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
