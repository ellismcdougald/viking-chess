#ifndef BOARD_CPP // GUARD
#define BOARD_CPP // GUARD

#include "Board.hpp"

// Constructor:
Board::Board() {}

// Initializer:
void Board::initialize_board_starting_position() {};

// Getters:
bitboard Board::get_piece_positions(Piece piece, Color color) {
  return piece_bitboards[color][piece];
}

bitboard Board::get_all_piece_positions(Color color) {
  bitboard result = 0;
  for(int piece_index = 0; piece_index < 6; piece_index++) {
    assert((result & piece_bitboards[color][piece_index]) == 0);
    result |= piece_bitboards[color][piece_index];
  }
  return result;
}

//Piece Board::get_piece_at_position(bitboard position, Color color) {}

//Move Board::get_last_move(Color color) {}

//bool Board::get_can_castle_queen(Color color) {}

//bool Board::get_can_castle_king(Color color) {}

// Attacks:
//bitboard Board::get_pawn_attacks(bitboard position, Color color) {}

//bitboard Board::get_knight_attacks(bitboard position) {}

bitboard Board::get_bishop_attacks(bitboard position) {
  return
    get_sliding_attacks(position, NORTHEAST) |
    get_sliding_attacks(position, NORTHWEST) |
    get_sliding_attacks(position, SOUTHEAST) |
    get_sliding_attacks(position, SOUTHWEST);
}

bitboard Board::get_rook_attacks(bitboard position) {
  return
    get_sliding_attacks(position, NORTH) |
    get_sliding_attacks(position, EAST) |
    get_sliding_attacks(position, SOUTH) |
    get_sliding_attacks(position, WEST);
}

bitboard Board::get_queen_attacks(bitboard position) {
  return get_bishop_attacks(position) | get_rook_attacks(position);
}

//bitboard Board::get_king_attacks(bitboard position) {}

bitboard Board::get_sliding_attacks(bitboard position, Direction direction) {
  assert((get_all_piece_positions(WHITE) & get_all_piece_positions(BLACK)) == 0);
  
  bitboard other_pieces = get_all_piece_positions(WHITE) | get_all_piece_positions(BLACK);
  bitboard result = 0;
  while((position & other_pieces) == 0) {
    position = move_direction(position, direction);
    result |= position;
  }

  return result;
}

// Helpers:
bitboard Board::move_direction(bitboard position, Direction direction) {
  switch(direction) {
  case NORTH: return north(position);
  case EAST: return east(position);
  case SOUTH: return south(position);
  case WEST: return west(position);
  case NORTHEAST: return north(east(position));
  case NORTHWEST: return north(west(position));
  case SOUTHEAST: return south(east(position));
  case SOUTHWEST: return south(west(position));
  }
}

#endif
