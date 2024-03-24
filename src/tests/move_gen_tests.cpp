#ifndef MOVE_GEN_TESTS_CPP // GUARD
#define MOVE_GEN_TESTS_CPP // GUARD

#include"iostream"
#include <catch2/catch_test_macros.hpp>

#include "../MoveGenerator.hpp"

bool move_vec_contains(std::vector<Move> &moves, Move &move);
void print_move_vec(std::vector<Move> &moves);

TEST_CASE("test pawn move gneration") {
  Board board;
  MoveGenerator move_gen;

  SECTION("two centre pawns") {
    board.set_piece(PAWN, WHITE, position_string_to_bitboard("d4"));
    board.set_piece(PAWN, WHITE, position_string_to_bitboard("e4"));

    std::vector<Move> pawn_pseudo_legal_moves;

    move_gen.add_pseudo_legal_pawn_moves(board, WHITE, pawn_pseudo_legal_moves);

    REQUIRE(pawn_pseudo_legal_moves.size() == 2);
    Move move_one('d', 4, 'd', 5, 0);
    REQUIRE(move_vec_contains(pawn_pseudo_legal_moves, move_one));
    Move move_two('e', 4, 'e', 5, 0);
    REQUIRE(move_vec_contains(pawn_pseudo_legal_moves, move_two));
  }

  SECTION("two double push pawns") {
    board.set_piece(PAWN, BLACK, position_string_to_bitboard("d7"));
    board.set_piece(PAWN, BLACK, position_string_to_bitboard("g7"));

    std::vector<Move> pawn_pseudo_legal_moves;

    move_gen.add_pseudo_legal_pawn_moves(board, BLACK, pawn_pseudo_legal_moves);

    REQUIRE(pawn_pseudo_legal_moves.size() == 4);
    Move move_one('d', 7, 'd', 6, 0);
    REQUIRE(move_vec_contains(pawn_pseudo_legal_moves, move_one));
    Move move_two('d', 7, 'd', 5, 1);
    REQUIRE(move_vec_contains(pawn_pseudo_legal_moves, move_two));
    Move move_three('g', 7, 'g', 6, 0);
    REQUIRE(move_vec_contains(pawn_pseudo_legal_moves, move_three));
    Move move_four('g', 7, 'g', 5, 1);
    REQUIRE(move_vec_contains(pawn_pseudo_legal_moves, move_four));
  }

  SECTION("four opposing centre pawns") {
    board.set_piece(PAWN, WHITE, position_string_to_bitboard("d4"));
    board.set_piece(PAWN, WHITE, position_string_to_bitboard("e4"));
    board.set_piece(PAWN, BLACK, position_string_to_bitboard("d5"));
    board.set_piece(PAWN, BLACK, position_string_to_bitboard("e5"));

    std::vector<Move> white_pawn_pseudo_legal_moves;
    move_gen.add_pseudo_legal_pawn_moves(board, WHITE, white_pawn_pseudo_legal_moves);

    REQUIRE(white_pawn_pseudo_legal_moves.size() == 2);
    Move move_one('d', 4, 'e', 5, 4);
    REQUIRE(move_vec_contains(white_pawn_pseudo_legal_moves, move_one));
    Move move_two('e', 4, 'd', 5, 4);
    REQUIRE(move_vec_contains(white_pawn_pseudo_legal_moves, move_two));

    std::vector<Move> black_pawn_pseudo_legal_moves;
    move_gen.add_pseudo_legal_pawn_moves(board, BLACK, black_pawn_pseudo_legal_moves);

    REQUIRE(black_pawn_pseudo_legal_moves.size() == 2);
    Move move_three('d', 5, 'e', 4, 4);
    REQUIRE(move_vec_contains(black_pawn_pseudo_legal_moves, move_three));
    Move move_four('e', 5, 'd', 4, 4);
    REQUIRE(move_vec_contains(black_pawn_pseudo_legal_moves, move_four));
  }
}


// Helpers:
bool move_vec_contains(std::vector<Move> &moves, Move &move) {
  for(auto & element : moves) {
    if(element.move_equals(move)) return true;
  }
  return false;
}

void print_move_vec(std::vector<Move> &moves) {
  for(auto &move : moves) {
    move.print();
  }
}

#endif
