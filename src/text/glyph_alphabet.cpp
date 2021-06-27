#include "glyph_alphabet.hpp"
#include <exception>
#include <stdexcept>

namespace rebarhickey::text
{

  GlyphAlphabet::GlyphAlphabet( std::map<char, std::shared_ptr<SDL_Texture>> param_alphabet_map )
    : alphabet_map( param_alphabet_map )
  {
    letter_h = 25;
    letter_w = 17;
  }

  std::unique_ptr<Glyph> GlyphAlphabet::get_char_as_glyph( char character )
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

    return std::make_unique<Glyph>(
      0,
      0,
      letter_h,
      letter_w,
      texture );
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
