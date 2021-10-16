#ifndef IO_EXECUTOR_H
#define IO_EXECUTOR_H

#include "action_factory.hpp"
#include "hickey_action.hpp"

namespace rebarhickey::io
{
  
  class IoExecutor : public HickeyAction
  {
  public:

    IoExecutor( const Hickey& hickey );

    ~IoExecutor() = default;

    void update() override;

  private:

    const Hickey& hickey;

  };
  
}

#endif
