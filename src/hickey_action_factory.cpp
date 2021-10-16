#include "hickey_action_factory.hpp"
#include "buffer_action.hpp"
#include "buffer_action_factory.hpp"
#include "buffer_executor.hpp"
#include "gap_buffer.hpp"
#include "hickey.hpp"
#include <memory>

using rebarhickey::HickeyActionFactory;
using rebarhickey::HickeyAction;
using rebarhickey::Hickey;
using rebarhickey::engine::Engine;
using rebarhickey::text::BufferAction;
using rebarhickey::text::BufferExecutor;
using rebarhickey::text::GapBuffer;
using std::make_unique;
using std::optional;
using std::unique_ptr;

HickeyActionFactory::HickeyActionFactory( Engine& engine )
{
  buffer_factory = make_unique<BufferActionFactory>( engine );
}

optional<unique_ptr<HickeyAction>> HickeyActionFactory::next_action(Hickey& hickey)
{
  optional<unique_ptr<HickeyAction>> hickey_action_optional {};

  optional<unique_ptr<BufferAction>> buffer_action_optional = buffer_factory -> next_action();

  if( buffer_action_optional.has_value() )
  {
    hickey_action_optional = {
      make_unique<text::BufferExecutor>(
        hickey.get_current_buffer(),
        std::move( buffer_action_optional.value() )
        )
    };
  }

  return hickey_action_optional;
}
