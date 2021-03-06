#ifndef REBARHICKEY_GLYPH_H
#define REBARHICKEY_GLYPH_H

#include "SDL_render.h"
#include "render_component.hpp"

using rebarhickey::engine::RenderComponent;

namespace rebarhickey::text
{

  class Glyph : public RenderComponent
  {
  public:

    Glyph( char character, int x, int y, int h, int w, std::shared_ptr<SDL_Texture> texture );

    std::shared_ptr<SDL_Texture> getTexture() const override;
  
    std::shared_ptr<SDL_Rect> getDestination() const override;
  
    std::shared_ptr<SDL_Rect> getClip() const override;
  
    void set_clip( std::shared_ptr<SDL_Rect> clip ) override;
  
    void set_destination( std::shared_ptr<SDL_Rect> destination ) override;

    char get_character();

    int get_x();
  
    int get_y();
  
    int get_h() const override;
  
    int get_w() const override;
  
    void set_x( int x );
  
    void set_y( int y );
  
    void calculate_destination();

  private:

    char character;

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
