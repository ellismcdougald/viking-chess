/*
 * UCI interface.
 */

#include "Engine.hpp"

#ifndef UCI_HPP // GUARD
#define UCI_HPP // GUARD

class Uci {
public:
  // Constructor
  Uci();

  void loop();

private:
  Engine engine;

  inline void search() { engine.search_best_move(); }
};

#endif
