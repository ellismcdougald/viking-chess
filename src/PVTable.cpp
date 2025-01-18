#ifndef PVTABLE_CPP // GUARD
#define PVTABLE_CPP // GUARD

/*
 * Principal variation table implementation.
 */

#include "PVTable.hpp"

void PVTable::add_move(unsigned ply, Move& move) {
  pv_length = std::max(pv_length, ply + 1);
  unsigned pv_index = (ply * (2 * MAX_DEPTH + 1 - ply)) / 2;
  unsigned pv_next_index = pv_index + MAX_DEPTH - ply;
  pv_table[pv_index] = move;
  memcpy(pv_table + pv_index + 1, pv_table + pv_next_index, sizeof(Move) * pv_length);
}

void PVTable::print_pv() {
  for (int i = 0; i < pv_length; ++i) {
    pv_table[i].print();
    std::cout << " ";
  }
}

#endif // GUARD
