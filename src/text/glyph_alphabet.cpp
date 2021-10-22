#include "glyph_alphabet.hpp"
#include "SDL_render.h"
#include "cleanup.hpp"
#include "hickey_renderer.hpp"
#include <exception>
#include <stdexcept>
#include <utility>

namespace rebarhickey::text
{

  GlyphAlphabet::GlyphAlphabet( engine::HickeyRenderer& renderer )
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
    SDL_Color blue { 100, 100, 255 };

    std::string black_block_path = "/home/jared/rebar-hickey/resources/black_block.png";

    for( auto& character : whitespace_chars )
    {
      std::pair<char, std::shared_ptr<SDL_Texture>> whitespace_pair =
      std::make_pair(
        character,
        renderer.create_texture( black_block_path )
        );

      alphabet_map.insert( whitespace_pair );
      selected_alphabet_map.insert( whitespace_pair );
    }

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

      selected_alphabet_map.insert(
        std::make_pair(
          character,
          renderer.render_letter_texture( font.get(),
                                          letter_singleton,
                                          blue )
          )
        );
    }

    SDL_QueryTexture( 
      find_letter_texture( 'a' , false ).get(), 
      NULL, 
      NULL, 
      &letter_h, 
      &letter_w );
  }

  std::shared_ptr<SDL_Texture> GlyphAlphabet::find_letter_texture( char character, bool selected )
  {
    std::shared_ptr<SDL_Texture> texture {};

    std::map<char, std::shared_ptr<SDL_Texture>> texture_map = alphabet_map;
    if( selected )
    {
      texture_map = selected_alphabet_map;
    }

    std::map<char, std::shared_ptr<SDL_Texture>>::iterator iterator;
    iterator = texture_map.find( character );

    if( iterator != texture_map.end() )
    {
      texture = (*iterator).second;
    }
    else
    {
      throw std::invalid_argument( &"unable to find char: " [ character] );
    }

    return texture;
  }

  std::unique_ptr<Glyph> GlyphAlphabet::get_char_as_glyph( char character, bool selected )
  {
    return std::make_unique<Glyph>(
      character,
      0,
      0,
      letter_w,
      letter_h,
      find_letter_texture( character, selected )
      );
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
