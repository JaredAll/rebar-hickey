#include "engine.hpp"
#include <cmath>
#include <memory>

using rebarhickey::engine::Engine;

int main( int argc, char* argv[] )
{
  std::unique_ptr<Engine> engine = std::make_unique<Engine>();
  
  return 0;
}
