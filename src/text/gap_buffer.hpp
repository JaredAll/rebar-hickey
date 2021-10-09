#ifndef JAREDALL_REBAR_HICKEY_BUFFER
#define JAREDALL_REBAR_HICKEY_BUFFER

#include "cursor.hpp"
#include <vector>

namespace rebarhickey::text
{
  class GapBuffer
  {
  public:

    GapBuffer();

    void insert( char character );

    void remove( int num_to_remove );

    std::vector<char> get_text();

    Cursor& get_cursor() const;

  private:

    int calculate_cursor_index();

    void shuffle_gap(int cursor_index, int gap_index );

    void update_cursor_on_insert( char character );

    void sync_text();

    std::vector<char> text_before_gap;    
    std::vector<char> text_after_gap;
    std::vector<char> text;

    std::unique_ptr<Cursor> cursor;

  };
};

#endif
