#ifndef EVALUATION_CPP // GUARD
#define EVALUATION_CPP // GUARD

#include "Evaluation.hpp"
#include "globals.cpp"

// Constructor:
Evaluation::Evaluation() {}

// Evaluate:
uint8_t Evaluation::evaluate(Board &board) {
  std::array<Piece, 5> piece_array = {PAWN, KNIGHT, BISHOP, ROOK, QUEEN};
  std::array<int, 5> piece_weights_array = {1, 3, 3, 5, 9};
  int score = 0;
  for(int i = 0; i < 5; i++) {
    score += count_set_bits(board.get_piece_positions(piece_array[i], WHITE)) * piece_weights_array[i];
    score -= count_set_bits(board.get_piece_positions(piece_array[i], BLACK)) * piece_weights_array[i];
  }

  return score;
}

// Helpers:
int Evaluation::count_set_bits(bitboard positions) {
  int count = 0;
  for(bitboard mask = 1; mask > 0; mask <<= 1) {
    if(positions & mask) count++;
  }
  return count;
}

#endif
