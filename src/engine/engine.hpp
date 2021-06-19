#include "cleanup.hpp"
#include "hickey_component.hpp"
#include "input_event.hpp"
#include "input_handler.hpp"
#include "render_component.hpp"
#include "hickey_renderer.hpp"
#include <SDL.h>
#include <memory>

#ifndef JAREDALL_TETRIS_ENGINE
#define JAREDALL_TETRIS_ENGINE

namespace rebarhickey::engine
{
  class Engine
  {
  public:

    ~Engine();

    void initialize( int height, int width );

    template< typename T, typename = typename std::enable_if_t<
                            std::is_base_of<HickeyComponent, T>::value>>
    void advance( std::vector<std::unique_ptr<T>>& components )
    {
      if( should_render )
      {
        render_components( components );
      }

      input::InputEvent& event = process_input();

      update_components( event, components );
    }

    void quit();

    bool peek_has_updated();

    HickeyRenderer& get_renderer();

  private:

    template< typename T >
    void render_components( std::vector<std::unique_ptr<T>>& components )
    {
      renderer -> render( components );
  
      frame_count++;
      should_render = false;
      should_update = true;
    }

    template< typename T >
    void update_components( input::InputEvent& input_event,
                            std::vector<std::unique_ptr<T>>& components )
    {
      for( auto& component : components )
      {
        if( should_update )
        {
          component -> update();
        }
        if( component -> accepting_input() )
        {
          component -> update( input_event );
        }
      }
      has_updated = true;
      should_update = false;
    }

    input::InputEvent& process_input();

    void maintain_time();

    std::unique_ptr<input::InputHandler> input_handler;
    std::unique_ptr<HickeyRenderer> renderer;
    int current_scroll;
    bool should_render;
    bool should_update;
    bool has_updated;
    bool running;
    int frame_count;
  };
}

#endif
