/*
 * Evaluation class.
 * Contains the evaluate_position function, which determines white's chances of
 * winning for a given position.
 */

#ifndef EVALUATION_HPP // GUARD
#define EVALUATION_HPP // GUARD

#include "Board.hpp"
#include <stdint.h>

typedef bitboard uint64_t;

class Evaluation {
public:
  // Constructor:
  Evaluation();

  // Evaluate:
  int evaluate(Board &board);

private:
  // Helpers:
  int count_set_bits(bitboard positions);

  // Piece Values:
  static const uint16_t piece_values[6];

  // Piece-Square Tables:
  static const int8_t pawn_square_table[2][64];
  static const int8_t knight_square_table[2][64];
  static const int8_t bishop_square_table[2][64];
  static const int8_t rook_square_table[2][64];
  static const int8_t queen_square_table[2][64];
  static const int8_t king_square_table[2][64];

  static const int8_t piece_square_tables[2][6][64];
};

#endif // GUARD
