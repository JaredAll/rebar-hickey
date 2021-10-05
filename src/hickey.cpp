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
using rebarhickey::engine::input::InputType;
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

  std::vector<std::vector<std::unique_ptr<GlyphNode>>> vector_of_nodes_2D;
  vector_of_nodes_2D.push_back( nodify( *gap_buffer ) );    

  int show_index = 0;
  while( true )
  {
    engine -> advance( vector_of_nodes_2D.at( show_index ) );

    std::optional<char> insertion = handle_input();
    if( insertion.has_value() )
    {
      vector_of_nodes_2D.clear();
      gap_buffer -> insert( insertion.value() );
      vector_of_nodes_2D.push_back( nodify( *gap_buffer ) );    
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

std::optional<char> Hickey::handle_input()
{
  std::optional<char> insertion {};
  std::optional<InputType> input_type_optional = engine -> process_input().key_pressed();

  if( input_type_optional.has_value() )
  {
    switch( input_type_optional.value() )
    {
    case InputType::alpha:
      insertion = std::optional<char> { 'a' };
      break;
    case InputType::bravo:
      insertion = std::optional<char> { 'b' };
      break;
    case InputType::charlie:
      insertion = std::optional<char> { 'c' };
      break;
    case InputType::delta:
      insertion = std::optional<char> { 'd' };
      break;
    case InputType::echo:
      insertion = std::optional<char> { 'e' };
      break;
    case InputType::foxtrot:
      insertion = std::optional<char> { 'f' };
      break;
    case InputType::golf:
      insertion = std::optional<char> { 'g' };
      break;
    case InputType::hotel:
      insertion = std::optional<char> { 'h' };
      break;
    case InputType::india:
      insertion = std::optional<char> { 'i' };
      break;
    case InputType::juliett:
      insertion = std::optional<char> { 'j' };
      break;
    case InputType::kilo:
      insertion = std::optional<char> { 'k' };
      break;
    case InputType::lima:
      insertion = std::optional<char> { 'l' };
      break;
    case InputType::mike:
      insertion = std::optional<char> { 'm' };
      break;
    case InputType::november:
      insertion = std::optional<char> { 'n' };
      break;
    case InputType::oscar:
      insertion = std::optional<char> { 'o' };
      break;
    case InputType::papa:
      insertion = std::optional<char> { 'p' };
      break;
    case InputType::quebec:
      insertion = std::optional<char> { 'q' };
      break;
    case InputType::romeo:
      insertion = std::optional<char> { 'r' };
      break;
    case InputType::sierra:
      insertion = std::optional<char> { 's' };
      break;
    case InputType::tango:
      insertion = std::optional<char> { 't' };
      break;
    case InputType::uniform:
      insertion = std::optional<char> { 'u' };
      break;
    case InputType::victor:
      insertion = std::optional<char> { 'v' };
      break;
    case InputType::whiskey:
      insertion = std::optional<char> { 'w' };
      break;
    case InputType::xray:
      insertion = std::optional<char> { 'x' };
      break;
    case InputType::yankee:
      insertion = std::optional<char> { 'y' };
      break;
    case InputType::zulu:
      insertion = std::optional<char> { 'z' };
      break;
    case InputType::enter:
      insertion = std::optional<char> { '\n' };
    default:
      break;
    }
  }

  return insertion;
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
