#include "hickey.hpp"
#include "cleanup.hpp"
#include "engine.hpp"
#include "glyph_alphabet.hpp"
#include "glyph_node.hpp"
#include "input_event.hpp"
#include <cmath>

using rebarhickey::Hickey;
using rebarhickey::engine::utility::TTF_Font_Destroyer;
using rebarhickey::text::GlyphAlphabet;
using rebarhickey::text::Glyph;
using rebarhickey::text::GlyphNode;
using rebarhickey::engine::input::InputEvent;

Hickey::Hickey()
{
  engine = std::make_unique<Engine>();
  engine -> initialize( 500, 500 );
}

int Hickey::run()
{
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

  std::unique_ptr<GlyphAlphabet> alphabet = std::make_unique<GlyphAlphabet>( texture_map );
  
  std::unique_ptr<GlyphNode> j_node = std::make_unique<GlyphNode>(
    0,
    0,
    std::move( alphabet -> get_char_as_glyph( 'J' ) )
    );

  std::unique_ptr<GlyphNode> a_node = std::make_unique<GlyphNode>(
    0,
    1,
    std::move( alphabet -> get_char_as_glyph( 'A' ) )
    );

  std::vector<std::unique_ptr<GlyphNode>> glyph_nodes_y;
  glyph_nodes_y.push_back( std::move( j_node ) );
  glyph_nodes_y.push_back( std::move( a_node ) );

  std::unique_ptr<GlyphNode> n_node = std::make_unique<GlyphNode>(
    1,
    1,
    std::move( alphabet -> get_char_as_glyph( 'N' ) )
    );

  std::vector<std::unique_ptr<GlyphNode>> glyph_nodes_n;
  glyph_nodes_n.push_back( std::move( n_node ) );

  std::vector<std::vector<std::unique_ptr<GlyphNode>>> vector_of_nodes_2D;
  vector_of_nodes_2D.push_back( std::move( glyph_nodes_y ) );
  vector_of_nodes_2D.push_back( std::move( glyph_nodes_n ) );

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
