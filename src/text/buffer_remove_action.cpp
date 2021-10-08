#include "buffer_remove_action.hpp"
#include "gap_buffer.hpp"
#include <iostream>

using rebarhickey::text::BufferRemoveAction;
using rebarhickey::text::GapBuffer;

BufferRemoveAction::BufferRemoveAction( int param_num_to_remove ) :
  num_to_remove( param_num_to_remove )
{
}

void BufferRemoveAction::update_buffer( GapBuffer& buffer )
{
  buffer.remove( num_to_remove );
}
