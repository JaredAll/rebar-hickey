#include "glyph_data.hpp"

using rebarhickey::text::GlyphData;

GlyphData::GlyphData(
  char param_character,
  int param_row,
  int param_column,
  bool param_selected
  ) : character( param_character ),
      row( param_row ),
      column( param_column ),
      selected( param_selected )
{}

char GlyphData::get_character()
{
  return character;
}

int GlyphData::get_row()
{
  return row;
}

int GlyphData::get_column()
{
  return column;
}

bool GlyphData::is_selected()
{
  return selected;
}
