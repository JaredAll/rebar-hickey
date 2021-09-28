#include "gap_buffer.hpp"

using rebarhickey::text::GapBuffer;

GapBuffer::GapBuffer(){}

void GapBuffer::insert( char character )
{
  text.push_back( character );
}

std::vector<char> GapBuffer::get_text() const
{
  return text;
}

