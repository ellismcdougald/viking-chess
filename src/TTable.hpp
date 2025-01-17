/*
 * Transposition table class.
 * Database for results of previous searches.
 */

#ifndef TTABLE_HPP // GUARD
#define TTABLE_HPP // GUARD

#include "Move.hpp"

namespace TTEntryType {
enum Value { NONE = 0, EXACT = 1, LOWER = 2, UPPER = 3 };
};

class TTEntry {
public:
  TTEntry();
  TTEntry(uint64_t zkey, TTEntryType::Value type, Move best_move, uint8_t depth,
          int score);

  inline uint64_t get_zkey() { return zkey; }
  inline TTEntryType::Value get_type() { return type; }
  inline Move get_best_move() { return best_move; }
  inline uint8_t get_depth() { return depth; }
  inline int get_score() { return score; }

private:
  uint64_t zkey;
  TTEntryType::Value type;
  Move best_move;
  uint8_t depth;
  int score;
};

// hardcode to 1024 entries for now
class TTable {
public:
  TTable();
  TTEntry &probe_entry(uint64_t zkey, unsigned depth);
  void set_entry(uint64_t zkey, int depth, TTEntryType::Value type,
                 Move best_move, int score);

private:
  static const unsigned size = 4096;
  TTEntry t_table[4096];
};

#endif // GUARD
