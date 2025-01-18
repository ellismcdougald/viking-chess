cmake_minimum_required(VERSION 3.10)
project(Viking-Chess-Engine VERSION 1.0)

set (CMAKE_CXX_FLAGS "-std=c++11")
Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

### VIKING (engine executable) 
add_executable(viking main.cpp Board.cpp Move.cpp MoveGenerator.cpp MoveList.cpp Evaluation.cpp Search.cpp globals.cpp Uci.cpp Engine.cpp TTable.cpp PVTable.cpp)

set (CMAKE_CXX_FLAGS "-Dprivate=public -std=c++11") # private members are public for testing

### BOARD TESTS
add_executable(board_tests tests/board_tests.cpp Board.cpp Move.cpp globals.cpp)
target_link_libraries(board_tests PRIVATE Catch2::Catch2WithMain)

### MOVE TESTS
add_executable(move_tests tests/move_tests.cpp Move.cpp globals.cpp)
target_link_libraries(move_tests PRIVATE Catch2::Catch2WithMain)

### MOVE GENERATION TESTS
add_executable(move_gen_tests tests/move_gen_tests.cpp MoveGenerator.cpp MoveList.cpp Board.cpp Move.cpp globals.cpp)
target_link_libraries(move_gen_tests PRIVATE Catch2::Catch2WithMain)

### PERFT TESTS (Move Generation)
add_executable(perft_tests tests/perft_tests.cpp MoveGenerator.cpp MoveList.cpp Board.cpp Move.cpp globals.cpp)
target_link_libraries(perft_tests PRIVATE Catch2::Catch2WithMain)

### EVALUATION TESTS
add_executable(eval_tests tests/evaluation_tests.cpp Evaluation.cpp Board.cpp Move.cpp globals.cpp)
target_link_libraries(eval_tests PRIVATE Catch2::Catch2WithMain)
