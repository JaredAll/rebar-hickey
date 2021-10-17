#include "hickey.hpp"
#include "cleanup.hpp"
#include "editor_node.hpp"
#include "engine.hpp"
#include "gap_buffer.hpp"
#include "glyph_alphabet.hpp"
#include "glyph_node.hpp"
#include "hickey_action_factory.hpp"
#include "hickey_highlights.hpp"
#include "hickey_renderer.hpp"
#include "input_event.hpp"
#include "selected_editor_node.hpp"
#include <cmath>
#include <cstddef>
#include <fstream>
#include <memory>

using rebarhickey::Hickey;
using rebarhickey::engine::utility::TTF_Font_Destroyer;
using rebarhickey::text::GlyphAlphabet;
using rebarhickey::text::Glyph;
using rebarhickey::text::GlyphNode;
using rebarhickey::text::BufferAction;
using rebarhickey::text::Cursor;
using rebarhickey::engine::input::InputEvent;
using rebarhickey::engine::input::InputType;
using rebarhickey::EditorNode;

using std::vector;
using std::unique_ptr;
using std::optional;

Hickey::Hickey()
{
  engine = std::make_unique<Engine>();
  engine -> initialize( 700, 700 );

  engine::HickeyRenderer& renderer = engine -> get_renderer();

  alphabet = std::make_unique<GlyphAlphabet>( renderer );
  highlights = std::make_unique<HickeyHighlights>( renderer );  
  hickey_action_factory = std::make_unique<HickeyActionFactory>( *engine );
}

int Hickey::run()
{
  std::string path = "/home/jared/rebar-hickey/resources/file.txt";
  gap_buffer = read( path );

  vector<vector<unique_ptr<EditorNode>>> vector_of_nodes_2D;
  vector_of_nodes_2D.push_back( nodify( *gap_buffer ) );    

  int show_index = 0;
  while( true )
  {
    engine -> advance( vector_of_nodes_2D.at( show_index ) );

    vector_of_nodes_2D.clear();
    optional<unique_ptr<HickeyAction>> action = hickey_action_factory -> next_action( *this );
    if( action.has_value() )
    {
      action.value() -> update();
    }
    vector_of_nodes_2D.push_back( nodify( *gap_buffer ) );
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

  buffer -> set_path( path );

  return buffer;
}

void Hickey::write( const std::string& path, const GapBuffer& buffer ) const
{
  vector<char> text = buffer.get_text();

  std::ofstream file_stream( path );
  int text_size = text.size();

  for( int i = 0; i < text.size(); i++ )
  {
    file_stream.write( &text.at( i ), 1 );
  }

  file_stream.close();
}

vector<std::unique_ptr<EditorNode>> Hickey::nodify( GapBuffer& gap_buffer )
{
  vector<char> text = gap_buffer.get_text();
  int text_length = text.size();
  vector<std::unique_ptr<EditorNode>> glyph_nodes {};

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
      bool selected = false;
      Cursor& cursor = gap_buffer.get_cursor();
      if( cursor.get_row() == row && cursor.get_column() == column )
      {
        selected = true;
      }

      std::unique_ptr<EditorNode> glyph_node = std::make_unique<GlyphNode>(
        row,
        column,
        std::move( alphabet -> get_char_as_glyph( nodified_char, selected ) )
        );

      if( selected )
      {
        glyph_node = std::make_unique<SelectedEditorNode>(
          std::move( glyph_node ),
          highlights -> get_highlight()
          );
      }

      glyph_nodes.push_back( std::move( glyph_node ) );
      column++;
    }
    character_count++;
  }

  return glyph_nodes;
}

GapBuffer& Hickey::get_current_buffer() const
{
  return *gap_buffer;
}
