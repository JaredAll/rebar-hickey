#ifndef IO_ACTION_FACTORY_H
#define IO_ACTION_FACTORY_H

#include "action_factory.hpp"
#include <map>

namespace rebarhickey::io
{
  class IoActionFactory : public ActionFactory
  {
  public:

    IoActionFactory();

    ~IoActionFactory() = default;

    std::optional<std::unique_ptr<HickeyAction>> next_action(
      const std::queue<std::unique_ptr<engine::input::InputEvent>>&,
      const Hickey& hickey
      ) override;

  };
}

#endif
