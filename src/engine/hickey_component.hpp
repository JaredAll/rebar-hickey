#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

#include "render_component.hpp"
#include <vector>
#include <iostream>
#include "input_event.hpp"

namespace rebarhickey::engine
{

  class HickeyRenderer;

  class HickeyComponent
  {
  public:

    virtual void update() = 0;

    virtual void update( input::InputEvent& event ) = 0;

    virtual bool accepting_input() = 0;

    virtual int get_height() = 0;

    virtual int get_width() = 0;

    virtual ~HickeyComponent() = default;

    virtual void accept_renderer( HickeyRenderer& renderer ) = 0;

  protected:

    HickeyComponent()
    {
    }
  
  };

}

#endif
