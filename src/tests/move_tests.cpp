#ifndef MOVE_TESTS_CPP // GUARD
#define MOVE_TESTS_CPP

#include "iostream"
#include <catch2/catch_test_macros.hpp>

#include "../globals.hpp"
#include "../Move.hpp"

TEST_CASE("Testing move implementation on a1h8", "[move]") {
  Move move('a', 1, 'h', 8, 0b0000);

  SECTION("Test get_origin") {
    bitboard actual = move.get_origin();
    bitboard expected = 0x80;
    REQUIRE(actual == expected);
  }

  SECTION("Test get_destination") {
    bitboard actual = move.get_destination();
    bitboard expected = 0x100000000000000;
    REQUIRE(actual == expected);
  }
  
  SECTION("Test get_flags") {
    unsigned actual = move.get_flags();
    unsigned expected = 0;
    REQUIRE(actual == expected);
  }
}

TEST_CASE("Testing move implementation on d4e5 capture", "[move]") {
  Move move('d', 4, 'e', 5, 4);

  SECTION("Test get_origin") {
    bitboard actual = move.get_origin();
    bitboard expected = 0x10000000;
    REQUIRE(actual == expected);
  }

  SECTION("Test get_destination") {
    bitboard actual = move.get_destination();
    bitboard expected = 0x800000000;
    REQUIRE(actual == expected);
  }
  
  SECTION("Test get_flags") {
    unsigned actual = move.get_flags();
    unsigned expected = 4;
    REQUIRE(actual == expected);
  }
}

TEST_CASE("testget_row_col_from_position") {
  Move move('a', 1, 'a', 2, 0);
  SECTION("a1") {
    std::string res = move.get_row_col_from_position(position_string_to_bitboard("a1"));
    REQUIRE(res == "a1");
  }

  SECTION("d4") {
    std::string res = move.get_row_col_from_position(position_string_to_bitboard("d4"));
    REQUIRE(res == "d4");
  }

  SECTION("h8") {
    std::string res = move.get_row_col_from_position(position_string_to_bitboard("h8"));
    REQUIRE(res == "h8");
  }
}

TEST_CASE("test bitboard constructor") {
  SECTION("test 1") {
    Move move(position_string_to_bitboard("d4"), position_string_to_bitboard("d5"), 0);

    REQUIRE(move.get_origin() == position_string_to_bitboard("d4"));
    REQUIRE(move.get_destination() == position_string_to_bitboard("d5"));
    REQUIRE(move.get_flags() == 0);
  }
}

#endif
