#ifndef PERFT_TESTS_CPP // GUARD
#define PERFT_TESTS_CPP // GUARD

#include"iostream"
#include <catch2/catch_test_macros.hpp>

#include "../MoveGenerator.hpp"

void print_results(std::array<uint64_t, 3> results);


TEST_CASE("perft position 2 results") {
  Board board;
  MoveGenerator move_gen;

  board.initialize_perft_position_2();

  
  SECTION("depth 1") {
    uint64_t result = move_gen.fast_perft(1, board);
    REQUIRE(result == 48);
  }
  

  SECTION("depth 2") {
    uint64_t result = move_gen.fast_perft(2, board);
    REQUIRE(result == 2039);
  }

  SECTION("depth 3") {
    uint64_t result = move_gen.fast_perft(3, board);
    REQUIRE(result == 97862);
  }

  SECTION("depth 4") {
    uint64_t result = move_gen.fast_perft(4, board);
    REQUIRE(result == 4085603);
  }
}



/*
TEST_CASE("perft position 3 trace") {
  Board board;
  MoveGenerator move_gen;

  board.initialize_perft_position_2();

  SECTION("c3b1") {
    Move move_one('c', 3, 'b', 1, 0);
    board.execute_move(move_one);

    Move move_two('a', 6, 'b', 5, 0);
    board.execute_move(move_two);

    std::vector<Move> legal_moves = move_gen.generate_legal_moves(board, WHITE);
    std::cout << legal_moves.size() << "\n";

    for(int i = 0; i < legal_moves.size(); i++) {
      legal_moves[i].print_full();
    }


  }
}
*/






/*
TEST_CASE("perft position 3 debug") {
  Board board;
  MoveGenerator move_gen;

  board.initialize_perft_position_2();

  //move_gen.perft(2, board, WHITE);

  SECTION("trace\n") {
    std::array<std::array<bool, 2>, 2> can_castle = board.can_castle;
    Move move_one('h', 1, 'g', 1, 0);
    board.execute_move(move_one);

    std::vector<Move> legal_moves_black = move_gen.generate_legal_moves(board, BLACK);
    for(int i = 0; i < legal_moves_black.size(); i++) {
      board.execute_move(legal_moves_black[i]);

      std::vector<Move> legal_moves_white = move_gen.generate_legal_moves(board, WHITE);
      for(int j = 0; j < legal_moves_white.size(); j++) {
	board.execute_move(legal_moves_white[j]);
	board.undo_move(legal_moves_white[j]);
      }
      board.undo_move(legal_moves_black[i]);
    }

    board.undo_move(move_one);

    REQUIRE(board.can_castle == can_castle);

    
  }
}
*/


/*
TEST_CASE("perft position 2 debug") {
  Board board;
  MoveGenerator move_gen;

  board.initialize_perft_position_2();

  SECTION("e5d7") {
    Move move('e', 5, 'd', 7, 4);
    board.execute_move(move);

    std::vector<Move> legal_moves = move_gen.generate_legal_moves(board, BLACK);
    std::cout << legal_moves.size() << "\n";

    for(int i = 0; i < legal_moves.size(); i++) {
      legal_moves[i].print_full();
    }

  }
}
*/



/*

TEST_CASE("perft") {
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
    uint64_t result = move_gen.fast_perft(5, board);
    REQUIRE(result == 4865609);
  }


  SECTION("depth 6") {
    uint64_t result = move_gen.perft(6, board, WHITE);
    REQUIRE(result == 119060324);
  }

}
*/

/*
TEST_CASE("perft depth 3") {
  Board board;
  MoveGenerator move_gen;

  board.initialize_board_starting_position();

  SECTION("first move b1c3 then a7a6") {
    Move move_one('b', 1, 'c', 3, 0);
    board.execute_move(move_one);
    Move move_two('a', 7, 'a', 6, 0);
    board.execute_move(move_two);

    uint64_t result = move_gen.divide(1, board, WHITE);
  }
}
*/












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
