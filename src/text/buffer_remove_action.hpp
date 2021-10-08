#ifndef BUFFER_REMOVE_ACTION_H
#define BUFFER_REMOVE_ACTION_H

#include "buffer_action.hpp"
#include "gap_buffer.hpp"

namespace rebarhickey::text
{
  
  class BufferRemoveAction : public BufferAction
  {
  public:

    BufferRemoveAction( int );
    
    ~BufferRemoveAction() override = default;

    virtual void update_buffer( GapBuffer& buffer ) override;

  private:

    int num_to_remove;

  };
  
}

#endif
