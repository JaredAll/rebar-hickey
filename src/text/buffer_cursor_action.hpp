#ifndef BUFFER_CURSOR_ACTION_H
#define BUFFER_CURSOR_ACTION_H

#include "buffer_action.hpp"
#include "gap_buffer.hpp"

namespace rebarhickey::text
{
  
  class BufferCursorAction : public BufferAction
  {
  public:

    BufferCursorAction( int row_change, int column_change );
    
    ~BufferCursorAction() override = default;

    virtual void update_buffer( GapBuffer& buffer ) override;

  private:

    int row_change;
    int column_change;

  };
  
}

#endif
