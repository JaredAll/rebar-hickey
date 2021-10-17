#ifndef JAREDALL_GLYPH_ALPHABET
#define JAREDALL_GLYPH_ALPHABET

#include <memory>
#include <map>
#include "SDL_render.h"
#include "glyph.hpp"
#include "engine.hpp"

namespace rebarhickey::text
{

  class GlyphAlphabet
  {
  public:

    GlyphAlphabet( engine::HickeyRenderer& );

    std::unique_ptr<Glyph> get_char_as_glyph( char character, bool selected );

    int get_letter_h();
    int get_letter_w();

  private:

    std::shared_ptr<SDL_Texture> find_letter_texture( char character, bool selected );

    std::map<char, std::shared_ptr<SDL_Texture>> alphabet_map;

    std::map<char, std::shared_ptr<SDL_Texture>> selected_alphabet_map;

    int letter_h;
    int letter_w;

    inline const static std::string path = "/home/jared/rebar-hickey/resources/cour.ttf";

    inline const static std::string upper_case_alphabet_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    inline const static std::string number_chars = "0123456789";
    inline const static std::string lower_case_alphabet_chars = "abcdefghijklmnopqrstuvwxyz";
    inline const static std::string punctuation_chars = ",!.;<>\"";

    inline const static std::string alphabet_chars = upper_case_alphabet_chars +
      lower_case_alphabet_chars +
      number_chars +
      punctuation_chars;

  };

}

#endif
