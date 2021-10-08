#ifndef BUFFER_ACTION_FACTORY_H
#define BUFFER_ACTION_FACTORY_H

#include "buffer_action.hpp"
#include <optional>
#include <memory>
#include "engine.hpp"

namespace rebarhickey
{
  class BufferActionFactory
  {
  public:

    BufferActionFactory( engine::Engine& engine );

    std::optional<std::unique_ptr<text::BufferAction>> next_action();

  private:
    
    engine::Engine& engine;
    std::map<engine::input::InputType, char> insertion_types;
    std::map<engine::input::InputType, int> removal_types;
  };
}

#endif
