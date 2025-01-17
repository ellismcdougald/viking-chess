/*
 * Transposition table implementation.
 */

#ifndef TTABLE_CPP // GUARD
#define TTABLE_CPP // GUARD

#include "TTable.hpp"

// TTEntry implementation:
TTEntry::TTEntry() {}

TTEntry::TTEntry(uint64_t zkey, TTEntryType::Value type, Move best_move,
                 uint8_t depth, int score) {
  this->zkey = zkey;
  this->type = type;
  this->best_move = best_move;
  this->depth = depth;
  this->score = score;
}

// TTable implementation:
Move empty_move;
TTEntry empty_entry(0, TTEntryType::Value::NONE, empty_move, 0, 0);

TTable::TTable() {}

TTEntry &TTable::probe_entry(uint64_t zkey, unsigned depth) {
  uint64_t index = zkey % size;
  if (t_table[index].get_type() != TTEntryType::Value::NONE &&
      t_table[index].get_zkey() == zkey &&
      t_table[index].get_depth() >= depth) {
    return t_table[index];
  }
  return empty_entry;
}

void TTable::set_entry(uint64_t zkey, int depth, TTEntryType::Value type,
                       Move best_move, int score) {
  uint64_t index = zkey % size;
  if (t_table[index].get_type() == TTEntryType::Value::NONE ||
      depth >= t_table[index].get_depth()) {
    TTEntry new_entry(zkey, type, best_move, depth, score);
    t_table[index] = new_entry;
  }
}

#endif // GUARD
