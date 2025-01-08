#ifndef BOARD_CPP // GUARD
#define BOARD_CPP // GUARD

#include <sstream>
#include <string>
#include <bit>
#include <bitset>
#include "Board.hpp"
#include "Move.hpp"
#include "globals.hpp"

// Constructor:
Board::Board() {
  piece_bitboards[0].fill(0);
  piece_bitboards[1].fill(0);
  turn_color = WHITE;
  initialize_lookups();
  can_castle[WHITE].fill(true);
  can_castle[BLACK].fill(true);
}

void Board::clear() {
  piece_bitboards[0].fill(0);
  piece_bitboards[1].fill(0);
  turn_color = WHITE;
  can_castle[WHITE].fill(true);
  can_castle[BLACK].fill(true);
}

// Initializer:
void Board::initialize_board_starting_position() {
  piece_bitboards[WHITE][PAWN] = starting_white_pawn_position;
  piece_bitboards[WHITE][KNIGHT] = starting_white_knight_position;
  piece_bitboards[WHITE][BISHOP] = starting_white_bishop_position;
  piece_bitboards[WHITE][ROOK] = starting_white_rook_position;
  piece_bitboards[WHITE][QUEEN] = starting_white_queen_position;
  piece_bitboards[WHITE][KING] = starting_white_king_position;

  piece_bitboards[BLACK][PAWN] = starting_black_pawn_position;
  piece_bitboards[BLACK][KNIGHT] = starting_black_knight_position;
  piece_bitboards[BLACK][BISHOP] = starting_black_bishop_position;
  piece_bitboards[BLACK][ROOK] = starting_black_rook_position;
  piece_bitboards[BLACK][QUEEN] = starting_black_queen_position;
  piece_bitboards[BLACK][KING] = starting_black_king_position;
};

void Board::initialize_perft_position_2() {
  piece_bitboards[WHITE][PAWN] = 0x100800E700;
  piece_bitboards[WHITE][KNIGHT] = 0x800200000;
  piece_bitboards[WHITE][BISHOP] = 0x1800;
  piece_bitboards[WHITE][ROOK] = 0x81;
  piece_bitboards[WHITE][QUEEN] = 0x40000;
  piece_bitboards[WHITE][KING] = 0x8;

  piece_bitboards[BLACK][PAWN] = 0xB40A0040010000;
  piece_bitboards[BLACK][KNIGHT] = 0x440000000000;
  piece_bitboards[BLACK][BISHOP] = 0x2800000000000;
  piece_bitboards[BLACK][ROOK] = 0x8100000000000000;
  piece_bitboards[BLACK][QUEEN] = 0x8000000000000;
  piece_bitboards[BLACK][KING] = 0x800000000000000;
}

void Board::initialize_perft_position_3() {
  piece_bitboards[WHITE][PAWN] = 0x4000000A00;
  piece_bitboards[WHITE][ROOK] = 0x40000000;
  piece_bitboards[WHITE][KING] = 0x8000000000;

  piece_bitboards[BLACK][PAWN] = 0x20100004000000;
  piece_bitboards[BLACK][ROOK] = 0x100000000;
  piece_bitboards[BLACK][KING] = 0x1000000;
}

/**
 ** This only supports position and turn color. The remaining information in the fen string is discarded. The engine does not use this function-- it is for testing only.
 **/
void Board::initialize_fen(std::string fen) {
  bitboard current_position = 0x8000000000000000;
  std::istringstream fen_ss(fen);

  std::string pieces_str, color_str, castle_string, ep_string, half_clock_str, full_clock_str;
    
  fen_ss >> pieces_str;
  Piece piece_to_place;
  Color piece_color;
  int numSpaces;
  for(int i = 0; i < pieces_str.length(); i++) {
    if(pieces_str[i] == '/') continue;
    else if(isdigit(pieces_str[i])) {
      for(int j = 0; j < pieces_str[i] - '0'; j++) current_position >>= 1;
    } else {
      piece_color = isupper(pieces_str[i]) ? WHITE : BLACK;
      piece_to_place = get_piece_from_char(pieces_str[i]);
      set_piece(piece_to_place, piece_color, current_position);
      current_position >>= 1;
    }
  }

  fen_ss >> color_str;
  if(!(color_str == "w" | color_str == "b")) {
    std::cout << "Invalid fen." << std::endl;
    return;
  }
  set_turn_color(color_str == "w" ? WHITE : BLACK);
}

Piece Board::get_piece_from_char(char piece_char) {
  switch(tolower(piece_char)) {
  case 'p': return PAWN;
  case 'n': return KNIGHT;
  case 'b': return BISHOP;
  case 'r': return ROOK;
  case 'q': return QUEEN;
  case 'k': return KING;
  default: return NONE;
  }
}

bitboard Board::get_end_edge_mask(Direction direction) {
  switch (direction) {
  case NORTH: return RANK_8;
  case SOUTH: return RANK_1;
  case EAST: return FILE_H;
  case WEST: return FILE_A;
  default: return 0;
  }
}

// Getters:
bitboard Board::get_piece_positions(Piece piece, Color color) {
  return piece_bitboards[color][piece];
}

bitboard Board::get_all_piece_positions(Color color) {
  bitboard result = 0;
  for(int piece_index = 0; piece_index < 6; piece_index++) {
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

Move Board::get_last_move(Color color) {
  assert(moves[color].size() > 0);
  return moves[color][moves[color].size() - 1];
}

bool Board::is_moves_empty(Color color) {
  return moves[color].size() == 0;
}

bool Board::get_can_castle_queen(Color color) {
  return can_castle[color][1];
}

bool Board::get_can_castle_king(Color color) {
  return can_castle[color][0];
}

Color Board::get_turn_color() {
  return turn_color;
}

std::array<std::array<bitboard, 6>, 2>& Board::get_piece_bitboards() {
  return piece_bitboards;
}

std::array<std::array<bool, 2>, 2>& Board::get_can_castle() {
  return can_castle;
}

int Board::get_square_index(bitboard square) {
  return square_index_lookup[square];
}

bitboard Board::get_square(int square_index) {
  return square_lookup[square_index];
}

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
bool Board::is_checked(Color color) {
  bitboard king_position = get_piece_positions(KING, color);
  return is_position_attacked_by(king_position, negate_color(color));
}

bool Board::is_move_legal(Move &move, Color color) {
  execute_move(move);
  bool is_legal = !is_checked(color);
  undo_move(move);
  return is_legal;
}

// Attacks:
bool Board::is_position_attacked_by(bitboard position, Color color) {
  std::array<Piece, 6> piece_array = {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};
  for(int piece_index = 0; piece_index < 6; piece_index++) {
    if(get_piece_attacks(piece_array[piece_index], position, negate_color(color)) & get_piece_positions(piece_array[piece_index], color)) {
      return true;
    }
  }
  return false;
}

bitboard Board::get_piece_attacks(Piece piece, bitboard position, Color color) {
  assert(piece != NONE);
  switch(piece) {
  case PAWN: return get_pawn_attacks(position, color);
  case KNIGHT: return get_knight_attacks(position);
  case BISHOP: return get_bishop_attacks(position);
  case ROOK: return get_rook_attacks(position);
  case QUEEN: return get_queen_attacks(position);
  case KING: return get_king_attacks(position);
  case NONE: return 0;
  }
  return 0;
}

bitboard Board::get_pawn_single_push(bitboard position, Color color) {
  return pawn_single_pushes_lookups[color][position];
}

bitboard Board::get_pawn_double_push(bitboard position, Color color) {
  return pawn_double_pushes_lookups[color][position];
}

bitboard Board::get_blockers(bitboard position) {
  return (get_all_piece_positions(WHITE) | get_all_piece_positions(BLACK)) & ~position;
}

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
  update_castle_rights(move, moving_piece);
  
  if(move_flags == 0 || move_flags == 1) { // Quiet move
    move_piece(moving_piece, turn_color, origin, destination);
  } else if(move_flags == 2 || move_flags == 3) { // Castle move
    execute_castle_move(origin, destination);
  } else if(move_flags == 4) { // capture move
    Piece captured_piece = get_piece_at_position(destination, negate_color(turn_color));
    assert(captured_piece != NONE);
    move_piece(moving_piece, turn_color, origin, destination);
    remove_piece(captured_piece, negate_color(turn_color), destination);
    captured_pieces[turn_color].push_back(captured_piece);
  } else if(move_flags == 5) { // en passant move
    bitboard capture_square = (turn_color == WHITE ? south(destination) : north(destination));
    Piece captured_piece = get_piece_at_position(capture_square, negate_color(turn_color));
    captured_pieces[turn_color].push_back(captured_piece);
    move_piece(moving_piece, turn_color, origin, destination);
    remove_piece(captured_piece, negate_color(turn_color), capture_square);
  } else { // promotion  move
    Piece promotion_piece = get_promotion_piece_from_flags(move_flags);
    remove_piece(moving_piece, turn_color, origin);
    set_piece(promotion_piece, turn_color, destination);
    if(move_flags >= 12 && move_flags <= 15) {
      Piece captured_piece = get_piece_at_position(destination, negate_color(turn_color));
      remove_piece(captured_piece, negate_color(turn_color), destination);
      captured_pieces[turn_color].push_back(captured_piece);
    }
  }

  moves[turn_color].push_back(move);

  set_turn_color(negate_color(turn_color));
}


void Board::execute_move(std::string move_str) {
  int move_flag;
  
  std::string start_str = move_str.substr(0, 2);
  std::string end_str = move_str.substr(2, 3);
  //bitboard start_position = position_string_to_bitboard(start_str);
  bitboard end_position = position_string_to_bitboard(end_str);

  Piece end_piece = get_piece_at_position(end_position, negate_color(turn_color));
  if(end_piece == 6) { // move is not capture
    if(turn_color == WHITE && start_str[1] == '2' && end_str[1] == '4') {
      move_flag = 1;
    } else if(turn_color == BLACK && start_str[1] == '7' && end_str[1] == '5') {
      move_flag = 1;
    }
    move_flag = 0;
  } else { // move is capture
    std::cout << "test\n";

  }
}


// Opposite of execute_move
void Board::undo_move(Move &move) {
  set_turn_color(negate_color(turn_color));
  
  uint8_t move_flags = move.get_flags();
  assert(move_flags != 6 && move_flags != 7);
  bitboard origin = move.get_origin();
  bitboard destination = move.get_destination();

  Piece moved_piece = get_piece_at_position(destination, turn_color);
  revert_castle_rights(turn_color);

  if(move_flags == 0 || move_flags == 1) { // Quiet move
    move_piece(moved_piece, turn_color, destination, origin);
  } else if(move_flags == 2 || move_flags == 3) { // Castle move
    execute_castle_move(origin, destination);
  } else if(move_flags == 4) { // capture move
    assert(captured_pieces[turn_color].size() > 0);
    Piece captured_piece = captured_pieces[turn_color].back();
    captured_pieces[turn_color].pop_back();
    move_piece(moved_piece, turn_color, destination, origin);
    set_piece(captured_piece, negate_color(turn_color), destination);
  } else if(move_flags == 5) { // en passant move
    bitboard capture_square = (turn_color == WHITE ? south(destination) : north(destination));
    assert(captured_pieces[turn_color].size() > 0);
    Piece captured_piece = captured_pieces[turn_color].back();
    captured_pieces[turn_color].pop_back();
    move_piece(moved_piece, turn_color, destination, origin);
    set_piece(captured_piece, negate_color(turn_color), capture_square);
  } else { // promotion move
    moved_piece = PAWN;
    Piece promotion_piece = get_promotion_piece_from_flags(move_flags);
    set_piece(moved_piece, turn_color, origin);
    remove_piece(promotion_piece, turn_color, destination);
    if(move_flags >= 12 && move_flags <= 15) {
      assert(captured_pieces[turn_color].size() > 0);
      Piece captured_piece = captured_pieces[turn_color].back();
      captured_pieces[turn_color].pop_back();
      set_piece(captured_piece, negate_color(turn_color), destination);
    }
  }

  moves[turn_color].pop_back();
}

// Print:
void Board::print() {
  std::string separator_line(17, '-');
  std::array<char, 7> piece_chars = {'p', 'n', 'b', 'r', 'q', 'k', ' '};
  bitboard mask = 0x8000000000000000;
  Piece current_piece;
  std::cout << " " << separator_line << std::endl;
  for(int row = 0; row < 8; row++) {
    std::cout << (8 - row) << "|";
    for(int col = 0; col < 8; col++) {
      current_piece = get_piece_at_position(mask, WHITE);
      if(current_piece < 6) {
	std::cout << (char) toupper(piece_chars[current_piece]);
      } else {
	current_piece = get_piece_at_position(mask, BLACK);
	std::cout << piece_chars[current_piece];
      }
      std::cout << "|";
      mask >>= 1;
    }
    std::cout << std::endl << " " << separator_line << std::endl;
  }
  std::cout << "  A B C D E F G H" << std::endl;
}

// Castling:
void Board::update_castle_rights(Move &move, Piece moving_piece) {
  bitboard origin = move.get_origin();
  //previous_can_castle[turn_color] = can_castle[turn_color];
  previous_can_castle_stacks[turn_color].push_back(can_castle[turn_color]);
  
  if(moving_piece == KING) {
    set_can_castle_king(turn_color, false);
    set_can_castle_queen(turn_color, false);
  } else if(moving_piece == ROOK) {
    if((turn_color == WHITE && origin == 0x80) || (turn_color == BLACK && origin == 0x8000000000000000)) {
      set_can_castle_queen(turn_color, false);
    } else if((turn_color == WHITE && origin == 1) || (turn_color == BLACK && origin == 0x100000000000000)) {
      set_can_castle_king(turn_color, false);
    }
  }
}

void Board::revert_castle_rights(Color color) {
  //can_castle[color] = previous_can_castle[color];
  can_castle[color] = previous_can_castle_stacks[turn_color].back();
  previous_can_castle_stacks[turn_color].pop_back();
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
  int square_index = square_index_lookup[position];
  bitboard blockers = (get_all_piece_positions(WHITE) | get_all_piece_positions(BLACK)) & BISHOP_MASKS[square_index];
  uint64_t key = (blockers * BISHOP_MAGICS[square_index]) >> BISHOP_SHIFTS[square_index];
  bitboard result = bishop_attacks_magic_bb[square_index][key];
  return result;
}

bitboard Board::get_rook_attacks(bitboard position) {
  int square_index = square_index_lookup[position];
  bitboard blockers = (get_all_piece_positions(WHITE) | get_all_piece_positions(BLACK)) & ROOK_MASKS[square_index];
  uint64_t key = (blockers * ROOK_MAGICS[square_index]) >> ROOK_SHIFTS[square_index];
  bitboard result = rook_attacks_magic_bb[square_index][key];
  return result;
}

bitboard Board::get_queen_attacks(bitboard position) {
  return get_rook_attacks(position) | get_bishop_attacks(position);
}

bitboard Board::get_king_attacks(bitboard position) {
  return king_moves_lookup[position];
}

// Sliding piece attack generation
bitboard Board::generate_sliding_attacks(bitboard position, Direction direction, bitboard blockers) {
  assert((get_all_piece_positions(WHITE) & get_all_piece_positions(BLACK)) == 0);
  
  bitboard result = 0;
  while((position & blockers) == 0) {
    position = move_direction(position, direction);
    if(!position) break;
    result |= position;
  }

  return result;
}

bitboard Board::generate_bishop_attacks(bitboard position, bitboard blockers) {
  return
    generate_sliding_attacks(position, NORTHEAST, blockers) |
    generate_sliding_attacks(position, NORTHWEST, blockers) |
    generate_sliding_attacks(position, SOUTHEAST, blockers) |
    generate_sliding_attacks(position, SOUTHWEST, blockers);
}

bitboard Board::generate_rook_attacks(bitboard position, bitboard blockers) {
  return
    generate_sliding_attacks(position, NORTH, blockers) |
    generate_sliding_attacks(position, EAST, blockers) |
    generate_sliding_attacks(position, SOUTH, blockers) |
    generate_sliding_attacks(position, WEST, blockers);
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
  initialize_square_lookups();
  initialize_single_pawn_pushes_lookups();
  initialize_double_pawn_pushes_lookups();
  initialize_pawn_attacks_lookups();
  initialize_knight_moves_lookup();
  initialize_king_moves_lookup();
  initialize_castle_rook_origin_lookup();
  initialize_castle_rook_destination_lookup();

  initialize_rook_attacks_magic_bb();
  initialize_bishop_attacks_magic_bb();
}

void Board::initialize_square_lookups() {
  bitboard square = 0x8000000000000000;
  for (int square_index = 63; square_index >= 0; --square_index) {
    square_lookup[square_index] = square;
    square_index_lookup[square] = square_index;
    square >>= 1;
  }
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
  castle_rook_destination_lookup[0x200000000000000] = 0x400000000000000;
  castle_rook_destination_lookup[0x2000000000000000] = 0x1000000000000000;
  castle_rook_destination_lookup[0x2] = 0x4;
  castle_rook_destination_lookup[0x20] = 0x10;
}

void Board::initialize_rook_attacks_magic_bb() {
  for (int square_index = 0; square_index < 64; square_index++) {
    bitboard square = square_lookup[square_index];

    bitboard blockers = 0;
    do {
      bitboard attack_set = generate_rook_attacks(square, blockers);
      
      uint64_t key = ((blockers & ROOK_MASKS[square_index]) * ROOK_MAGICS[square_index]) >> ROOK_SHIFTS[square_index];
      rook_attacks_magic_bb[square_index][key] = attack_set;

      blockers = (blockers - ROOK_MASKS[square_index]) & ROOK_MASKS[square_index]; // get next subset of blockers
    } while (blockers);
  }
}

void Board::initialize_bishop_attacks_magic_bb() {
  for (int square_index = 0; square_index < 64; square_index++) {
    bitboard square = square_lookup[square_index];

    bitboard blockers = 0;
    do {
      bitboard attack_set = generate_bishop_attacks(square, blockers);
      
      uint64_t key = ((blockers & BISHOP_MASKS[square_index]) * BISHOP_MAGICS[square_index]) >> BISHOP_SHIFTS[square_index];
      bishop_attacks_magic_bb[square_index][key] = attack_set;

      blockers = (blockers - BISHOP_MASKS[square_index]) & BISHOP_MASKS[square_index]; // get next subset of blockers
    } while (blockers);
  }
}

// Constants:
const std::array<bitboard, 64> Board::ROOK_MAGICS = {
  0x0080001020400080, 0x0040001000200040, 0x0080081000200080, 0x0080040800100080,
  0x0080020400080080, 0x0080010200040080, 0x0080008001000200, 0x0080002040800100,
  0x0000800020400080, 0x0000400020005000, 0x0000801000200080, 0x0000800800100080,
  0x0000800400080080, 0x0000800200040080, 0x0000800100020080, 0x0000800040800100,
  0x0000208000400080, 0x0000404000201000, 0x0000808010002000, 0x0000808008001000,
  0x0000808004000800, 0x0000808002000400, 0x0000010100020004, 0x0000020000408104,
  0x0000208080004000, 0x0000200040005000, 0x0000100080200080, 0x0000080080100080,
  0x0000040080080080, 0x0000020080040080, 0x0000010080800200, 0x0000800080004100,
  0x0000204000800080, 0x0000200040401000, 0x0000100080802000, 0x0000080080801000,
  0x0000040080800800, 0x0000020080800400, 0x0000020001010004, 0x0000800040800100,
  0x0000204000808000, 0x0000200040008080, 0x0000100020008080, 0x0000080010008080,
  0x0000040008008080, 0x0000020004008080, 0x0000010002008080, 0x0000004081020004,
  0x0000204000800080, 0x0000200040008080, 0x0000100020008080, 0x0000080010008080,
  0x0000040008008080, 0x0000020004008080, 0x0000800100020080, 0x0000800041000080,
  0x00FFFCDDFCED714A, 0x007FFCDDFCED714A, 0x003FFFCDFFD88096, 0x0000040810002101,
  0x0001000204080011, 0x0001000204000801, 0x0001000082000401, 0x0001FFFAABFAD1A2
};
const std::array<bitboard, 64> Board::ROOK_MASKS = {	
  0x000101010101017E, 0x000202020202027C, 0x000404040404047A, 0x0008080808080876,
  0x001010101010106E, 0x002020202020205E, 0x004040404040403E, 0x008080808080807E,
  0x0001010101017E00, 0x0002020202027C00, 0x0004040404047A00, 0x0008080808087600,
  0x0010101010106E00, 0x0020202020205E00, 0x0040404040403E00, 0x0080808080807E00,
  0x00010101017E0100, 0x00020202027C0200, 0x00040404047A0400, 0x0008080808760800,
  0x00101010106E1000, 0x00202020205E2000, 0x00404040403E4000, 0x00808080807E8000,
  0x000101017E010100, 0x000202027C020200, 0x000404047A040400, 0x0008080876080800,
  0x001010106E101000, 0x002020205E202000, 0x004040403E404000, 0x008080807E808000,
  0x0001017E01010100, 0x0002027C02020200, 0x0004047A04040400, 0x0008087608080800,
  0x0010106E10101000, 0x0020205E20202000, 0x0040403E40404000, 0x0080807E80808000,
  0x00017E0101010100, 0x00027C0202020200, 0x00047A0404040400, 0x0008760808080800,
  0x00106E1010101000, 0x00205E2020202000, 0x00403E4040404000, 0x00807E8080808000,
  0x007E010101010100, 0x007C020202020200, 0x007A040404040400, 0x0076080808080800,
  0x006E101010101000, 0x005E202020202000, 0x003E404040404000, 0x007E808080808000,
  0x7E01010101010100, 0x7C02020202020200, 0x7A04040404040400, 0x7608080808080800,
  0x6E10101010101000, 0x5E20202020202000, 0x3E40404040404000, 0x7E80808080808000
};
const std::array<bitboard, 64> Board::ROOK_SHIFTS = {
  52, 53, 53, 53, 53, 53, 53, 52,
  53, 54, 54, 54, 54, 54, 54, 53,
  53, 54, 54, 54, 54, 54, 54, 53,
  53, 54, 54, 54, 54, 54, 54, 53,
  53, 54, 54, 54, 54, 54, 54, 53,
  53, 54, 54, 54, 54, 54, 54, 53,
  53, 54, 54, 54, 54, 54, 54, 53,
  53, 54, 54, 53, 53, 53, 53, 53
};
const std::array<bitboard, 64> Board::BISHOP_MASKS = {
  0x0040201008040200, 0x0000402010080400, 0x0000004020100A00, 0x0000000040221400,
  0x0000000002442800, 0x0000000204085000, 0x0000020408102000, 0x0002040810204000,
  0x0020100804020000, 0x0040201008040000, 0x00004020100A0000, 0x0000004022140000,
  0x0000000244280000, 0x0000020408500000, 0x0002040810200000, 0x0004081020400000,
  0x0010080402000200, 0x0020100804000400, 0x004020100A000A00, 0x0000402214001400,
  0x0000024428002800, 0x0002040850005000, 0x0004081020002000, 0x0008102040004000,
  0x0008040200020400, 0x0010080400040800, 0x0020100A000A1000, 0x0040221400142200,
  0x0002442800284400, 0x0004085000500800, 0x0008102000201000, 0x0010204000402000,
  0x0004020002040800, 0x0008040004081000, 0x00100A000A102000, 0x0022140014224000,
  0x0044280028440200, 0x0008500050080400, 0x0010200020100800, 0x0020400040201000,
  0x0002000204081000, 0x0004000408102000, 0x000A000A10204000, 0x0014001422400000,
  0x0028002844020000, 0x0050005008040200, 0x0020002010080400, 0x0040004020100800,
  0x0000020408102000, 0x0000040810204000, 0x00000A1020400000, 0x0000142240000000,
  0x0000284402000000, 0x0000500804020000, 0x0000201008040200, 0x0000402010080400,
  0x0002040810204000, 0x0004081020400000, 0x000A102040000000, 0x0014224000000000,
  0x0028440200000000, 0x0050080402000000, 0x0020100804020000, 0x0040201008040200
};
const std::array<bitboard, 64> Board::BISHOP_MAGICS = {
  0x0002020202020200, 0x0002020202020000, 0x0004010202000000, 0x0004040080000000,
  0x0001104000000000, 0x0000821040000000, 0x0000410410400000, 0x0000104104104000,
  0x0000040404040400, 0x0000020202020200, 0x0000040102020000, 0x0000040400800000,
  0x0000011040000000, 0x0000008210400000, 0x0000004104104000, 0x0000002082082000,
  0x0004000808080800, 0x0002000404040400, 0x0001000202020200, 0x0000800802004000,
  0x0000800400A00000, 0x0000200100884000, 0x0000400082082000, 0x0000200041041000,
  0x0002080010101000, 0x0001040008080800, 0x0000208004010400, 0x0000404004010200,
  0x0000840000802000, 0x0000404002011000, 0x0000808001041000, 0x0000404000820800,
  0x0001041000202000, 0x0000820800101000, 0x0000104400080800, 0x0000020080080080,
  0x0000404040040100, 0x0000808100020100, 0x0001010100020800, 0x0000808080010400,
  0x0000820820004000, 0x0000410410002000, 0x0000082088001000, 0x0000002011000800,
  0x0000080100400400, 0x0001010101000200, 0x0002020202000400, 0x0001010101000200,
  0x0000410410400000, 0x0000208208200000, 0x0000002084100000, 0x0000000020880000,
  0x0000001002020000, 0x0000040408020000, 0x0004040404040000, 0x0002020202020000,
  0x0000104104104000, 0x0000002082082000, 0x0000000020841000, 0x0000000000208800,
  0x0000000010020200, 0x0000000404080200, 0x0000040404040400, 0x0002020202020200
};
const std::array<bitboard, 64> Board::BISHOP_SHIFTS = {
  58, 59, 59, 59, 59, 59, 59, 58,
  59, 59, 59, 59, 59, 59, 59, 59,
  59, 59, 57, 57, 57, 57, 59, 59,
  59, 59, 57, 55, 55, 57, 59, 59,
  59, 59, 57, 55, 55, 57, 59, 59,
  59, 59, 57, 57, 57, 57, 59, 59,
  59, 59, 59, 59, 59, 59, 59, 59,
  58, 59, 59, 59, 59, 59, 59, 58
};

#endif
