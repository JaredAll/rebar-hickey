#include "buffer_action_factory.hpp"
#include "input_event.hpp"
#include "buffer_insert_action.hpp"
#include "buffer_remove_action.hpp"
#include <queue>

using rebarhickey::text::BufferAction;
using rebarhickey::text::BufferInsertAction;
using rebarhickey::text::BufferRemoveAction;
using rebarhickey::BufferActionFactory;
using rebarhickey::engine::input::InputEvent;
using rebarhickey::engine::input::InputType;
using rebarhickey::engine::Engine;

BufferActionFactory::BufferActionFactory( Engine& param_engine ) : engine( param_engine )
{  
  insertion_types[ InputType::alpha ]  = 'a';
  insertion_types[ InputType::bravo ]  = 'b';
  insertion_types[ InputType::charlie ]  = 'c';
  insertion_types[ InputType::delta ]  = 'd';
  insertion_types[ InputType::echo ]  = 'e';
  insertion_types[ InputType::foxtrot ]  = 'f';
  insertion_types[ InputType::golf ]  = 'g';
  insertion_types[ InputType::hotel ]  = 'h';
  insertion_types[ InputType::india ]  = 'i';
  insertion_types[ InputType::juliett ]  = 'j';
  insertion_types[ InputType::kilo ]  = 'k';
  insertion_types[ InputType::lima ]  = 'l';
  insertion_types[ InputType::mike ]  = 'm';
  insertion_types[ InputType::november ]  = 'n';
  insertion_types[ InputType::oscar ]  = 'o';
  insertion_types[ InputType::papa ]  = 'p';
  insertion_types[ InputType::quebec ]  = 'q';
  insertion_types[ InputType::romeo ]  = 'r';
  insertion_types[ InputType::sierra ]  = 's';
  insertion_types[ InputType::tango ]  = 't';
  insertion_types[ InputType::uniform ]  = 'u';
  insertion_types[ InputType::victor ]  = 'v';
  insertion_types[ InputType::whiskey ]  = 'w';
  insertion_types[ InputType::xray ]  = 'x';
  insertion_types[ InputType::yankee ]  = 'y';
  insertion_types[ InputType::zulu ]  = 'z';
  insertion_types[ InputType::space ]  = ' ';
  insertion_types[ InputType::enter ]  = '\n';

  removal_types[ InputType::backspace ] = 1;
}

std::optional<std::unique_ptr<BufferAction>> BufferActionFactory::next_action()
{
  std::optional<char> input_char_optional {};
  std::optional<int> removal_int_optional {};
  std::queue<std::unique_ptr<InputEvent>>& event_queue = engine.process_input();

  if( !event_queue.empty() )
  {
    std::optional<InputType> input_type_optional = event_queue.front() -> key_pressed();

    if( input_type_optional.has_value() )
    {
      for( const auto& insertion_pair : insertion_types )
      {
        if( input_type_optional.value() == insertion_pair.first )
        {
          input_char_optional = { insertion_pair.second };
        }
      }

      for( const auto& removal_pair : removal_types )
      {
        if( input_type_optional.value() == removal_pair.first )
        {
          removal_int_optional = { removal_pair.second };
        }
      }
    }
    event_queue.pop();
  }

  std::optional<std::unique_ptr<BufferAction>> action {};
  if( input_char_optional.has_value() )
  {
    action = { std::make_unique<BufferInsertAction> ( input_char_optional.value() ) };
  }
  else if( removal_int_optional.has_value() )
  {    
    action = { std::make_unique<BufferRemoveAction> ( removal_int_optional.value() ) };
  }

  return action;
}
