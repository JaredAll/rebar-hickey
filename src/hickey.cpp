#include "hickey.hpp"
#include "cleanup.hpp"
#include "engine.hpp"
#include "gap_buffer.hpp"
#include "glyph_alphabet.hpp"
#include "glyph_node.hpp"
#include "input_event.hpp"
#include <cmath>
#include <cstddef>
#include <fstream>
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
  engine -> initialize( 700, 700 );

  alphabet = std::make_unique<GlyphAlphabet>( engine -> get_renderer() );

}

int Hickey::run()
{
  std::unique_ptr<GapBuffer> gap_buffer = read( "/home/jared/rebar-hickey/resources/file.txt" );
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

std::unique_ptr<GapBuffer> Hickey::read( const std::string& path )
{
  char current_char;

  std::ifstream file_stream( path );
  std::unique_ptr<GapBuffer> buffer = std::make_unique<GapBuffer>();
  if( file_stream.is_open() )
  {
    while( file_stream.get( current_char ) )
    {
      buffer -> insert( current_char );
    }
  }

  file_stream.close();

  return buffer;
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
    else if( nodified_char == ' ' )
    {
      column++;
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
