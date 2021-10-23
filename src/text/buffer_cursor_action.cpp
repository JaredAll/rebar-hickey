#include "buffer_cursor_action.hpp"

using rebarhickey::text::BufferCursorAction;

BufferCursorAction::BufferCursorAction( std::function<void( GapBuffer& )> param_buffer_consumer )
  : buffer_consumer( param_buffer_consumer )
{
}

void BufferCursorAction::update_buffer( GapBuffer& buffer )
{
  buffer_consumer( buffer );
}
