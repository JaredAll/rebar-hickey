#ifndef BUFFER_EXECUTOR_H
#define BUFFER_EXECUTOR_H

#include "buffer_action.hpp"
#include "gap_buffer.hpp"
#include "hickey_action.hpp"

namespace rebarhickey::text
{
  
  class BufferExecutor : public HickeyAction
  {
  public:

    BufferExecutor( GapBuffer& buffer, std::unique_ptr<BufferAction> buffer_action );

    ~BufferExecutor() = default;

    void update() override;

  private:

    GapBuffer& buffer;

    std::unique_ptr<BufferAction> buffer_action;

  };
  
}

#endif
