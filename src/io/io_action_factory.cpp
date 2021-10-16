#include "io_action_factory.hpp"

using rebarhickey::io::IoActionFactory;
using rebarhickey::HickeyAction;
using rebarhickey::Hickey;
using rebarhickey::engine::input::InputEvent;

IoActionFactory::IoActionFactory() {}

std::optional<std::unique_ptr<HickeyAction>> IoActionFactory::next_action(
  const std::queue<std::unique_ptr<rebarhickey::engine::input::InputEvent>>&,
  const Hickey& hickey
  ) {
  return {};
}
