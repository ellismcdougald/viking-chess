#ifndef BOARD_TESTS_CPP // GUARD
#define BOARD_TESTS_CPP

#include"iostream"
#include <catch2/catch_test_macros.hpp>

#include "../Board.hpp"

/*
TEST_CASE("Test board", "[board]") {
  Board board;
}

TEST_CASE("Test set_piece_positions", "[set_piece_positions]") {
  Board board;

  SECTION("test one") {
    board.set_piece_positions(PAWN, WHITE, 10);
    REQUIRE(board.piece_bitboards[WHITE][PAWN] == 10);
  }

  SECTION("test two") {
    board.set_piece_positions(KNIGHT, BLACK, 20);
    REQUIRE(board.piece_bitboards[BLACK][KNIGHT] == 20);
  }
}

TEST_CASE("Test get_piece_at_posiiton", "[get_piece_at_position]") {
  Board board;

  SECTION("pawn at h1") {
    board.set_piece_positions(PAWN, WHITE, 1);
    REQUIRE(board.get_piece_at_position(1, WHITE) == PAWN);
  }

  SECTION("pawn at d4") {
    board.set_piece_positions(PAWN, WHITE, get_position_from_row_col(4, 'd'));
    REQUIRE(board.get_piece_at_position(get_position_from_row_col(4, 'd'), WHITE) == PAWN);
  }
}

TEST_CASE("Test execute_move quiet", "[execute_move quiet]") {
  Board board;

  SECTION("white pawn quiet move d2 d4") {
    board.set_piece(PAWN, WHITE, position_string_to_bitboard("d2"));
    Move move('d', 2, 'd', 4, 0);
    board.execute_move(move);

    REQUIRE(board.piece_bitboards[WHITE][PAWN] == position_string_to_bitboard("d4"));
    REQUIRE(board.piece_bitboards[BLACK][PAWN] == 0);
    for(int piece_index = 1; piece_index < 6; piece_index++) {
      for(int color_index = 0; color_index < 2; color_index ++) {
	REQUIRE(board.piece_bitboards[color_index][piece_index] == 0);
      }
    }
  }

  SECTION("black queen quiet move a1h8") {
    board.set_piece(QUEEN, BLACK, position_string_to_bitboard("a1"));
    Move move('a', 1, 'h', 8, 0);
    board.set_turn_color(BLACK);

    board.execute_move(move);

    for(int piece_index = 0; piece_index < 4; piece_index++) {
      for(int color_index = 0; color_index < 2; color_index++) {
	REQUIRE(board.piece_bitboards[color_index][piece_index] == 0);
      }
    }
    REQUIRE(board.piece_bitboards[WHITE][QUEEN] == 0);
    REQUIRE(board.piece_bitboards[BLACK][QUEEN] == position_string_to_bitboard("h8"));
    REQUIRE(board.piece_bitboards[WHITE][KING] == 0);
    REQUIRE(board.piece_bitboards[BLACK][KING] == 0);
  }
}

TEST_CASE("Test execute_move capture", "[execute_move capture]") {
  Board board;

  SECTION("white pawn captures black pawn d4e5") {
    board.set_piece(PAWN, WHITE, position_string_to_bitboard("d4"));
    board.set_piece(PAWN, BLACK, position_string_to_bitboard("e5"));

    Move move('d', 4, 'e', 5, 4);

    board.execute_move(move);

    REQUIRE(board.piece_bitboards[WHITE][PAWN] == position_string_to_bitboard("e5"));
    REQUIRE(board.piece_bitboards[BLACK][PAWN] == 0);
    for(int piece_index = 1; piece_index < 6; piece_index++) {
      for(int color_index = 0; color_index < 2; color_index++) {
	REQUIRE(board.piece_bitboards[color_index][piece_index] == 0);
      }
    }
  }
}
*/

TEST_CASE("Test execute_move castle", "[execute_move castle]") {
  Board board;
  board.set_turn_color(BLACK);
  board.set_piece(KING, BLACK, position_string_to_bitboard("e8"));
  board.set_piece(ROOK, BLACK, position_string_to_bitboard("a8"));
  board.set_piece(ROOK, BLACK, position_string_to_bitboard("h8"));

  SECTION("black castle king side") {
    Move move('e', 8, 'g', 8, 2);

    board.execute_move(move);

    REQUIRE(board.piece_bitboards[BLACK][KING] == position_string_to_bitboard("g8"));
    REQUIRE(board.piece_bitboards[BLACK][ROOK] == (position_string_to_bitboard("f8") | position_string_to_bitboard("a8")));
  }

  SECTION("black castle queen side") {
    Move move('e', 8, 'c', 8, 3);

    board.execute_move(move);

    REQUIRE(board.piece_bitboards[BLACK][KING] == position_string_to_bitboard("c8"));
    REQUIRE(board.piece_bitboards[BLACK][ROOK] == (position_string_to_bitboard("d8") | position_string_to_bitboard("h8")));
  }

}

#endif
