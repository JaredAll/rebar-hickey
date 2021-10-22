#include "buffer_cursor_action.hpp"

using rebarhickey::text::BufferCursorAction;

BufferCursorAction::BufferCursorAction( int param_row_change, int param_column_change )
  : row_change( param_row_change ), column_change( param_column_change )
{
}
    
void BufferCursorAction::update_buffer( GapBuffer& buffer )
{
  if( row_change != 0 )
  {
    buffer.update_cursor_row( row_change );
  }
  else if( column_change != 0 )
  {
    buffer.update_cursor_column( column_change );
  }
}
