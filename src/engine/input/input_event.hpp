#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H

#include "input_type.hpp"
#include <optional>

namespace rebarhickey::engine::input
{

  class InputEvent
  {
  public:

    InputEvent( InputType current, InputType previous );

    std::optional<InputType> key_pressed() const;

    bool escape() const;

  private:  

    InputType current_frame_input;
    InputType previous_frame_input;

  };

}

#endif
