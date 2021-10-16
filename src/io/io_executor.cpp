#include "io_executor.hpp"
#include "hickey.hpp"

using rebarhickey::io::IoExecutor;

IoExecutor::IoExecutor( const Hickey& param_hickey )
  : hickey( param_hickey ) {}

void IoExecutor::update()
{
  const GapBuffer& buffer = hickey.get_current_buffer();
  hickey.write( buffer.get_path(), buffer );
  std::cout << "wrote " << buffer.get_path() << std::endl;
}
