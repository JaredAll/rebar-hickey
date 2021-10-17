#include "glyph.hpp"

using std::make_shared;

using rebarhickey::text::Glyph;

Glyph::Glyph( char param_character,
              int param_x,
              int param_y,
              int param_h,
              int param_w,
              std::shared_ptr<SDL_Texture> param_texture )
  : character( param_character ),
    x( param_x ),
    y( param_y ),
    h( param_h ),
    w( param_w ),
    texture( param_texture )
{
  calculate_destination();
}

std::shared_ptr<SDL_Texture> Glyph::getTexture() const 
{
  return texture;
}
  
std::shared_ptr<SDL_Rect> Glyph::getDestination() const
{
  return destination;
}
  
std::shared_ptr<SDL_Rect> Glyph::getClip() const
{
  return clip;
}
  
void Glyph::set_clip( std::shared_ptr<SDL_Rect> param_clip )
{
  clip = param_clip;
}
  
void Glyph::set_destination( std::shared_ptr<SDL_Rect> param_destination )
{
  destination = param_destination;
}

char Glyph::get_character()
{
  return character;
}

int Glyph::get_x()
{
  return x;
}
  
int Glyph::get_y()
{
  return y;
}
  
int Glyph::get_h() const
{
  return h;
}
  
int Glyph::get_w() const
{
  return w;
}
  
void Glyph::set_x( int param_x )
{
  x = param_x;
  calculate_destination();
}
  
void Glyph::set_y( int param_y )
{
  y = param_y;
  calculate_destination();
}
  
void Glyph::calculate_destination()
{
  destination = make_shared<SDL_Rect>();
  destination -> x = x;
  destination -> y = y;
  destination -> h = h;
  destination -> w = w;
}

