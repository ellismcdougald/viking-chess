#ifndef EVALUATION_TESTS_CPP // GUARD
#define EVALUATION_TESTS_CPP // GUARD

#include"iostream"
#include <catch2/catch_test_macros.hpp>

#include "../Evaluation.hpp"

TEST_CASE("Test") {
  Evaluation eval;
  Board board;

  SECTION("empty board") {
    int result = eval.evaluate(board);
    REQUIRE(result == 0);
  }

  SECTION("starting position") {
    board.initialize_board_starting_position();
    int result = eval.evaluate(board);
    REQUIRE(result == 0);
  }

  SECTION("even") {
    board.set_piece_positions(PAWN, WHITE, 0xFF00); // add 8 white pawns
    board.set_piece_positions(PAWN, BLACK, 0xF000000000000); // add 4 black pawns
    board.set_piece_positions(ROOK, WHITE, 0x81); // add 2 white rooks
    board.set_piece_positions(ROOK, BLACK, 0x8000000000000000); // add one black rook
    board.set_piece_positions(QUEEN, BLACK, 0x800000000000000); // add one black queen

    int result = eval.evaluate(board);
    REQUIRE(result == 0);
  }

  SECTION("uneven") {
    board.set_piece_positions(PAWN, WHITE, 0xFF00); // add 8 white pawns
    board.set_piece_positions(ROOK, WHITE, 0x81); // add 2 white rooks
    board.set_piece_positions(ROOK, BLACK, 0x8000000000000000); // add one black rook
    board.set_piece_positions(QUEEN, BLACK, 0x800000000000000); // add one black queen

    int result = eval.evaluate(board);
    REQUIRE(result == 4);
  }

  SECTION("perft position 2") {
    board.initialize_perft_position_2();
    int result = eval.evaluate(board);
    REQUIRE(result == 0);
  }

  SECTION("perft position 3") {
    board.initialize_perft_position_3();
    int result = eval.evaluate(board);
    REQUIRE(result == 0);
  }
}

#endif
