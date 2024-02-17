cmake_minimum_required(VERSION 3.2)
project(ChessEngine VERSION 1.0)

set (CMAKE_CXX_FLAGS "-Dprivate=public")
Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

add_executable(main main.cpp Move.cpp)

add_executable(move_tests tests/move_tests.cpp Move.cpp)
target_link_libraries(move_tests PRIVATE Catch2::Catch2WithMain)
