#ifndef PERFT_TESTS_CPP // GUARD
#define PERFT_TESTS_CPP // GUARD

#include "iostream"
#include <catch2/catch_test_macros.hpp>

#include "../MoveGenerator.hpp"

TEST_CASE("perft position 3 results up to depth 5") {
  Board board;
  MoveGenerator move_gen;

  board.initialize_perft_position_3();

  SECTION("depth 1") {
    uint64_t result = move_gen.fast_perft(1, board);
    REQUIRE(result == 14);
  }

  SECTION("depth 2") {
    uint64_t result = move_gen.fast_perft(2, board);
    REQUIRE(result == 191);
  }

  SECTION("depth 3") {
    uint64_t result = move_gen.fast_perft(3, board);
    REQUIRE(result == 2812);
  }

  SECTION("depth 4") {
    uint64_t result = move_gen.fast_perft(4, board);
    REQUIRE(result == 43238);
  }

  SECTION("depth 5") {
    uint64_t result = move_gen.fast_perft(5, board);
    REQUIRE(result == 674624);
  }
}

TEST_CASE("perft position 2 results up to depth 4") {
  Board board;
  MoveGenerator move_gen;

  board.initialize_perft_position_2();

  SECTION("depth 1") {
    uint64_t result = move_gen.pl_perft(1, board);
    REQUIRE(result == 48);
  }

  SECTION("depth 2") {
    uint64_t result = move_gen.pl_perft(2, board);
    REQUIRE(result == 2039);
  }

  SECTION("depth 3") {
    uint64_t result = move_gen.pl_perft(3, board);
    REQUIRE(result == 97862);
  }

  SECTION("depth 4") {
    uint64_t result = move_gen.pl_perft(4, board);
    REQUIRE(result == 4085603);
  }
}

TEST_CASE("perft startpos up to depth 5") {
  Board board;
  MoveGenerator move_gen;

  board.initialize_board_starting_position();

  SECTION("depth 1") {
    uint64_t result = move_gen.fast_perft(1, board);
    REQUIRE(result == 20);
  }

  SECTION("depth 2") {
    uint64_t result = move_gen.fast_perft(2, board);
    REQUIRE(result == 400);
  }

  SECTION("depth 3") {
    uint64_t result = move_gen.fast_perft(3, board);
    REQUIRE(result == 8902);
  }

  SECTION("depth 4") {
    uint64_t result = move_gen.fast_perft(4, board);
    REQUIRE(result == 197281);
  }

  SECTION("depth 5") {
    uint64_t result = move_gen.pl_perft(5, board);
    REQUIRE(result == 4865609);
  }

  /* slow running
  SECTION("depth 6") {
    uint64_t result = move_gen.pl_perft(6, board);
    REQUIRE(result == 119060324);
  }
  */
}

#endif // GUARD
