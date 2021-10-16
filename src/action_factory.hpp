#ifndef ACTION_FACTORY_H
#define ACTION_FACTORY_H

#include <optional>
#include <memory>
#include "hickey_action.hpp"
#include "input_event.hpp"
#include <queue>

namespace rebarhickey
{
  class Hickey;

  class ActionFactory
  {
  public:
    
    virtual std::optional<std::unique_ptr<HickeyAction>> next_action(
      const std::queue<std::unique_ptr<engine::input::InputEvent>>&,
      const Hickey& hickey
      ) = 0;

    virtual ~ActionFactory() = default;

  };
}

#endif
