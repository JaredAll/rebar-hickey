#include "buffer_insert_action.hpp"
#include "gap_buffer.hpp"

using rebarhickey::text::BufferInsertAction;
using rebarhickey::text::GapBuffer;

BufferInsertAction::BufferInsertAction( char param_char ) :
  character_to_insert( param_char )
{
}

void BufferInsertAction::update_buffer( GapBuffer& buffer )
{
  buffer.insert( character_to_insert );
}
