#include "hickey.hpp"
#include "cleanup.hpp"
#include "engine.hpp"
#include "gap_buffer.hpp"
#include "glyph_alphabet.hpp"
#include "glyph_node.hpp"
#include "input_event.hpp"
#include <cmath>
#include <cstddef>
#include <memory>

using rebarhickey::Hickey;
using rebarhickey::engine::utility::TTF_Font_Destroyer;
using rebarhickey::text::GlyphAlphabet;
using rebarhickey::text::Glyph;
using rebarhickey::text::GlyphNode;
using rebarhickey::engine::input::InputEvent;

using std::vector;

Hickey::Hickey()
{
  engine = std::make_unique<Engine>();
  engine -> initialize( 500, 500 );

  if( TTF_Init() == -1 )
  {
    std::cout << "TTF_Init failed" << std::endl;
  }

  std::string path = "/home/jared/rebar-hickey/resources/OpenSans-Bold.ttf";

  std::shared_ptr<TTF_Font> font {
    TTF_OpenFont( path.c_str(), 24 ),
    TTF_Font_Destroyer()
  };

  if( font == nullptr )
  {
    std::cout << "Error initializing font: " << TTF_GetError() << std::endl;
  }
  
  std::string alphabet_chars = "0123456789TETRISYNtetrisJA";
  SDL_Color white { 255, 255, 255 };

  std::map<char, std::shared_ptr<SDL_Texture>> texture_map;
  for( const char& character : alphabet_chars )
  {
    char letter_singleton[ 2 ] = { character, '\0' };

    texture_map.insert(
      std::make_pair(
        character,
        engine -> get_renderer().render_letter_texture( font.get(),
                                                        letter_singleton,
                                                        white )));
  }

  alphabet = std::make_unique<GlyphAlphabet>( texture_map );

}

int Hickey::run()
{
  std::unique_ptr<GapBuffer> gap_buffer = std::make_unique<GapBuffer>();
  gap_buffer -> insert( 'J' );
  gap_buffer -> insert( 'A' );
  gap_buffer -> insert( '\n' );
  gap_buffer -> insert( 'A' );
  gap_buffer -> insert( 'A' );

  std::unique_ptr<GapBuffer> gap_buffer_N = std::make_unique<GapBuffer>();
  gap_buffer_N -> insert( 'N' );

  std::vector<std::vector<std::unique_ptr<GlyphNode>>> vector_of_nodes_2D;
  vector_of_nodes_2D.push_back( nodify( *gap_buffer ) );
  vector_of_nodes_2D.push_back( nodify( *gap_buffer_N ) );

  int show_index = 0;
  while( true )
  {
    engine -> advance( vector_of_nodes_2D.at( show_index ) );
    
    if( engine -> process_input().up_up() )
    {
      if( show_index == 0 )
      {
        show_index = 1;
      }
      else
      {
        show_index = 0;
      }
    }
  }

  return 0;
}

vector<std::unique_ptr<GlyphNode>> Hickey::nodify( const GapBuffer& gap_buffer )
{
  vector<char> text = gap_buffer.get_text();
  int text_length = text.size();
  vector<std::unique_ptr<GlyphNode>> glyph_nodes {};

  int character_count = 0;
  int row = 0;
  int column = 0;

  while( character_count < text_length )
  {
    char nodified_char = text.at( character_count );
    if( nodified_char == '\n' )
    {
      row++;
      column = 0;
    }
    else
    {
      std::unique_ptr<GlyphNode> glyph_node = std::make_unique<GlyphNode>(
        row,
        column,
        std::move( alphabet -> get_char_as_glyph( nodified_char ) )
        );

      glyph_nodes.push_back( std::move( glyph_node ) );
      column++;
    }
    character_count++;
  }

  return glyph_nodes;
}
