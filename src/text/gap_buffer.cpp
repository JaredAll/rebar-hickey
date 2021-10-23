#include "gap_buffer.hpp"
#include "glyph_data.hpp"
#include <algorithm>
#include <memory>
#include <string>

using rebarhickey::text::GapBuffer;
using rebarhickey::text::GlyphData;
using rebarhickey::text::Cursor;
using std::vector;

GapBuffer::GapBuffer()
{
  cursor = std::make_unique<Cursor>( 0, 0 );
}

void GapBuffer::insert( char character )
{
  int cursor_index = calculate_cursor_index();
  int gap_index = text_before_gap.size();

  if( cursor_index != gap_index )
  {
    shuffle_gap( cursor_index, gap_index );
  }

  update_cursor_on_insert( character );
  text_before_gap.push_back( character );
  sync_text();
}

void GapBuffer::remove( int num_to_remove )
{
  int cursor_index = calculate_cursor_index();
  int gap_index = text_before_gap.size();

  if( cursor_index != gap_index )
  {
    shuffle_gap( cursor_index, gap_index );
  }
  
  int new_size = text_before_gap.size() - num_to_remove;

  vector<char> removed;
  removed.assign(
    text_before_gap.begin() + new_size,
    text_before_gap.end()
    );

  std::vector<char> new_text_before_gap {};
  for( int i = 0; i < new_size; i++ )
  {
    new_text_before_gap.push_back( text_before_gap.at( i ) );
  }
  update_cursor_on_remove( removed );
  text_before_gap = new_text_before_gap;
  sync_text();
}


std::vector<char> GapBuffer::get_text() const
{
  return text;
}

std::vector<std::unique_ptr<GlyphData>> GapBuffer::to_glyph_data()
{
  int text_length = text.size();
  vector<std::unique_ptr<GlyphData>> glyph_data {};
  int character_count = 0;
  int row = 0;
  int column = 0;

  while( character_count <= text_length )
  {
    char nodified_char;
    if( character_count < text_length )
    {
      nodified_char = text.at( character_count );
    }
    else
    {
      nodified_char = ' ';
    }
      
    bool selected = cursor -> get_row() == row && cursor -> get_column() == column;    

    std::unique_ptr<GlyphData> glyph_datum = std::make_unique<GlyphData>(
      nodified_char,
      row,
      column,
      selected
      );

    glyph_data.push_back( std::move( glyph_datum ) );
    column++;
    
    if( nodified_char == '\n' )
    {
      row++;
      column = 0;
    }
    
    character_count++;
  }

  return glyph_data;
}

Cursor& GapBuffer::get_cursor() const
{
  return *cursor;
}

void GapBuffer::update_cursor_row( int row_change )
{
  int number_of_rows = calculate_num_rows();
  int max_cursor_row = number_of_rows;
  int new_row = std::min(
    cursor -> get_row() + row_change,
    max_cursor_row
    );

  int original_column = cursor -> get_column();
  int line_length = calculate_line_length( new_row );

  int new_column = original_column;
  if( line_length <= original_column )
  {
    if( new_row == max_cursor_row )
    {
      new_column = line_length;
    }
    else
    {
      new_column = line_length - 1;
    }
  }

  if( new_row < 0 )
  {
    new_row = 0;
  }
  else if( new_row > max_cursor_row )
  {
    new_row = max_cursor_row;
  }

  cursor -> set_column( new_column );
  cursor -> set_row( new_row );
}

void GapBuffer::update_cursor_column( int column_change )
{
  int number_of_rows = calculate_num_rows();
  int new_row = cursor -> get_row();
  int line_length = calculate_line_length( new_row );

  int new_column = std::min(
    cursor -> get_column() + column_change,
    line_length
    );

  if( new_column < 0 )
  {
    new_row--;
    if( new_row < 0 )
    {
      new_row = 0;
      new_column = 0;
    }
    else
    {
      new_column = calculate_line_length( new_row ) - 1;
    }
  }
  else if( new_column == line_length )
  {
    int old_row = cursor -> get_row();
    new_row = std::min( ++new_row, number_of_rows );
    if( new_row == number_of_rows && old_row == number_of_rows )
    {
      new_column = calculate_line_length( new_row );
    }
    else
    {
      new_column = 0;
    }
  }

  cursor -> set_row( new_row );
  cursor -> set_column( new_column );
}

void GapBuffer::cursor_end()
{
  int current_row = cursor -> get_row();
  int new_column = calculate_line_length( current_row );
  if( current_row != calculate_num_rows() )
  {
    new_column--;
  }

  cursor -> set_column( new_column );
}

void GapBuffer::cursor_home()
{
  cursor -> set_column( 0 );
}

int GapBuffer::calculate_cursor_index()
{
  int index = 0;
  int row = cursor -> get_row();

  int rows_encountered = 0;
  int before_gap_size = text_before_gap.size();
  std::vector<char> text_to_check;
  while( rows_encountered < row )
  {
    if( index < before_gap_size )
    {
      text_to_check = text_before_gap;
    }
    else
    {
      text_to_check = text_after_gap;
    }
    
    if( text_to_check.at( index ) == '\n' )
    {
      rows_encountered++;
    }
    ++index;
  }

  return index += cursor -> get_column();
}

void GapBuffer::shuffle_gap( int cursor_index, int gap_index )
{
  std::vector<char> new_text_before_gap {};
  std::vector<char> new_text_after_gap {};
  if( cursor_index < gap_index )
  {
    for( int i = 0; i < cursor_index; i++ )
    {
      new_text_before_gap.push_back( text_before_gap.at( i ) );
    }

    for( int i = cursor_index; i < text_before_gap.size(); i++ )
    {
      new_text_after_gap.push_back( text_before_gap.at( i ) );
    }

    for( int i = 0; i < text_after_gap.size(); i++ )
    {
      new_text_after_gap.push_back( text_after_gap.at( i ) );
    }
  }
  else if( cursor_index > gap_index )
  {
    for( int i = 0; i < text_before_gap.size(); i++ )
    {
      new_text_before_gap.push_back( text_before_gap.at( i ) );
    }
    
    for( int i = 0; i < cursor_index - text_before_gap.size(); i++ )
    {
      new_text_before_gap.push_back( text_after_gap.at( i ) );
    }

    for( int i = cursor_index - text_before_gap.size(); i < text_after_gap.size(); i++ )
    {
      new_text_after_gap.push_back( text_after_gap.at( i ) );
    }
  }
  
  text_before_gap.assign(
    new_text_before_gap.begin(),
    new_text_before_gap.end()
    );
  
  text_after_gap.assign(
    new_text_after_gap.begin(),
    new_text_after_gap.end()
    );
}

void GapBuffer::update_cursor_on_insert( char character )
{
  int cursor_row = cursor -> get_row();
  int cursor_column = cursor -> get_column();
  if( character == '\n' )
  {
    cursor -> set_row( ++cursor_row );
    cursor -> set_column( 0 );
  }
  else
  {
    cursor -> set_column( ++cursor_column );
  }
}

void GapBuffer::update_cursor_on_remove( vector<char> removed )
{
  int row_change = 0;
  int column_change = 0;
  
  for( char character : removed )
  {
    update_cursor_column( -1 );
  }  
}

int GapBuffer::calculate_line_length( int row )
{
  int index = 0;
  int rows_counted = 0;
  while( rows_counted < row )
  {
    if( text.at( index ) == '\n' )
    {
      rows_counted++;
    }
    index++;
  }

  int line_length = 0;

  if( index < text.size() )
  {
    char current_char = text.at( index );
    bool count_newline = current_char == '\n';
    while( current_char != '\n' && index < text.size() )
    {
      current_char = text.at( index );
      line_length++;
      index++;
    }

    if( count_newline )
    {
      line_length++;
    }
  }

  return line_length;
}

int GapBuffer::calculate_num_rows()
{
  int num_rows = 0;

  for( int i = 0; i < text.size(); i++ )
  {
    if( text.at( i ) == '\n' )
    {
      ++num_rows;
    }
  }

  return num_rows;
}

void GapBuffer::sync_text()
{
  text.clear();
  for( int i = 0; i < text_before_gap.size(); i++ )
  {
    text.push_back( text_before_gap.at( i ) );
  }

  for( int i = 0; i < text_after_gap.size(); i++ )
  {
    text.push_back( text_after_gap.at( i ) );
  }
}

void GapBuffer::set_path( std::string param_path )
{
  path = param_path;
}

std::string GapBuffer::get_path() const
{
  return path;
}
