#include "gap_buffer.hpp"

using rebarhickey::text::GapBuffer;

GapBuffer::GapBuffer(){}

void GapBuffer::insert( char character )
{
  text.push_back( character );
}

void GapBuffer::remove( int num_to_remove )
{
  int new_size = text.size() - num_to_remove;

  std::vector<char> new_text {};
  for( int i = 0; i < new_size; i++ )
  {
    new_text.push_back( text.at( i ) );
  }
  text = new_text;
}


std::vector<char> GapBuffer::get_text() const
{
  return text;
}

