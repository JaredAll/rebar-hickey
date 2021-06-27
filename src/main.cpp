#include "hickey.hpp"
#include <memory>

using rebarhickey::Hickey;

int main( int argc, char* argv[] )
{
  std::unique_ptr<Hickey> hickey = std::make_unique<Hickey>();
  return hickey -> run();
}
