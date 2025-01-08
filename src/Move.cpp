/*
 * Move class implementation.
 */

#ifndef MOVE_CPP // GUARD
#define MOVE_CPP // GUARD

#include "Move.hpp"
#include"iostream"

// Constructor:
Move::Move(char origin_column, uint8_t origin_row, char dest_column, char dest_row, char flag) {
  bitboard origin = get_position_from_row_col(origin_row - 1, origin_column - 97);
  bitboard destination = get_position_from_row_col(dest_row - 1, dest_column - 97);
  set_origin(origin);
  set_destination(destination);
  set_flag(flag);
}

Move::Move(bitboard origin, bitboard destination, char flag) {
  //std::string origin_str = get_row_col_from_position(origin);
  //std::string dest_str = get_row_col_from_position(destination);

  //set_origin_column(origin_str[0]);
  //set_origin_row(origin_str[1] - '0');
  //set_dest_column(dest_str[0]);
  //set_dest_row(dest_str[1] - '0');
  set_origin(origin);
  set_destination(destination);
  set_flag(flag);
}

Move::Move() {}

// Getters:
bool Move::is_double_pawn_push() {
  return get_flags() == 1;
}

bool Move::is_null() {
  return get_origin() == get_destination();
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

// Printers:
void Move::print_binary(uint16_t move_rep) {
  for(uint16_t mask = 0x8000; mask > 0; mask >>= 1) {
    std::cout << ((move_rep & mask) ? '1' : '0');
  }
  std::cout << "\n";
}

void Move::print() {
  if(is_null()) std::cout << "Null";
  else std::cout << get_row_col_from_position(get_origin()) << get_row_col_from_position(get_destination());
}

void Move::print_full() {
  std::cout << get_row_col_from_position(get_origin()) << get_row_col_from_position(get_destination()) << " -- " << get_flags() << "\n";
}

// To String:
std::string Move::to_uci_notation() {
  std::string move_str = get_row_col_from_position(get_origin());
  move_str.append(get_row_col_from_position(get_destination()));
  switch(get_flags()) {
  case 8:
    move_str.append("n");
    break;
  case 9:
    move_str.append("b");
    break;
  case 10:
    move_str.append("r");
    break;
  case 11:
    move_str.append("q");
    break;
  case 12:
    move_str.append("n");
    break;
  case 13:
    move_str.append("b");
    break;
  case 14:
    move_str.append("r");
    break;
  case 15:
    move_str.append("q");
    break;
  }
  return move_str;
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
