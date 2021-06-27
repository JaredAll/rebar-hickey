#ifndef JAREDALL_GLYPH_ALPHABET
#define JAREDALL_GLYPH_ALPHABET

#include <memory>
#include <map>
#include "SDL_render.h"
#include "glyph.hpp"

namespace rebarhickey::text
{

  class GlyphAlphabet
  {
  public:

    GlyphAlphabet( std::map<char, std::shared_ptr<SDL_Texture>> alphabet_map );

    std::unique_ptr<Glyph> get_char_as_glyph( char character );

    int get_letter_h();
    int get_letter_w();

  private:

    std::map<char, std::shared_ptr<SDL_Texture>> alphabet_map;

    int letter_h;
    int letter_w;

  };

}

#endif
