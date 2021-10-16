#ifndef HICKEY_ACTION_FACTORY_H
#define HICKEY_ACTION_FACTORY_H

#include "hickey_action.hpp"
#include <optional>
#include <memory>
#include "engine.hpp"
#include "gap_buffer.hpp"
#include "action_factory.hpp"

namespace rebarhickey
{
  class Hickey;

  class HickeyActionFactory
  {
  public:

    HickeyActionFactory( engine::Engine& engine );

    std::optional<std::unique_ptr<HickeyAction>> next_action( Hickey& );
    
  private:

    engine::Engine& engine;
    std::queue<std::unique_ptr<engine::input::InputEvent>>& event_queue;
    std::vector<std::unique_ptr<ActionFactory>> action_factories;
    
  };
}

#endif
