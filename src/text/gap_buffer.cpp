#include "gap_buffer.hpp"
#include <memory>

using rebarhickey::text::GapBuffer;
using rebarhickey::text::Cursor;

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

  std::vector<char> new_text_before_gap {};
  for( int i = 0; i < new_size; i++ )
  {
    new_text_before_gap.push_back( text_before_gap.at( i ) );
  }
  text_before_gap = new_text_before_gap;
  sync_text();
}


std::vector<char> GapBuffer::get_text()
{
  return text;
}

Cursor& GapBuffer::get_cursor() const
{
  return *cursor;
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
