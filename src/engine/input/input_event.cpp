#include "input_event.hpp"
#include "input_type.hpp"
#include <string>

using rebarhickey::engine::input::InputEvent;
using rebarhickey::engine::input::InputType;

InputEvent::InputEvent( InputType current, InputType previous )
  : current_frame_input( current ), previous_frame_input( previous )
{}

std::optional<InputType> InputEvent::key_pressed() const
{
  std::optional<InputType> key_type {};
  if( current_frame_input != previous_frame_input &&
      current_frame_input != InputType::none )
  {
    key_type = std::optional<InputType> { current_frame_input };
  }
  
  return key_type;
}

bool InputEvent::escape() const
{
  return current_frame_input == InputType::escape;
}


