#ifndef BUFFER_CURSOR_ACTION_H
#define BUFFER_CURSOR_ACTION_H

#include "buffer_action.hpp"
#include "gap_buffer.hpp"
#include <functional>

namespace rebarhickey::text
{
  
  class BufferCursorAction : public BufferAction
  {
  public:

    BufferCursorAction( std::function<void( GapBuffer& )> );
    
    ~BufferCursorAction() override = default;

    virtual void update_buffer( GapBuffer& buffer ) override;

  private:

    std::function<void( GapBuffer& )> buffer_consumer;

  };
  
}

#endif
