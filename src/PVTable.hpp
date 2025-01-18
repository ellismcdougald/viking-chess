#ifndef PVTABLE_HPP // GUARD
#define PVTABLE_HPP // GUARD

/*
 * Principal variation table.
 */

#include "Move.hpp"

class PVTable {
public:
  void add_move(unsigned ply, Move &move);
  void print_pv();
  
private:
  static const unsigned MAX_DEPTH = 64; // TODO: perhaps this should be a global option
  Move pv_table[(MAX_DEPTH * MAX_DEPTH + MAX_DEPTH) / 2];
  unsigned pv_length = 0;
};

#endif // GUARD
