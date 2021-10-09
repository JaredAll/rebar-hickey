#include "buffer_cursor_action.hpp"

using rebarhickey::text::BufferCursorAction;

BufferCursorAction::BufferCursorAction( int param_row_change, int param_column_change )
  : row_change( param_row_change ), column_change( param_column_change )
{
}
    
void BufferCursorAction::update_buffer( GapBuffer& buffer )
{
  Cursor& cursor = buffer.get_cursor();
  cursor.set_row( cursor.get_row() + row_change );
  cursor.set_column( cursor.get_column() + column_change );
}
