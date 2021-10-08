#include "input_handler.hpp"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "input_type.hpp"
#include <future>
#include <iostream>

using std::unique_ptr;
using std::make_unique;
using rebarhickey::engine::input::InputHandler;
using rebarhickey::engine::input::InputEvent;

InputHandler::InputHandler()
{
  keyboard_state = SDL_GetKeyboardState( NULL );
  current_input_type = InputType::none;
  previous_input_type = InputType::none;

  polling = true;
}

InputHandler::~InputHandler()
{
  polling = false;
}

void InputHandler::initialize()
{
  std::thread input_poller{ [=](){ determine_input(); } };
  input_poller.detach();
}

void InputHandler::determine_input()
{
  while( polling )
  {
    previous_input_type = current_input_type;
  
    while( SDL_PollEvent( &e ))
    {
      if( e.type == SDL_KEYDOWN )
      {
        SDL_Keycode keycode = e.key.keysym.sym;
        switch(keycode)
        {
        case SDLK_RIGHT:
          current_input_type = InputType::right;
          break;
        case SDLK_LEFT:
          current_input_type = InputType::left;
          break;
        case SDLK_DOWN:
          current_input_type = InputType::down;
          break;
        case SDLK_UP:
          current_input_type = InputType::up;
          break;
        case SDLK_RETURN:
          current_input_type = InputType::enter;
          break;
        case SDLK_ESCAPE:
          current_input_type = InputType::escape;
          break;
        case SDLK_a:
          current_input_type = InputType::alpha;
          break;
        case SDLK_b:
          current_input_type = InputType::bravo;
          break;
        case SDLK_c:
          current_input_type = InputType::charlie;
          break;
        case SDLK_d:
          current_input_type = InputType::delta;
          break;
        case SDLK_e:
          current_input_type = InputType::echo;
          break;
        case SDLK_f:
          current_input_type = InputType::foxtrot;
          break;
        case SDLK_g:
          current_input_type = InputType::golf;
          break;
        case SDLK_h:
          current_input_type = InputType::hotel;
          break;
        case SDLK_i:
          current_input_type = InputType::india;
          break;
        case SDLK_j:
          current_input_type = InputType::juliett;
          break;
        case SDLK_k:
          current_input_type = InputType::kilo;
          break;
        case SDLK_l:
          current_input_type = InputType::lima;
          break;
        case SDLK_m:
          current_input_type = InputType::mike;
          break;
        case SDLK_n:
          current_input_type = InputType::november;
          break;
        case SDLK_o:
          current_input_type = InputType::oscar;
          break;
        case SDLK_p:
          current_input_type = InputType::papa;
          break;
        case SDLK_q:
          current_input_type = InputType::quebec;
          break;
        case SDLK_r:
          current_input_type = InputType::romeo;
          break;
        case SDLK_s:
          current_input_type = InputType::sierra;
          break;
        case SDLK_t:
          current_input_type = InputType::tango;
          break;
        case SDLK_u:
          current_input_type = InputType::uniform;
          break;
        case SDLK_v:
          current_input_type = InputType::victor;
          break;
        case SDLK_w:
          current_input_type = InputType::whiskey;
          break;
        case SDLK_x:
          current_input_type = InputType::xray;
          break;
        case SDLK_y:
          current_input_type = InputType::yankee;
          break;
        case SDLK_z:
          current_input_type = InputType::zulu;
          break;
        case SDLK_SPACE:
          current_input_type = InputType::space;
          break;
        case SDLK_BACKSPACE:
          current_input_type = InputType::backspace;
          break;
        }
      }
      else if( e.type == SDL_KEYUP )
      {
        current_input_type = InputType::none;
      }
      else if( e.type == SDL_QUIT )
      {
        current_input_type = InputType::escape;
      }
    }

    unique_ptr<InputEvent> event = make_unique<InputEvent>(
      current_input_type,
      previous_input_type
      );

    if( event -> key_pressed().has_value() )
    {
      event_queue.push(
        std::move( event )
        );  
    }
  }  
}

std::queue<std::unique_ptr<InputEvent>>& InputHandler::handle_input()
{ 
  return event_queue;
}
