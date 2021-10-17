#include "selected_highlight.hpp"

using std::make_shared;

using rebarhickey::SelectedHighlight;

SelectedHighlight::SelectedHighlight( int param_x,
                                      int param_y,
                                      int param_h,
                                      int param_w,
                                      std::shared_ptr<SDL_Texture> param_texture )
  : x( param_x ),
    y( param_y ),
    h( param_h ),
    w( param_w ),
    texture( param_texture )
{
  calculate_destination();
}

std::shared_ptr<SDL_Texture> SelectedHighlight::getTexture() const 
{
  return texture;
}

std::shared_ptr<SDL_Rect> SelectedHighlight::getDestination() const
{
  return destination;
}
  
std::shared_ptr<SDL_Rect> SelectedHighlight::getClip() const
{
  return clip;
}
  
void SelectedHighlight::set_clip( std::shared_ptr<SDL_Rect> param_clip )
{
  clip = param_clip;
}
  
void SelectedHighlight::set_destination( std::shared_ptr<SDL_Rect> param_destination )
{
  destination = param_destination;
}
  
int SelectedHighlight::get_x()
{
  return x;
}
  
int SelectedHighlight::get_y()
{
  return y;
}
  
int SelectedHighlight::get_h() const
{
  return h;
}
  
int SelectedHighlight::get_w() const
{
  return w;
}
  
void SelectedHighlight::set_x( int param_x )
{
  x = param_x;
  calculate_destination();
}
  
void SelectedHighlight::set_y( int param_y )
{
  y = param_y;
  calculate_destination();
}
  
void SelectedHighlight::calculate_destination()
{
  destination = make_shared<SDL_Rect>();
  destination -> x = x;
  destination -> y = y;
  destination -> h = h;
  destination -> w = w;
}

