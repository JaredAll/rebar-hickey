#ifndef REBARHICKEY_GLYPH_DATA_H
#define REBARHICKEY_GLYPH_DATA_H

#include "SDL_render.h"
#include "render_component.hpp"

namespace rebarhickey::text
{

  class GlyphData
  {
  public:

    GlyphData( char character, int row, int column, bool selected );

    char get_character();

    int get_row();

    int get_column();

    bool is_selected();

  private:

    const char character;
    const int row;
    const int column;
    const bool selected;

  };

}

#endif
