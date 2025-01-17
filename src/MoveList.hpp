/*
 * Array of moves.
 */

#ifndef MOVE_LIST_HPP
#define MOVE_LIST_HPP

#include "Move.hpp"
#include "globals.hpp"

#include <array>

class MoveList {
public:
  Move moves[256];
  size_t count;

  MoveList();
  inline void add_move(Move move) { moves[count++] = move; }
  inline size_t size() { return count; }

  Move &operator[](size_t i) { return moves[i]; }
};

#endif
