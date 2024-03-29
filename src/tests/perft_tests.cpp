#ifndef PERFT_TESTS_CPP // GUARD
#define PERFT_TESTS_CPP // GUARD

#include"iostream"
#include <catch2/catch_test_macros.hpp>

#include "../MoveGenerator.hpp"

void print_results(std::array<uint64_t, 3> results);


TEST_CASE("perft") {
  Board board;
  MoveGenerator move_gen;

  board.initialize_board_starting_position();

  SECTION("depth 1") {
    uint64_t result = move_gen.perft(1, board, WHITE);
    REQUIRE(result == 20);
  }

  SECTION("depth 2") {
    uint64_t result = move_gen.perft(2, board, WHITE);
    REQUIRE(result == 400);
  }

  SECTION("depth 3") {
    uint64_t result = move_gen.divide(3, board, WHITE);
  }
}


/*
TEST_CASE("detailed perft") {
  Board board;
  MoveGenerator move_gen;

  board.initialize_board_starting_position();

  SECTION("depth 1") {
    std::array<uint64_t, 3> results = move_gen.detailed_perft(1, board, WHITE);
    REQUIRE(results[0] == 20);
  }

  SECTION("depth 2") {
    std::array<uint64_t, 3> results = move_gen.detailed_perft(2, board, WHITE);
    REQUIRE(results[0] == 400);
  }

  SECTION("depth 3") {
    std::array<uint64_t, 3> results = move_gen.detailed_perft(3, board, WHITE);
    print_results(results);
    REQUIRE(results[0] == 8902);
  }
}
*/

void print_results(std::array<uint64_t, 3> results) {
  std::cout << "Total: " << results[0] << "\n";
  std::cout << "Quiet: " << results[1] << "\n";
  std::cout << "Capture: " << results[2] << "\n";
}

#endif // GUARD
