#include "buffer_action_factory.hpp"
#include "buffer_executor.hpp"
#include "input_event.hpp"
#include "buffer_insert_action.hpp"
#include "buffer_remove_action.hpp"
#include "buffer_cursor_action.hpp"
#include "hickey.hpp"
#include <memory>
#include <optional>
#include <queue>

using rebarhickey::text::BufferAction;
using rebarhickey::HickeyAction;
using rebarhickey::text::BufferInsertAction;
using rebarhickey::text::BufferRemoveAction;
using rebarhickey::text::BufferCursorAction;
using rebarhickey::text::BufferActionFactory;
using rebarhickey::engine::input::InputEvent;
using rebarhickey::engine::input::InputType;
using rebarhickey::engine::Engine;

using std::optional;
using std::queue;
using std::unique_ptr;
using std::pair;

BufferActionFactory::BufferActionFactory()
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
  insertion_types[ InputType::period ] = '.';

  removal_types[ InputType::backspace ] = 1;

  cursor_types[ InputType::up ] = { -1, 0 };
  cursor_types[ InputType::down ] = { 1, 0 };
  cursor_types[ InputType::left ] = { 0, -1 };
  cursor_types[ InputType::right ] = { 0, 1 };
}

optional<unique_ptr<HickeyAction>> BufferActionFactory::next_action(
  const queue<unique_ptr<engine::input::InputEvent>>& event_queue,
  const Hickey& hickey
  ) {
  optional<char> input_char_optional {};
  optional<int> removal_int_optional {};
  optional<pair<int, int>> cursor_pair_optional {};

  if( !event_queue.empty() )
  {
    const std::unique_ptr<InputEvent>& input_event = event_queue.front();
    optional<InputType> input_type_optional = input_event -> key_pressed();

    if( input_type_optional.has_value() && !input_event -> is_control_down() )
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

      for( const auto& cursor_pair : cursor_types )
      {
        if( input_type_optional.value() == cursor_pair.first )
        {
          cursor_pair_optional = { cursor_pair.second };
        }
      }
    }
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
  else if( cursor_pair_optional.has_value() )
  {
    std::pair<int, int> cursor_pair = cursor_pair_optional.value();
    action = {
      std::make_unique<BufferCursorAction> (
        cursor_pair.first,
        cursor_pair.second
        )
    };
  }
  
  optional<unique_ptr<HickeyAction>> hickey_action_optional {};
  
  if( action.has_value() )
  {
    hickey_action_optional = {
      std::make_unique<text::BufferExecutor>(
        hickey.get_current_buffer(),
        std::move( action.value() )
        )
    };
  }

  return hickey_action_optional;
}
