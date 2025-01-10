/*
 * Board class.
 * Stores information regarding the current game state.
 *
 * Magic bitboards: https://essays.jwatzman.org/essays/chess-move-generation-with-magic-bitboards.html
 */

#ifndef BOARD_HPP // GUARD
#define BOARD_HPP // GUARD

#include <stdint.h>
#include <array>
#include <map>
#include <stack>

#include "globals.hpp"
#include "Move.hpp"

typedef uint64_t bitboard;

class Board {
public:
  // Constructor:
  Board();

  // Clear:
  void clear();

  // Initializer:
  void initialize_board_starting_position();
  void initialize_perft_position_2();
  void initialize_perft_position_3();
  void initialize_fen(std::string fen);

  // Getters:
  inline bitboard get_piece_positions(Piece piece, Color color) { return piece_bitboards[color][piece]; }
  inline bitboard get_all_piece_positions(Color color) { return piece_bitboards[color][ALL]; }
  Piece get_piece_at_position(bitboard position, Color color);
  Move get_last_move(Color color);
  bool is_moves_empty(Color color);
  bool get_can_castle_queen(Color color);
  bool get_can_castle_king(Color color);
  Color get_turn_color();
  std::array<std::array<bitboard, 7>, 2>& get_piece_bitboards();
  int get_square_index(bitboard square);
  bitboard get_square(int square_index);
  bitboard get_blockers(bitboard position);

  // Setters:
  void set_piece_positions(Piece piece, Color color, bitboard new_positions);
  void set_turn_color(Color new_turn_color);

  // Board logic:
  bool is_checked(Color color);
  bool is_move_legal(Move &move, Color color);

  // Attacks:
  bool is_position_attacked_by(bitboard position, Color color);
  bitboard get_piece_attacks(Piece piece, bitboard position, Color color);
  bitboard get_pawn_single_push(bitboard position, Color color);
  bitboard get_pawn_double_push(bitboard position, Color color);

  // Moves:
  void execute_move(Move &move);
  void undo_move(Move &move);

  // Print:
  void print();

private:
  // NEW:
  
  
  Color turn_color; // color who has the current turn
  Move moves[2][256];
  size_t moves_size[2];
  Piece captured_pieces[2][16];
  size_t captured_pieces_size[2];
  std::array<std::array<bitboard, 7>, 2> piece_bitboards; // COLOR, PIECE
  std::array<bitboard, 7> all_piece_bitboards; // all pieces of a type (regardless of color)
  std::array<Piece, 64> board_pieces;

  // Castle rights:
  uint8_t castle_rights; // uses the lower 4 bits: white king side, white queen side, black king side, black queen side
  inline void set_king_castle_right(Color color) { castle_rights |= (0x8 >> (color << 1)); }
  inline void set_queen_castle_right(Color color) { castle_rights |= (0x4 >> (color << 1)); }
  inline void clear_king_castle_right(Color color) { castle_rights &= ~(0x8 >> (color << 1)); }
  inline void clear_queen_castle_right(Color color) { castle_rights &= ~(0x4 >> (color << 1)); }
  uint8_t previous_castle_rights[512];
  size_t castle_rights_size;

  // Moves -- Called by execute_move, undo_move
  void move_piece(Piece piece, Color color, bitboard origin, bitboard destination);
  void set_piece(Piece piece, Color color, bitboard position);
  void remove_piece(Piece piece, Color color, bitboard position);
  void execute_castle_move(bitboard origin, bitboard destination);
  void undo_castle_move(bitboard king_origin, bitboard king_destination);

  // Castling:
  void update_castle_rights(Move &move, Piece moving_piece); // Called by execute_move
  void revert_castle_rights(Color color); // Called by undo_move

  // Attacks:
  bitboard get_pawn_attacks(bitboard position, Color color);
  bitboard get_knight_attacks(bitboard position);
  bitboard get_bishop_attacks(bitboard position);
  bitboard get_rook_attacks(bitboard position);
  bitboard get_queen_attacks(bitboard position);
  bitboard get_king_attacks(bitboard position);
  bitboard get_attacks_to_king(bitboard king_position, Color king_color);

  // Sliding piece attack generation:
  bitboard generate_sliding_attacks(bitboard position, Direction direction, bitboard blockers);
  bitboard generate_bishop_attacks(bitboard position, bitboard blockers);
  bitboard generate_rook_attacks(bitboard position, bitboard blockers);

  // Helpers:
  Piece get_piece_from_index(int index);
  bitboard move_direction(bitboard position, Direction direction);
  Piece get_promotion_piece_from_flags(uint8_t flags);
  Piece get_piece_from_char(char piece_char);
  bitboard get_end_edge_mask(Direction direction);
  void verify_board_pieces_consistency();

  // Lookup Tables:
  std::map<int, bitboard> square_lookup;
  std::map<bitboard, int> square_index_lookup;
  std::array<std::array<bitboard, 64>, 2> pawn_single_pushes_lookups;
  std::array<std::array<bitboard, 64>, 2> pawn_double_pushes_lookups;
  std::array<std::array<bitboard, 64>, 2> pawn_attacks_lookups;
  std::array<bitboard, 64> knight_moves_lookup;
  std::array<bitboard, 64> king_moves_lookup;
  std::array<bitboard, 64> castle_rook_origin_lookup;
  std::array<bitboard, 64> castle_rook_destination_lookup;
  
  // Magic Bitboards:
  std::array<std::array<bitboard, 4096>, 64> rook_attacks_magic_bb;
  std::array<std::array<bitboard, 4096>, 64> bishop_attacks_magic_bb;

  // Initialize Lookup Tables:
  void initialize_lookups(); // Called by constructor
  void initialize_square_lookups();
  void initialize_single_pawn_pushes_lookups();
  void initialize_double_pawn_pushes_lookups();
  void initialize_pawn_attacks_lookups();
  void initialize_knight_moves_lookup();
  void initialize_king_moves_lookup();
  void initialize_castle_rook_origin_lookup();
  void initialize_castle_rook_destination_lookup();
  // Initialize Magic Bitboards
  void initialize_rook_attacks_magic_bb();
  void initialize_bishop_attacks_magic_bb();

  static const bitboard white_queenside_castle_king_position;
  static const bitboard white_queenside_castle_rook_position;
  static const bitboard white_kingside_castle_king_position;
  static const bitboard white_kingside_castle_rook_position;
  static const bitboard black_queenside_castle_king_position;
  static const bitboard black_queenside_castle_rook_position;
  static const bitboard black_kingside_castle_king_position;
  static const bitboard black_kingside_castle_rook_position;

  static const std::array<bitboard, 64> ROOK_MASKS;
  static const std::array<bitboard, 64> ROOK_MAGICS;
  static const std::array<bitboard, 64> ROOK_SHIFTS;
  static const std::array<bitboard, 64> BISHOP_MASKS;
  static const std::array<bitboard, 64> BISHOP_MAGICS;
  static const std::array<bitboard, 64> BISHOP_SHIFTS;
};

#endif // END GUARD
