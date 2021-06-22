#ifndef REBARHICKEY
#define REBARHICKEY

#include <memory>
#include "engine.hpp"

using rebarhickey::engine::Engine;

namespace rebarhickey
{
  
  class Hickey
  {
  public:

    Hickey();

    int run();

  private:

    std::unique_ptr<Engine> engine;

  };

}

#endif
