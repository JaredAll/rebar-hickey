#ifndef BUFFER_ACTION_H
#define BUFFER_ACTION_H

#include "gap_buffer.hpp"
#include "hickey_action.hpp"

namespace rebarhickey::text
{
  
  class BufferAction
  {
  public:

    virtual void update_buffer( GapBuffer& buffer ) = 0;

    virtual ~BufferAction() = default;
    
  };
  
}

#endif
