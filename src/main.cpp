#include "cleanup.hpp"
#include "engine.hpp"
#include "text/glyph_alphabet.hpp"
#include "text/glyph_node.hpp"
#include <cmath>
#include <memory>

using rebarhickey::engine::Engine;
using rebarhickey::engine::utility::TTF_Font_Destroyer;
using rebarhickey::text::GlyphAlphabet;
using rebarhickey::text::Glyph;
using rebarhickey::text::GlyphNode;

int main( int argc, char* argv[] )
{
  std::unique_ptr<Engine> engine = std::make_unique<Engine>();
  engine -> initialize( 500, 500 );

  if( TTF_Init() == -1 )
  {
    std::cout << "TTF_Init failed" << std::endl;
  }

  std::string path = "/home/jared/rebar-hickey/resources/OpenSans-Bold.ttf";

  std::shared_ptr<TTF_Font> font {
    TTF_OpenFont( path.c_str(), 12 ),
    TTF_Font_Destroyer()
  };

  if( font == nullptr )
  {
    std::cout << "Error initializing font: " << TTF_GetError() << std::endl;
  }
  
  std::string alphabet_chars = "0123456789TETRIStetris";
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
  
  std::vector<std::unique_ptr<Glyph>> glyphs;
  glyphs.push_back( std::move( alphabet -> get_char_as_glyph( 'T' ) ) );

  std::vector<std::unique_ptr<GlyphNode>> glyph_nodes;
  glyph_nodes.push_back( std::move( std::make_unique<GlyphNode>( glyphs ) ) );

  while( true )
  {
    engine -> advance( glyph_nodes );
  }

  return 0;
}
