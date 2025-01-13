cmake_minimum_required(VERSION 3.5)
project(ChessEngine VERSION 1.0)

set (CMAKE_CXX_FLAGS "-Dprivate=public -std=c++11")
Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

add_executable(main main.cpp Board.cpp Move.cpp MoveGenerator.cpp MoveList.cpp Evaluation.cpp Search.cpp globals.cpp Uci.cpp Engine.cpp)

add_executable(perft perft.cpp Board.cpp Move.cpp MoveGenerator.cpp MoveList.cpp globals.cpp)

add_executable(move_tests tests/move_tests.cpp Move.cpp globals.cpp)
target_link_libraries(move_tests PRIVATE Catch2::Catch2WithMain)

add_executable(board_tests tests/board_tests.cpp Board.cpp Move.cpp globals.cpp)
target_link_libraries(board_tests PRIVATE Catch2::Catch2WithMain)

add_executable(move_gen_tests tests/move_gen_tests.cpp MoveGenerator.cpp MoveList.cpp Board.cpp Move.cpp globals.cpp)
target_link_libraries(move_gen_tests PRIVATE Catch2::Catch2WithMain)

add_executable(perft_tests tests/perft_tests.cpp MoveGenerator.cpp MoveList.cpp Board.cpp Move.cpp globals.cpp)
target_link_libraries(perft_tests PRIVATE Catch2::Catch2WithMain)

add_executable(eval_tests tests/evaluation_tests.cpp Evaluation.cpp Board.cpp Move.cpp globals.cpp)
target_link_libraries(eval_tests PRIVATE Catch2::Catch2WithMain)

add_executable(search_tests tests/search_tests.cpp Search.cpp Evaluation.cpp Board.cpp Move.cpp MoveGenerator.cpp MoveList.cpp globals.cpp)
target_link_libraries(search_tests PRIVATE Catch2::Catch2WithMain)
