#ifndef BOARD_TESTS_CPP // GUARD
#define BOARD_TESTS_CPP

#include"iostream"
#include <catch2/catch_test_macros.hpp>

#include "../Board.hpp"

TEST_CASE("Test board", "[board]") {
  Board board;
  board.initialize_board_starting_position();
}

TEST_CASE("test inititalize_fen") {
  Board board;

  SECTION("starting position") {
    board.initialize_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  }
}

TEST_CASE("Test set_piece_positions", "[set_piece_positions]") {
  Board board;

  SECTION("test one") {
    board.set_piece_positions(PAWN, WHITE, 10);
    REQUIRE(board.piece_bitboards[WHITE][PAWN] == 10);
    REQUIRE(board.all_piece_bitboards[PAWN] == 10);
    REQUIRE(board.piece_bitboards[WHITE][ALL] == 10);
  }

  SECTION("test two") {
    board.set_piece_positions(KNIGHT, BLACK, 20);
    REQUIRE(board.piece_bitboards[BLACK][KNIGHT] == 20);
    REQUIRE(board.piece_bitboards[BLACK][ALL] == 20);
    REQUIRE(board.all_piece_bitboards[KNIGHT] == 20);
  }
}

TEST_CASE("Test get_piece_at_position", "[get_piece_at_position]") {
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

TEST_CASE("Test execute_move and undo_move quiet", "[execute_move undo_move quiet]") {
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

    board.undo_move(move);
    REQUIRE(board.piece_bitboards[WHITE][PAWN] == position_string_to_bitboard("d2"));
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

    board.undo_move(move);

    for(int piece_index = 0; piece_index < 4; piece_index++) {
      for(int color_index = 0; color_index < 2; color_index++) {
	REQUIRE(board.piece_bitboards[color_index][piece_index] == 0);
      }
    }
    REQUIRE(board.piece_bitboards[WHITE][QUEEN] == 0);
    REQUIRE(board.piece_bitboards[BLACK][QUEEN] == position_string_to_bitboard("a1"));
    REQUIRE(board.piece_bitboards[WHITE][KING] == 0);
    REQUIRE(board.piece_bitboards[BLACK][KING] == 0);
  }
}

TEST_CASE("Test execute_move and undo_move capture", "[execute_move undo_move capture]") {
  Board board;

  SECTION("white pawn captures black pawn d4e5") {
    board.set_piece(PAWN, WHITE, position_string_to_bitboard("d4"));
    board.set_piece(PAWN, BLACK, position_string_to_bitboard("e5"));

    Move move('d', 4, 'e', 5, 4);

    board.execute_move(move);

    REQUIRE(board.piece_bitboards[WHITE][PAWN] == position_string_to_bitboard("e5"));
    REQUIRE(board.piece_bitboards[WHITE][ALL] == position_string_to_bitboard("e5"));
    REQUIRE(board.piece_bitboards[BLACK][PAWN] == 0);
    REQUIRE(board.piece_bitboards[BLACK][ALL] == 0);
    for(int piece_index = 1; piece_index < 6; piece_index++) {
      for(int color_index = 0; color_index < 2; color_index++) {
	REQUIRE(board.piece_bitboards[color_index][piece_index] == 0);
      }
    }
    REQUIRE(board.all_piece_bitboards[PAWN] == position_string_to_bitboard("e5"));

    board.undo_move(move);
    
    REQUIRE(board.piece_bitboards[WHITE][PAWN] == position_string_to_bitboard("d4"));
    REQUIRE(board.piece_bitboards[BLACK][PAWN] == position_string_to_bitboard("e5"));
    REQUIRE(board.piece_bitboards[WHITE][ALL] == position_string_to_bitboard("d4"));
    REQUIRE(board.piece_bitboards[BLACK][ALL] == position_string_to_bitboard("e5"));
    REQUIRE(board.all_piece_bitboards[PAWN] == (position_string_to_bitboard("d4") | position_string_to_bitboard("e5")));
  }
}

TEST_CASE("Test execute_move and undo_move castle", "[execute_move undo_move castle]") {
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

    board.undo_move(move);

    REQUIRE(board.piece_bitboards[BLACK][KING] == position_string_to_bitboard("e8"));
    REQUIRE(board.piece_bitboards[BLACK][ROOK] == (position_string_to_bitboard("h8") | position_string_to_bitboard("a8")));
  }

  SECTION("black castle queen side") {
    Move move('e', 8, 'c', 8, 3);

    board.execute_move(move);

    REQUIRE(board.piece_bitboards[BLACK][KING] == position_string_to_bitboard("c8"));
    REQUIRE(board.piece_bitboards[BLACK][ROOK] == (position_string_to_bitboard("d8") | position_string_to_bitboard("h8")));

    board.undo_move(move);
    REQUIRE(board.piece_bitboards[BLACK][KING] == position_string_to_bitboard("e8"));
    REQUIRE(board.piece_bitboards[BLACK][ROOK] == (position_string_to_bitboard("a8") | position_string_to_bitboard("h8")));
  }
}

TEST_CASE("Test execute_move and undo_move en passant", "[execute_move undo_move en passant]") {
  Board board;

  SECTION("white en passant capture e5d6") {
    board.set_piece(PAWN, WHITE, position_string_to_bitboard("e5"));
    board.set_piece(PAWN, BLACK, position_string_to_bitboard("d5"));

    Move move('e', 5, 'd', 6, 5);

    board.execute_move(move);

    REQUIRE(board.piece_bitboards[WHITE][PAWN] == position_string_to_bitboard("d6"));
    REQUIRE(board.piece_bitboards[BLACK][PAWN] == 0);
    for(int piece_index = 1; piece_index < 6; piece_index++) {
      for(int color_index = 0; color_index < 2; color_index ++) {
	REQUIRE(board.piece_bitboards[color_index][piece_index] == 0);
      }
    }

    board.undo_move(move);

    REQUIRE(board.piece_bitboards[WHITE][PAWN] == position_string_to_bitboard("e5"));
    REQUIRE(board.piece_bitboards[BLACK][PAWN] == position_string_to_bitboard("d5"));

    for(int piece_index = 1; piece_index < 6; piece_index++) {
      for(int color_index = 0; color_index < 2; color_index ++) {
	REQUIRE(board.piece_bitboards[color_index][piece_index] == 0);
      }
    }
  }
}

TEST_CASE("Test execute_move and undo_move promotion", "[execute_move undo_move promotion]") {
  Board board;
  board.set_piece(PAWN, WHITE, position_string_to_bitboard("a7"));

  
  SECTION("no promotion (pawn promotion)") {
    Move move('a', 7, 'a', 8, 0);
    board.execute_move(move);

    REQUIRE(board.piece_bitboards[WHITE][PAWN] == position_string_to_bitboard("a8"));

    board.undo_move(move);
  }

  SECTION("knight promotion") {
    Move move('a', 7, 'a', 8, 8);
    board.execute_move(move);

    REQUIRE(board.piece_bitboards[WHITE][PAWN] == 0);
    REQUIRE(board.piece_bitboards[WHITE][KNIGHT] == position_string_to_bitboard("a8"));

    board.undo_move(move);
  }

  SECTION("bishop promotion") {
    Move move('a', 7, 'a', 8, 9);
    board.execute_move(move);

    REQUIRE(board.piece_bitboards[WHITE][PAWN] == 0);
    REQUIRE(board.piece_bitboards[WHITE][BISHOP] == position_string_to_bitboard("a8"));

    board.undo_move(move);
  }

  SECTION("rook promotion") {
    Move move('a', 7, 'a', 8, 10);
    board.execute_move(move);

    REQUIRE(board.piece_bitboards[WHITE][PAWN] == 0);
    REQUIRE(board.piece_bitboards[WHITE][ROOK] == position_string_to_bitboard("a8"));

    board.undo_move(move);
  }

  SECTION("queen promotion") {
    Move move('a', 7, 'a', 8, 11);
    board.execute_move(move);

    REQUIRE(board.piece_bitboards[WHITE][PAWN] == 0);
    REQUIRE(board.piece_bitboards[WHITE][QUEEN] == position_string_to_bitboard("a8"));

    board.undo_move(move);
  }

  REQUIRE(board.piece_bitboards[WHITE][PAWN] == position_string_to_bitboard("a7"));
  REQUIRE(board.piece_bitboards[BLACK][PAWN] == 0);
  for(int piece_index = 1; piece_index < 6; piece_index++) {
    for(int color_index = 0; color_index < 2; color_index ++) {
      REQUIRE(board.piece_bitboards[color_index][piece_index] == 0);
    }
  }
}

TEST_CASE("Test execute_move capture promotion", "[execute_move undo_move capture promotion]") {
  Board board;
  board.set_piece(PAWN, WHITE, position_string_to_bitboard("a7"));
  board.set_piece(KNIGHT, BLACK, position_string_to_bitboard("b8"));

  SECTION("no promotion (pawn promotion") {
    Move move('a', 7, 'b', 8, 4);
    board.execute_move(move);

    REQUIRE(board.piece_bitboards[WHITE][PAWN] == position_string_to_bitboard("b8"));

    board.undo_move(move);
  }

  SECTION("knight promotion") {
    Move move('a', 7, 'b', 8, 12);
    board.execute_move(move);

    REQUIRE(board.piece_bitboards[WHITE][PAWN] == 0);
    REQUIRE(board.piece_bitboards[WHITE][KNIGHT] == position_string_to_bitboard("b8"));

    board.undo_move(move);
  }

  
  SECTION("bishop promotion") {
    Move move('a', 7, 'b', 8, 13);
    board.execute_move(move);

    REQUIRE(board.piece_bitboards[WHITE][PAWN] == 0);
    REQUIRE(board.piece_bitboards[WHITE][BISHOP] == position_string_to_bitboard("b8"));

    board.undo_move(move);
  }

  SECTION("rook promotion") {
    Move move('a', 7, 'b', 8, 14);
    board.execute_move(move);

    REQUIRE(board.piece_bitboards[WHITE][PAWN] == 0);
    REQUIRE(board.piece_bitboards[WHITE][ROOK] == position_string_to_bitboard("b8"));

    board.undo_move(move);
  }

  SECTION("queen promotion") {
    Move move('a', 7, 'b', 8, 15);
    board.execute_move(move);

    REQUIRE(board.piece_bitboards[WHITE][PAWN] == 0);
    REQUIRE(board.piece_bitboards[WHITE][QUEEN] == position_string_to_bitboard("b8"));

    board.undo_move(move);
  }

  REQUIRE(board.piece_bitboards[WHITE][PAWN] == position_string_to_bitboard("a7"));
  REQUIRE(board.piece_bitboards[BLACK][KNIGHT] == position_string_to_bitboard("b8"));
}

TEST_CASE("test castling and castle rights") {
  Board board;
  board.set_piece(KING, WHITE, position_string_to_bitboard("e1"));
  board.set_piece(ROOK, WHITE, position_string_to_bitboard("a1"));
  board.set_piece(ROOK, WHITE, position_string_to_bitboard("h1"));
  board.set_piece(KING, BLACK, position_string_to_bitboard("e8"));
  board.set_piece(ROOK, BLACK, position_string_to_bitboard("a8"));
  board.set_piece(ROOK, BLACK, position_string_to_bitboard("h8"));

  SECTION("white castles king side") {
    REQUIRE(board.get_can_castle_king(WHITE) == true);
    REQUIRE(board.get_can_castle_queen(WHITE) == true);
    
    Move move('e', 1, 'g', 1, 2);
    board.execute_move(move);

    REQUIRE(board.piece_bitboards[WHITE][KING] == position_string_to_bitboard("g1"));
    REQUIRE(board.piece_bitboards[WHITE][ROOK] == (position_string_to_bitboard("a1") | position_string_to_bitboard("f1")));
    REQUIRE(board.get_can_castle_king(WHITE) == false);
    REQUIRE(board.get_can_castle_queen(WHITE) == false);

    board.undo_move(move);
    
    REQUIRE(board.piece_bitboards[WHITE][KING] == position_string_to_bitboard("e1"));
    REQUIRE(board.piece_bitboards[WHITE][ROOK] == (position_string_to_bitboard("a1") | position_string_to_bitboard("h1")));
    REQUIRE(board.get_can_castle_king(WHITE) == true);
    REQUIRE(board.get_can_castle_queen(WHITE) == true);
  }

  SECTION("white castles queen side") {
    REQUIRE(board.get_can_castle_king(WHITE) == true);
    REQUIRE(board.get_can_castle_queen(WHITE) == true);
    
    Move move('e', 1, 'c', 1, 3);
    board.execute_move(move);

    REQUIRE(board.piece_bitboards[WHITE][KING] == position_string_to_bitboard("c1"));
    REQUIRE(board.piece_bitboards[WHITE][ROOK] == (position_string_to_bitboard("d1") | position_string_to_bitboard("h1")));
    REQUIRE(board.get_can_castle_king(WHITE) == false);
    REQUIRE(board.get_can_castle_queen(WHITE) == false);

    board.undo_move(move);
    
    REQUIRE(board.piece_bitboards[WHITE][KING] == position_string_to_bitboard("e1"));
    REQUIRE(board.piece_bitboards[WHITE][ROOK] == (position_string_to_bitboard("a1") | position_string_to_bitboard("h1")));
    REQUIRE(board.get_can_castle_king(WHITE) == true);
    REQUIRE(board.get_can_castle_queen(WHITE) == true);
  }

  board.set_turn_color(BLACK);

  SECTION("black castles king side") {
    REQUIRE(board.get_can_castle_king(BLACK) == true);
    REQUIRE(board.get_can_castle_queen(BLACK) == true);
    
    Move move('e', 8, 'g', 8, 2);
    board.execute_move(move);

    REQUIRE(board.piece_bitboards[BLACK][KING] == position_string_to_bitboard("g8"));
    REQUIRE(board.piece_bitboards[BLACK][ROOK] == (position_string_to_bitboard("a8") | position_string_to_bitboard("f8")));
    REQUIRE(board.get_can_castle_king(BLACK) == false);
    REQUIRE(board.get_can_castle_queen(BLACK) == false);

    board.undo_move(move);
    
    REQUIRE(board.piece_bitboards[BLACK][KING] == position_string_to_bitboard("e8"));
    REQUIRE(board.piece_bitboards[BLACK][ROOK] == (position_string_to_bitboard("a8") | position_string_to_bitboard("h8")));
    REQUIRE(board.get_can_castle_king(BLACK) == true);
    REQUIRE(board.get_can_castle_queen(BLACK) == true);
  }

  
  SECTION("black castles queen side") {
    REQUIRE(board.get_can_castle_king(WHITE) == true);
    REQUIRE(board.get_can_castle_queen(WHITE) == true);
    
    Move move('e', 8, 'c', 8, 3);
    board.execute_move(move);

    REQUIRE(board.piece_bitboards[BLACK][KING] == position_string_to_bitboard("c8"));
    REQUIRE(board.piece_bitboards[BLACK][ROOK] == (position_string_to_bitboard("d8") | position_string_to_bitboard("h8")));
    REQUIRE(board.get_can_castle_king(BLACK) == false);
    REQUIRE(board.get_can_castle_queen(BLACK) == false);

    board.undo_move(move);
    
    REQUIRE(board.piece_bitboards[BLACK][KING] == position_string_to_bitboard("e8"));
    REQUIRE(board.piece_bitboards[BLACK][ROOK] == (position_string_to_bitboard("a8") | position_string_to_bitboard("h8")));
    REQUIRE(board.get_can_castle_king(BLACK) == true);
    REQUIRE(board.get_can_castle_queen(BLACK) == true);
  }
}

TEST_CASE("test castle rights on non-castle moves") {
  Board board;
  board.set_piece(KING, WHITE, position_string_to_bitboard("e1"));
  board.set_piece(ROOK, WHITE, position_string_to_bitboard("a1"));
  board.set_piece(ROOK, WHITE, position_string_to_bitboard("h1"));
  board.set_piece(KING, BLACK, position_string_to_bitboard("e8"));
  board.set_piece(ROOK, BLACK, position_string_to_bitboard("a8"));
  board.set_piece(ROOK, BLACK, position_string_to_bitboard("h8"));
  
  board.set_piece(ROOK, WHITE, position_string_to_bitboard("a2"));

  SECTION("white non-castle king move removes both castle rights") {
    REQUIRE(board.get_can_castle_king(WHITE) == true);
    REQUIRE(board.get_can_castle_queen(WHITE) == true);

    Move move('e', 1, 'd', 1, 0);
    board.execute_move(move);

    REQUIRE(board.get_can_castle_king(WHITE) == false);
    REQUIRE(board.get_can_castle_queen(WHITE) == false);
  }

  SECTION("white queen side rook move removes queen side castle right") {
    REQUIRE(board.get_can_castle_king(WHITE) == true);
    REQUIRE(board.get_can_castle_queen(WHITE) == true);

    Move move('a', 1, 'b', 1, 0);
    board.execute_move(move);

    REQUIRE(board.get_can_castle_king(WHITE) == true);
    REQUIRE(board.get_can_castle_queen(WHITE) == false);
  }

  SECTION("white king side rook moves removes king side castle right") {
    REQUIRE(board.get_can_castle_king(WHITE) == true);
    REQUIRE(board.get_can_castle_queen(WHITE) == true);

    Move move('h', 1, 'h', 2, 0);
    board.execute_move(move);

    REQUIRE(board.get_can_castle_king(WHITE) == false);
    REQUIRE(board.get_can_castle_queen(WHITE) == true);
  }

  board.set_turn_color(BLACK);

  SECTION("black non-castle king move removes both castle rights") {
    REQUIRE(board.get_can_castle_king(BLACK) == true);
    REQUIRE(board.get_can_castle_queen(BLACK) == true);

    Move move('e', 8, 'd', 8, 0);
    board.execute_move(move);

    REQUIRE(board.get_can_castle_king(BLACK) == false);
    REQUIRE(board.get_can_castle_queen(BLACK) == false);
  }
  
  SECTION("white queen side rook move removes queen side castle right") {
    REQUIRE(board.get_can_castle_king(BLACK) == true);
    REQUIRE(board.get_can_castle_queen(BLACK) == true);

    Move move('a', 8, 'b', 8, 0);
    board.execute_move(move);

    REQUIRE(board.get_can_castle_king(BLACK) == true);
    REQUIRE(board.get_can_castle_queen(BLACK) == false);
  }
  
  SECTION("white king side rook moves removes king side castle right") {
    REQUIRE(board.get_can_castle_king(BLACK) == true);
    REQUIRE(board.get_can_castle_queen(BLACK) == true);

    Move move('h', 8, 'h', 7, 0);
    board.execute_move(move);

    REQUIRE(board.get_can_castle_king(BLACK) == false);
    REQUIRE(board.get_can_castle_queen(BLACK) == true);
  }

  board.set_turn_color(WHITE);
  
  SECTION("pawn move does not affect castle rights") {
    REQUIRE(board.get_can_castle_king(WHITE) == true);
    REQUIRE(board.get_can_castle_queen(WHITE) == true);

    Move move('a', 2, 'a', 3, 0);
    board.execute_move(move);

    REQUIRE(board.get_can_castle_king(WHITE) == true);
    REQUIRE(board.get_can_castle_queen(WHITE) == true);
  }
}

TEST_CASE("test is_position_attacked_by") {
  Board board;
  board.set_piece(ROOK, WHITE, position_string_to_bitboard("a1"));
  board.set_piece(ROOK, BLACK, position_string_to_bitboard("a8"));

  SECTION("a8 is attacked by white") {
    bool result = board.is_position_attacked_by(position_string_to_bitboard("a8"), WHITE);
    bool expected = true;
    REQUIRE(result == expected);
  }

  

  SECTION("b8 is not attacked by white") {
    bool result = board.is_position_attacked_by(position_string_to_bitboard("b8"), WHITE);
    bool expected = false;
    REQUIRE(result == expected);
  }

  SECTION("a1 is attacked by black") {
    bool result = board.is_position_attacked_by(position_string_to_bitboard("a1"), BLACK);
    bool expected = true;
    REQUIRE(result == expected);
  }

  SECTION("b1 is not attacked by black") {
    bool result = board.is_position_attacked_by(position_string_to_bitboard("b1"), BLACK);
    bool expected = false;
    REQUIRE(result == expected);
  }
  
}

TEST_CASE("test is_checked") {
  Board board;

  SECTION("white king attacked by rook") {
    board.set_piece(KING, WHITE, position_string_to_bitboard("e1"));
    board.set_piece(ROOK, BLACK, position_string_to_bitboard("e8"));
    REQUIRE(board.is_checked(WHITE) == true);
  }

  SECTION("white king not attacked by rook") {
    board.set_piece(KING, WHITE, position_string_to_bitboard("e1"));
    board.set_piece(ROOK, BLACK, position_string_to_bitboard("a8"));
    REQUIRE(board.is_checked(WHITE) == false);
  }

  SECTION("black king attacked by knight") {
    board.set_piece(KING, BLACK, position_string_to_bitboard("e8"));
    board.set_piece(KNIGHT, WHITE, position_string_to_bitboard("d6"));
    REQUIRE(board.is_checked(BLACK) == true);
  }

  SECTION("black king not attacked by pawn") {
    board.set_piece(KING, BLACK, position_string_to_bitboard("e8"));
    board.set_piece(PAWN, WHITE, position_string_to_bitboard("e7"));
    REQUIRE(board.is_checked(BLACK) == false);
  }

  SECTION("black king attacked by pawn") {
    board.set_piece(KING, BLACK, position_string_to_bitboard("e8"));
    board.set_piece(PAWN, WHITE, position_string_to_bitboard("d7"));
    REQUIRE(board.is_checked(BLACK) == true);
  }
}

TEST_CASE("test get_sliding_attacks") {
  Board board;

  SECTION("east works properly") {
    bitboard actual = east(position_string_to_bitboard("h3"));
    bitboard expected = 0;
    REQUIRE(actual == expected);
  }

  SECTION("test northeast from f1") {
    bitboard actual = board.generate_sliding_attacks(position_string_to_bitboard("f1"), NORTHEAST, board.get_blockers(position_string_to_bitboard("f1")));
    bitboard expected = 0x10200;
    REQUIRE(actual == expected);
  }
}

TEST_CASE("test is_move_legal") {
  Board board;
  board.set_piece(KING, WHITE, position_string_to_bitboard("e1"));
  board.set_piece(ROOK, WHITE, position_string_to_bitboard("h1"));
  board.set_piece(PAWN, WHITE, position_string_to_bitboard("c3"));
  board.set_piece(BISHOP, BLACK, position_string_to_bitboard("b4"));
  board.set_piece(ROOK, BLACK, position_string_to_bitboard("d8"));

  SECTION("rook move legal") {
    Move move('h', 1, 'h', 8, 0);
    REQUIRE(board.is_move_legal(move, WHITE) == true);
  }

  SECTION("king move right legal") {
    Move move('e', 1, 'f', 1, 0);
    REQUIRE(board.is_move_legal(move, WHITE) == true);
  }
  
  SECTION("king move left illegal") {
    Move move('e', 1, 'd', 1, 0);
    REQUIRE(board.is_move_legal(move, WHITE) == false);
  }

  SECTION("pawn push illegal") {
    Move move('c', 3, 'c', 4, 0);
    REQUIRE(board.is_move_legal(move, WHITE) == false);
  }

  SECTION("pawn capture legal") {
    Move move('c', 3, 'b', 4, 4);
    REQUIRE(board.is_move_legal(move, WHITE) == true);
  }
}

#endif
