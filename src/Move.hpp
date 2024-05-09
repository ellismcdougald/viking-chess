/*
 * Move representation.
 */

#ifndef MOVE_HPP // GUARD
#define MOVE_HPP // GUARD

#include <stdint.h>
#include <string>

typedef uint64_t bitboard;

/**
 * Move is represented with a 16-bit integer.
 * This is a minimal representation. Moving and captured pieces will be looked up on the board at move time.
 * Bits 1-3: start column (0 - 7)
 * Bits 4-6: start row (0 - 7)
 * Bits 7-9: end column (0 - 7)
 * Bits 10-12: end row (0 - 7)
 * Bits 13 - 16: flags
 * See: https://www.chessprogramming.org/Encoding_Moves#Check_Flag
 */
class Move {
public:
  // Flags:
  static const uint16_t quiet_flag; // 0
  static const uint16_t double_pawn_push_flag; // 1
  static const uint16_t king_castle_flag; // 2
  static const uint16_t queen_castle_flag; // 3
  static const uint16_t capture_flag; // 4
  static const uint16_t en_passant_capture_flag; // 5
  static const uint16_t knight_promotion_flag; // 8
  static const uint16_t bishop_promotion_flag; // 9
  static const uint16_t rook_promotion_flag; // 10
  static const uint16_t queen_promotion_flag; // 11
  static const uint16_t knight_promotion_capture_flag; // 12
  static const uint16_t bishop_promotion_capture_flag; // 13
  static const uint16_t rook_promotion_capture_flag; // 14
  static const uint16_t queen_promotion_capture_flag; // 15

  // Constructors:
  /**
   * Simple constructor.
   * Accepts columns as letters ('a' - 'h'). Stores as integers (0 - 7).
   * Accepts rows as integers 1 - 8. Stores as integers 0 - 7.
   * Should be given one of the 14 move flags depending on type of move.
   */
  Move(char origin_column, uint8_t origin_row, char dest_column, char dest_row, char flag);
  Move(bitboard origin, bitboard destination, char flag);

  // Getters:
  bitboard get_origin();
  bitboard get_destination();
  bitboard get_flags();
  bool is_double_pawn_push();
  bool is_null();

  // Setters:
  void set_origin_column(char origin_column);
  void set_origin_row(char origin_row);
  void set_dest_column(char dest_column);
  void set_dest_row(char dest_row);
  void set_flag(char flag);

  // Printers:
  void print_binary(uint16_t move_rep);
  void print();
  void print_full();

  // To String:
  std::string to_uci_notation();

  // Equality:
  bool move_equals(Move &other_move);
  
private:
  uint16_t move_rep;

  // Helpers:
  bitboard get_position_from_row_col(uint8_t row, uint8_t col);
  std::string get_row_col_from_position(bitboard position);
};

#endif
