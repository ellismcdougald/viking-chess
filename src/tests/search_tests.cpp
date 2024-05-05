#include"iostream"
#include <catch2/catch_test_macros.hpp>

#include "../Search.hpp"

TEST_CASE("Test search") {
  Search search;
}

TEST_CASE("Starting position") {
  Board board;
  MoveGenerator move_gen;
  Search search;
  Evaluation eval;

  SECTION("Starting position depth 1") {
    board.initialize_board_starting_position();
    int score = search.alpha_beta_max_root(-10000, 10000, 1, board, move_gen, eval);
    search.best_move.print();
    std::cout << "\n";
    REQUIRE(score == 0);
  }

  SECTION("Starting position second move") {
    board.initialize_board_starting_position();
    Move move_one('h', 2, 'h', 3, 0);
    board.execute_move(move_one);
    int score = search.alpha_beta_max_root(-10000, 10000, 5, board, move_gen, eval);
    search.best_move.print();
    std::cout << "\n";
    REQUIRE(score == 0);
  }

  SECTION("Starting position third move") {
    board.initialize_board_starting_position();
    Move move_one('h', 2, 'h', 3, 0);
    board.execute_move(move_one);
    Move move_two('h', 7, 'h', 6, 0);
    board.execute_move(move_two);
    int score = search.alpha_beta_max_root(-10000, 10000, 5, board, move_gen, eval);
    search.best_move.print();
    std::cout << "\n";
    REQUIRE(score == 0);
  }
}
