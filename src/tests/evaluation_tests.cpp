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
}

#endif
