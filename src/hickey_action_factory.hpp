#ifndef HICKEY_ACTION_FACTORY_H
#define HICKEY_ACTION_FACTORY_H

#include "buffer_action_factory.hpp"
#include "hickey_action.hpp"
#include <optional>
#include <memory>
#include "engine.hpp"
#include "gap_buffer.hpp"

namespace rebarhickey
{
  class Hickey;

  class HickeyActionFactory
  {
  public:

    HickeyActionFactory( engine::Engine& engine );

    std::optional<std::unique_ptr<HickeyAction>> next_action( Hickey& );
    
  private:
    
    std::unique_ptr<BufferActionFactory> buffer_factory;
    
  };
}

#endif
