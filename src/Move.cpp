/*
 * Move class implementation.
 */

#ifndef MOVE_CPP // GUARD
#define MOVE_CPP // GUARD

#include "Move.hpp"
#include"iostream"

// Constructor:
Move::Move(char origin_column, uint8_t origin_row, char dest_column, char dest_row, char flag) {
  set_origin_column(origin_column);
  set_origin_row(origin_row);
  set_dest_column(dest_column);
  set_dest_row(dest_row);
  set_flag(flag);
}

Move::Move(bitboard origin, bitboard destination, char flag) {
  std::string origin_str = get_row_col_from_position(origin);
  std::string dest_str = get_row_col_from_position(destination);

  set_origin_column(origin_str[0]);
  set_origin_row(origin_str[1] - '0');
  set_dest_column(dest_str[0]);
  set_dest_row(dest_str[1] - '0');
  set_flag(flag);
}

// Getters:
bitboard Move::get_origin() {
  uint8_t origin_row_int = (0x1C00 & move_rep) >> 10; // 0 - 7
  uint8_t origin_col_int = (0xE000 & move_rep) >> 13; // 0 - 7

  return get_position_from_row_col(origin_row_int, origin_col_int);
}

bitboard Move::get_destination() {
  uint8_t dest_row_int = (0x70 & move_rep) >> 4; // 0 - 7
  uint8_t dest_col_int = (0x380 & move_rep) >> 7; // 0 - 7

  return get_position_from_row_col(dest_row_int, dest_col_int);
}

bitboard Move::get_flags() {
  return move_rep & 0xF;
}

// Setters:
void Move::set_origin_column(char origin_column) {
  char col_rep = origin_column - 97;
  move_rep &= ~0xE000;
  move_rep |= (col_rep << 13);
}
void Move::set_origin_row(char origin_row) {
  origin_row -= 1;
  move_rep &= ~0x1C00;
  move_rep |= (origin_row << 10);
}

void Move::set_dest_column(char dest_column) {
  char col_rep = dest_column - 97;
  move_rep &= ~0x0380;
  move_rep |= (col_rep << 7);
}

void Move::set_dest_row(char dest_row) {
  dest_row -= 1;
  move_rep &= ~0x0070;
  move_rep |= (dest_row << 4);
}

void Move::set_flag(char flag) {
  move_rep &= ~0xF;
  move_rep |= flag;
}

// Printers:
void Move::print_binary(uint16_t move_rep) {
  for(uint16_t mask = 0x8000; mask > 0; mask >>= 1) {
    std::cout << ((move_rep & mask) ? '1' : '0');
  }
  std::cout << "\n";
}

void Move::print() {
  std::cout << get_row_col_from_position(get_origin()) << get_row_col_from_position(get_destination()) << "\n";
}

// Equality:
bool Move::move_equals(Move &other_move) {
  return move_rep == other_move.move_rep;
}

// Helpers:
bitboard Move::get_position_from_row_col(uint8_t row, uint8_t col) {
  bitboard position = 1;

  for(char row_index = 0; row_index < row; row_index++) {
    position <<= 8;
  }
  
  for(char col_index = 7; col_index > col; col_index--) {
    position <<= 1;
  }
  
  return position;
}

std::string Move::get_row_col_from_position(bitboard position) {
  std::array<char, 8> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  std::string row_col = "00";
  bitboard mask = 1;
  for(int row = 0; row <= 7; row++) {
    for(int col = 7; col >= 0; col--) {
      if(mask & position) {
	row_col[0] = col + 'a';
	row_col[1] = row + '1';
	return row_col;
      }
      mask <<= 1;
    }
  }
  return "00";
}

#endif // GUARD
