#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "SDL_events.h"
#include "input_event.hpp"
#include <SDL.h>
#include <memory>

namespace rebarhickey::engine::input
{

  class InputHandler
  {
  public:

    InputHandler();

    InputEvent& handle_input();

  private:

    void determine_input();

    std::unique_ptr<InputEvent> current_event;
    SDL_Event e;
    const Uint8* keyboard_state;
    InputType previous_input_type;
    InputType current_input_type;
  };

}

#endif
