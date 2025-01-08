#include "globals.hpp"

#ifndef GLOBALS_CPP // GUARD
#define GLOBALS_CPP

uint64_t get_position_from_row_col(uint8_t row, uint8_t col) {
  uint64_t position = 1;

  for(char row_index = 0; row_index < row; row_index++) {
    position <<= 8;
  }
  
  for(char col_index = 7; col_index > col; col_index--) {
    position <<= 1;
  }
  
  return position;
}

bitboard position_string_to_bitboard(std::string position_str) {
  char col = 7 - (position_str[0] - 'a');
  char row = position_str[1] - '0' - 1;

  bitboard position = 1;
  for(char row_index = 0; row_index < row; row_index++) {
    position <<= 8;
  }
  for(char col_index = 0; col_index < col; col_index++) {
    position <<= 1;
  }

  return position;
}

void print_bitboard(bitboard bb) {
  bitboard mask = (bitboard) 1 << 63;
  for(int i = 0; i < 64; i++) {
    std::cout << (mask & bb ? 1 : 0);
    mask >>= 1;
    if((i + 1) % 8 == 0) std::cout << "\n";
  }
}

#endif
