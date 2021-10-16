#ifndef HICKEY_ACTION_H
#define HICKEY_ACTION_H

namespace rebarhickey
{
  
  class HickeyAction
  {
  public:

    virtual void update() = 0;

    virtual ~HickeyAction() = default;
    
  };
  
}

#endif
