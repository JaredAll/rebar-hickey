#ifndef BUFFER_INSERT_ACTION_H
#define BUFFER_INSERT_ACTION_H

#include "buffer_action.hpp"
#include "gap_buffer.hpp"

namespace rebarhickey::text
{
  
  class BufferInsertAction : public BufferAction
  {
  public:

    BufferInsertAction( char );
    
    ~BufferInsertAction() override = default;

    virtual void update_buffer( GapBuffer& buffer ) override;

  private:

    char character_to_insert;

  };
  
}

#endif
