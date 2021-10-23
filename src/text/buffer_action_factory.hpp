#ifndef BUFFER_ACTION_FACTORY_H
#define BUFFER_ACTION_FACTORY_H

#include "buffer_action.hpp"
#include <optional>
#include <memory>
#include "engine.hpp"
#include "action_factory.hpp"
#include <functional>

namespace rebarhickey::text
{
  class BufferActionFactory : public ActionFactory
  {
  public:

    BufferActionFactory();

    ~BufferActionFactory() = default;

    std::optional<std::unique_ptr<HickeyAction>> next_action(
      const std::queue<std::unique_ptr<engine::input::InputEvent>>&,
      const Hickey& hickey
      ) override;

  private:
    
    std::map<engine::input::InputType, char> insertion_types;
    std::map<engine::input::InputType, int> removal_types;
    std::map<engine::input::InputType, std::function<void( GapBuffer& )>> cursor_types;
  };
}

#endif
