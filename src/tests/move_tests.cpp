#ifndef MOVE_TESTS_CPP // GUARD
#define MOVE_TESTS_CPP

#include "iostream"
#include <catch2/catch_test_macros.hpp>

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


#endif
