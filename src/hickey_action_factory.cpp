#include "hickey_action_factory.hpp"
#include "buffer_action.hpp"
#include "buffer_action_factory.hpp"
#include "buffer_executor.hpp"
#include "gap_buffer.hpp"
#include "hickey.hpp"
#include "action_factory.hpp"
#include "io_action_factory.hpp"
#include <memory>

using rebarhickey::HickeyActionFactory;
using rebarhickey::HickeyAction;
using rebarhickey::Hickey;
using rebarhickey::engine::Engine;
using rebarhickey::text::BufferAction;
using rebarhickey::text::BufferActionFactory;
using rebarhickey::io::IoActionFactory;
using rebarhickey::text::BufferExecutor;
using rebarhickey::text::GapBuffer;
using std::make_unique;
using std::optional;
using std::unique_ptr;

HickeyActionFactory::HickeyActionFactory( Engine& param_engine )
  : event_queue( engine.process_input() ), engine( param_engine )
{
  action_factories.push_back( make_unique<BufferActionFactory>() );
  action_factories.push_back( make_unique<IoActionFactory>() );
}

optional<unique_ptr<HickeyAction>> HickeyActionFactory::next_action(Hickey& hickey)
{
  optional<unique_ptr<HickeyAction>> hickey_action_optional {};

  int factory_index = 0;
  while( !hickey_action_optional.has_value() && factory_index < action_factories.size() )
  {
    hickey_action_optional = action_factories.at(
      factory_index
      ) -> next_action( event_queue, hickey );

    factory_index++;
  }

  if( !event_queue.empty() )
  {
    engine::input::InputEvent& event = *event_queue.front();
    if( event.escape() )
    {
      engine.quit();
    }

    event_queue.pop();
  }

  return hickey_action_optional;
}
