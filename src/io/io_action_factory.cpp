#include "io_action_factory.hpp"
#include "input_type.hpp"
#include "io_executor.hpp"
#include <iostream>
#include <memory>

using rebarhickey::io::IoActionFactory;
using rebarhickey::io::IoExecutor;
using rebarhickey::HickeyAction;
using rebarhickey::Hickey;
using rebarhickey::engine::input::InputEvent;

using std::optional;
using std::unique_ptr;


IoActionFactory::IoActionFactory() {}

std::optional<std::unique_ptr<HickeyAction>> IoActionFactory::next_action(
  const std::queue<std::unique_ptr<rebarhickey::engine::input::InputEvent>>& event_queue,
  const Hickey& hickey
  ) {

  optional<unique_ptr<HickeyAction>> hickey_action_optional {};

  if( !event_queue.empty() )
  {
    engine::input::InputEvent& event = *event_queue.front();

    optional<engine::input::InputType> input_type_optional = event.key_pressed();
    
    if( event.is_control_down() && input_type_optional.has_value() )
    {
      if( input_type_optional.value() == engine::input::InputType::whiskey )
      {
        hickey_action_optional = { std::make_unique<IoExecutor>( hickey ) };
      }
    }
  }
  
  return hickey_action_optional;
}
