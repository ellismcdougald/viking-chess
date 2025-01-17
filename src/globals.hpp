#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <iostream>
#include <stdint.h>
#include <string>

typedef uint64_t bitboard;

enum Piece { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, ALL, NONE };
enum Color { WHITE, BLACK };
enum Direction {
  NORTH,
  EAST,
  SOUTH,
  WEST,
  NORTHEAST,
  NORTHWEST,
  SOUTHEAST,
  SOUTHWEST
};

static const bitboard FILE_A = 0x8080808080808080;
static const bitboard FILE_B = 0x4040404040404040;
static const bitboard FILE_C = 0x2020202020202020;
static const bitboard FILE_D = 0x1010101010101010;
static const bitboard FILE_E = 0x0808080808080808;
static const bitboard FILE_F = 0x0404040404040404;
static const bitboard FILE_G = 0x0202020202020202;
static const bitboard FILE_H = 0x0101010101010101;
static const bitboard RANK_1 = 0xFF;
static const bitboard RANK_2 = 0x00FF;
static const bitboard RANK_7 = 0x00FF000000000000;
static const bitboard RANK_8 = 0xFF00000000000000;

static const bitboard WHITE_KINGSIDE_CASTLE_PATH = 0xE;
static const bitboard WHITE_QUEENSIDE_CASTLE_PATH = 0x38;
static const bitboard BLACK_KINGSIDE_CASTLE_PATH = 0xE00000000000000;
static const bitboard BLACK_QUEENSIDE_CASTLE_PATH = 0x3800000000000000;

static const bitboard starting_white_king_position = 0x8;
static const bitboard starting_white_queen_position = 0x10;
static const bitboard starting_white_rook_position = 0x81;
static const bitboard starting_white_bishop_position = 0x24;
static const bitboard starting_white_knight_position = 0x42;
static const bitboard starting_white_pawn_position = 0xFF00;

static const bitboard starting_black_king_position = 0x800000000000000;
static const bitboard starting_black_queen_position = 0x1000000000000000;
static const bitboard starting_black_rook_position = 0x8100000000000000;
static const bitboard starting_black_bishop_position = 0x2400000000000000;
static const bitboard starting_black_knight_position = 0x4200000000000000;
static const bitboard starting_black_pawn_position = 0x00FF000000000000;

inline bitboard north(bitboard position) { return (position & ~RANK_8) << 8; }
inline bitboard south(bitboard position) { return (position & ~RANK_1) >> 8; }
inline bitboard east(bitboard position) { return (position & ~FILE_H) >> 1; }
inline bitboard west(bitboard position) { return (position & ~FILE_A) << 1; }

inline Color negate_color(Color color) { return (Color)(color ^ 1); }

uint64_t get_position_from_row_col(uint8_t row, uint8_t col);
void print_bitboard(bitboard bb);
bitboard position_string_to_bitboard(std::string position_str);

// https://chessprogramming.wikispaces.com/Population+Count
inline unsigned popcount(bitboard bb) { return __builtin_popcount(bb); }

inline int lsb(bitboard bb) { return __builtin_ctzl(bb); }

inline bitboard pop_lsb(bitboard &bb) {
  bitboard square = ((uint64_t)1) << __builtin_ctzl(bb);
  bb &= bb - 1;
  return square;
}

#endif
