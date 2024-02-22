#ifndef BOARD_CPP // GUARD
#define BOARD_CPP // GUARD

#include "Board.hpp"
#include "Move.hpp"

// Constructor:
Board::Board() {
  piece_bitboards = {};
  turn_color = WHITE;
}

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

Piece Board::get_piece_at_position(bitboard position, Color color) {
  std::array<Piece, 6> piece_array = {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};
  for(int i = 0; i < 6; i++) {
    if(piece_bitboards[color][i] & position) {
      return piece_array[i];
    }
  }
  return NONE;
}

//Move Board::get_last_move(Color color) {}

//bool Board::get_can_castle_queen(Color color) {}

//bool Board::get_can_castle_king(Color color) {}

// Setters:
void Board::set_piece_positions(Piece piece, Color color, bitboard new_positions) {
  piece_bitboards[color][piece] = new_positions;
}

void Board::set_can_castle_queen(Color color, bool new_can_castle_queen) {
  can_castle[color][1] = new_can_castle_queen;
}

void Board::set_can_castle_king(Color color, bool new_can_castle_king) {
  can_castle[color][0] = new_can_castle_king;
}

void Board::set_turn_color(Color new_turn_color) {
  turn_color = new_turn_color;
}

// Board Logic:
//bool Board::is_checked(Color color) {}

//bool Board::is_move_legal(Move &move, Color color) {}

// Attacks:
//bool Board::is_position_attacked_by(bitboard position, Color color) {}

// Moves:
/**
 * Move cases:
 * Quiet move: remove bit for origin, set bit for destination
 * Capture move: remove bit for origin, remove bit for captured piece at destination, set bit at destination
 * En passant: Remove bit for origin, remove bit for captured piece at its position, set bit at destination
 * Promotion: Remove bit for original piece at origin, set bit for promotion piece at destination
 */
void Board::execute_move(Move &move) {
  uint8_t move_flags = move.get_flags();
  assert(move_flags != 6 && move_flags != 7);
  bitboard origin = move.get_origin();
  bitboard destination = move.get_destination();

  Piece moving_piece = get_piece_at_position(origin, turn_color);
  
  if(move_flags == 0 || move_flags == 1) { // Quiet move
    move_piece(moving_piece, turn_color, origin, destination);
  } else if(move_flags == 2 || move_flags == 3) { // Castle move
    execute_castle_move(origin, destination);
  } else if(move_flags == 4) { // capture move
    Piece captured_piece = get_piece_at_position(destination, negate_color(turn_color));
    assert(captured_piece != NONE);
    move_piece(moving_piece, turn_color, origin, destination);
    remove_piece(captured_piece, negate_color(turn_color), destination);
  } else if(move_flags == 5) { // en passant move
    Piece captured_piece = get_piece_at_position(destination, negate_color(turn_color));
    bitboard capture_square = (turn_color == WHITE ? south(destination) : north(destination));
    move_piece(moving_piece, turn_color, origin, destination);
    remove_piece(captured_piece, negate_color(turn_color), capture_square);
  } else { // promotion  move
    Piece promotion_piece = get_promotion_piece_from_flags(move_flags);
    remove_piece(moving_piece, turn_color, origin);
    set_piece(promotion_piece, turn_color, destination);
    if(move_flags >= 12 && move_flags <= 15) {
      Piece captured_piece = get_piece_at_position(destination, negate_color(turn_color));
      remove_piece(captured_piece, negate_color(turn_color), destination);
    }
  }
}

//void Board::undo_move(Move &move, Color color) {}

// Castling:
//void Board::update_castle_rights(Move &move) {}

void Board::revert_castle_rights(Move &move) {
  can_castle = previous_can_castle;
}

// Moves:
void Board::move_piece(Piece piece, Color color, bitboard origin, bitboard destination) {
  piece_bitboards[color][piece] ^= (origin | destination);
}

void Board::set_piece(Piece piece, Color color, bitboard position) {
  assert((piece_bitboards[color][piece] & position) == 0);
  piece_bitboards[color][piece] |= position;
}

void Board::remove_piece(Piece piece, Color color, bitboard position) {
  assert(piece_bitboards[color][piece] & position);
  piece_bitboards[color][piece] &= ~position;
}

void Board::execute_castle_move(bitboard king_origin, bitboard king_destination) {
  bitboard rook_origin = castle_rook_origin_lookup[king_destination];
  bitboard rook_destination = castle_rook_destination_lookup[king_destination];

  move_piece(KING, turn_color, king_origin, king_destination);
  move_piece(ROOK, turn_color, rook_origin, rook_destination);
}

// Attacks:
bitboard Board::get_pawn_attacks(bitboard position, Color color) {
  return pawn_attacks_lookups[color][position];
}

bitboard Board::get_knight_attacks(bitboard position) {
  return knight_moves_lookup[position];
}

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

bitboard Board::get_king_attacks(bitboard position) {
  return king_moves_lookup[position];
}

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

Piece Board::get_promotion_piece_from_flags(uint8_t flags) {
  switch(flags) {
  case 8: return KNIGHT;
  case 9: return BISHOP;
  case 10: return ROOK;
  case 11: return QUEEN;
  case 12: return KNIGHT;
  case 13: return BISHOP;
  case 14: return ROOK;
  case 15: return QUEEN;
  }
  return NONE;
}

// Lookup Tables:
void Board::initialize_lookups() { // Called by constructor
  initialize_single_pawn_pushes_lookups();
  initialize_double_pawn_pushes_lookups();
  initialize_pawn_attacks_lookups();
  initialize_knight_moves_lookup();
  initialize_king_moves_lookup();
  initialize_castle_rook_origin_lookup();
  initialize_castle_rook_destination_lookup();
}

void Board::initialize_single_pawn_pushes_lookups() {
  for(bitboard position = 1; position > 0; position <<= 1) {
    pawn_single_pushes_lookups[WHITE][position] = north(position);
    pawn_single_pushes_lookups[BLACK][position] = south(position);
  }
}

void Board::initialize_double_pawn_pushes_lookups() {
  for(bitboard position = 0x100; position <= 0x8000; position <<= 1) {
    pawn_double_pushes_lookups[WHITE][position] = north(north(position));
  }
  for(bitboard position = 0x1000000000000; position <= 0x80000000000000; position <<= 1) {
    pawn_double_pushes_lookups[BLACK][position] = south(south(position));
  }
}

void Board::initialize_pawn_attacks_lookups() {
  for(bitboard position = 1; position > 0; position <<= 1) {
    pawn_attacks_lookups[WHITE][position] = east(north(position)) | west(north(position));
    pawn_attacks_lookups[BLACK][position] = east(south(position)) | west(south(position));
  }
}

void Board::initialize_knight_moves_lookup() {
  for(bitboard position = 1; position > 0; position <<= 1) {
    knight_moves_lookup[position] = east(north(north(position))) | west(north(north(position))) | east(south(south(position))) | west(south(south(position))) | north(east(east(position))) | north(west(west(position))) | south(east(east(position))) | south(west(west(position)));
  }
}

void Board::initialize_king_moves_lookup() {
  for(bitboard position = 1; position > 0; position <<= 1) {
    king_moves_lookup[position] = north(position) | east(position) | south(position) | west(position) | east(north(position)) | west(north(position)) | east(south(position)) | west(south(position));
  }
}

void Board::initialize_castle_rook_origin_lookup() {
  castle_rook_origin_lookup[0x200000000000000] = 0x100000000000000;
  castle_rook_origin_lookup[0x2000000000000000] = 0x8000000000000000;
  castle_rook_origin_lookup[0x2] = 0x1;
  castle_rook_origin_lookup[0x20] = 0x80;
}

void Board::initialize_castle_rook_destination_lookup() {
  castle_rook_origin_lookup[0x200000000000000] = 0x400000000000000;
  castle_rook_origin_lookup[0x2000000000000000] = 0x1000000000000000;
  castle_rook_origin_lookup[0x2] = 0x4;
  castle_rook_origin_lookup[020] = 0x1;

}

#endif
