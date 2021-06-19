#ifndef JAREDALL_TETRIS_GLYPH
#define JAREDALL_TETRIS_GLYPH

#include "SDL_render.h"
#include "render_component.hpp"

using rebarhickey::engine::RenderComponent;

namespace rebarhickey::text
{

  class Glyph : public RenderComponent
  {
  public:

    Glyph( int x, int y, int h, int w, std::shared_ptr<SDL_Texture> texture );

    std::shared_ptr<SDL_Texture> getTexture() const override;
  
    std::shared_ptr<SDL_Rect> getDestination() const override;
  
    std::shared_ptr<SDL_Rect> getClip() const override;
  
    void set_clip( std::shared_ptr<SDL_Rect> clip ) override;
  
    void set_destination( std::shared_ptr<SDL_Rect> destination ) override;
  
    int get_x();
  
    int get_y();
  
    int get_h();
  
    int get_w();
  
    void set_x( int x );
  
    void set_y( int y );
  
    void calculate_destination();

  private:
  
    int x;
    int y;
    int h;
    int w;

    std::shared_ptr<SDL_Texture> texture;
    std::shared_ptr<SDL_Rect> destination;
    std::shared_ptr<SDL_Rect> clip;

  };

}

#endif
