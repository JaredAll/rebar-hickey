#include "hickey_renderer.hpp"
#include "SDL_render.h"
#include "easy_sdl.hpp"
#include "cleanup.hpp"
#include "render_component.hpp"

using std::unique_ptr;
using std::shared_ptr;
using std::string;
using std::cout;
using std::endl;
using rebarhickey::engine::HickeyRenderer;
using rebarhickey::engine::utility::SDL_Renderer_Destroyer;
using rebarhickey::engine::utility::SDL_Surface_Destroyer;
using rebarhickey::engine::utility::SDL_Texture_Destroyer;
using rebarhickey::engine::utility::SDL_Window_Destroyer;

HickeyRenderer::HickeyRenderer( unique_ptr<SDL_Window, SDL_Window_Destroyer> win )
{
  unique_ptr<SDL_Renderer, SDL_Renderer_Destroyer> ren {
    SDL_CreateRenderer(win.get(), -1,
                       SDL_RENDERER_ACCELERATED
                       | SDL_RENDERER_PRESENTVSYNC) };
  if (!ren)
  {
    cout << "CreateRenderer failed" << endl;
    SDL_Quit();
  }
  renderer = move( ren );
  window = move( win );
}

shared_ptr<SDL_Texture> HickeyRenderer::create_texture( string image_path )
{
  shared_ptr<SDL_Texture> texture {};

  std::map<string, shared_ptr<SDL_Texture>>::iterator iterator;
  iterator = textures.find( image_path );
  if( iterator != textures.end() )
  {
    texture = (*iterator).second;
  }
  else
  {
    texture = {
      utility::loadTexture( image_path, renderer.get() ),
      SDL_Texture_Destroyer()
    };
    textures.insert( make_pair( image_path, texture ) );
  }
  
  return texture;
}

shared_ptr<SDL_Texture> HickeyRenderer::render_letter_texture( TTF_Font* font,
                                                             char letter_singleton[],
                                                             SDL_Color color ) const
{
  shared_ptr<SDL_Surface> letter_surface {
    TTF_RenderText_Solid( font, letter_singleton, color ),
    SDL_Surface_Destroyer()
  };
  
  shared_ptr<SDL_Texture> letter_texture {
    SDL_CreateTextureFromSurface( renderer.get(), letter_surface.get() ),
    SDL_Texture_Destroyer()
  };
  
  return letter_texture;
}
