#include "buffer_executor.hpp"

using rebarhickey::text::BufferExecutor;

BufferExecutor::BufferExecutor(
  GapBuffer& param_buffer,
  std::unique_ptr<BufferAction> param_buffer_action
  ) : buffer( param_buffer ), buffer_action( std::move( param_buffer_action ) )
{
}

void BufferExecutor::update()
{
  buffer_action -> update_buffer( buffer );
};
