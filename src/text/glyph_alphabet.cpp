#include "glyph_alphabet.hpp"
#include "SDL_render.h"
#include "cleanup.hpp"
#include "hickey_renderer.hpp"
#include <exception>
#include <stdexcept>

namespace rebarhickey::text
{

  GlyphAlphabet::GlyphAlphabet( const engine::HickeyRenderer& renderer )
  {

    if( TTF_Init() == -1 )
    {
      std::cout << "TTF_Init failed" << std::endl;
    }

    int point_size = 24;

    std::shared_ptr<TTF_Font> font {
      TTF_OpenFont( path.c_str(), point_size ),
      engine::utility::TTF_Font_Destroyer()
    };

    if( font == nullptr )
    {
      std::cout << "Error initializing font: " << TTF_GetError() << std::endl;
    }

    SDL_Color white { 255, 255, 255 };

    for( const char& character : alphabet_chars )
    {
      char letter_singleton[ 2 ] = { character, '\0' };

      alphabet_map.insert(
        std::make_pair(
          character,
          renderer.render_letter_texture( font.get(),
                                          letter_singleton,
                                          white )
          )
        );
    }

    SDL_QueryTexture( 
      find_letter_texture( 'a' ).get(), 
      NULL, 
      NULL, 
      &letter_h, 
      &letter_w );
  }

  std::shared_ptr<SDL_Texture> GlyphAlphabet::find_letter_texture( char character )
  {
    std::shared_ptr<SDL_Texture> texture {};

    std::map<char, std::shared_ptr<SDL_Texture>>::iterator iterator;
    iterator = alphabet_map.find( character );

    if( iterator != alphabet_map.end() )
    {
      texture = (*iterator).second;
    }
    else
    {
      throw std::invalid_argument( &"unable to find char: " [ character] );
    }

    return texture;
  }

  std::unique_ptr<Glyph> GlyphAlphabet::get_char_as_glyph( char character )
  {
    return std::make_unique<Glyph>(
      0,
      0,
      letter_w,
      letter_h,
      find_letter_texture( character ) );
  }

  int GlyphAlphabet::get_letter_h()
  {
    return letter_h;
  }
  
  int GlyphAlphabet::get_letter_w()
  {
    return letter_w;
  }
}
