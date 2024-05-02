/*
 * Evaluation class.
 * Contains the evaluate_position function, which determines white's chances of winning for a given position.
 */

#ifndef EVALUATION_HPP // GUARD
#define EVALUATION_HPP // GUARD

#include <stdint.h>
#include "Board.hpp"

typedef bitboard uint64_t;

class Evaluation {
public:
  // Constructor:
  Evaluation();

  // Evaluate:
  uint8_t evaluate(Board &board);
  
private:
  // Helpers:
  int count_set_bits(bitboard positions);
};

#endif // GUARD
