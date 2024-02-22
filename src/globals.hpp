#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <stdint.h>
#include <iostream>
#include <string>

typedef uint64_t bitboard;

enum Piece {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE};
enum Color {WHITE, BLACK};
enum Direction {NORTH, EAST, SOUTH, WEST, NORTHEAST, NORTHWEST, SOUTHEAST, SOUTHWEST};

static const bitboard FILE_A = 0x8080808080808080;
static const bitboard FILE_H = 0x0808080808080808;
static const bitboard RANK_1 = 0xFF;
static const bitboard RANK_8 = 0xFF00000000000000;

inline bitboard north(bitboard position) { return (position & ~RANK_8) << 8; }
inline bitboard south(bitboard position) { return (position & ~RANK_1) >> 8; }
inline bitboard east(bitboard position) { return (position & ~FILE_H) >> 1; }
inline bitboard west(bitboard position) { return (position & ~FILE_A) << 1; }

inline Color negate_color(Color color) { return (color == WHITE ? BLACK : WHITE); }

uint64_t get_position_from_row_col(uint8_t row, uint8_t col);
void print_bitboard(bitboard bb);
bitboard position_string_to_bitboard(std::string position_str);

#endif
