#ifndef JAREDALL_REBAR_HICKEY_BUFFER
#define JAREDALL_REBAR_HICKEY_BUFFER

#include "cursor.hpp"
#include "glyph_data.hpp"
#include <vector>

namespace rebarhickey::text
{
  class GapBuffer
  {
  public:

    GapBuffer();

    void insert( char character );

    void remove( int num_to_remove );

    std::vector<char> get_text() const;

    std::vector<std::unique_ptr<GlyphData>> to_glyph_data();

    Cursor& get_cursor() const;
    
    void update_cursor_row( int row_change );

    void update_cursor_column( int column_change );

    std::string get_path() const;

    void set_path( std::string );

  private:

    int calculate_cursor_index();

    void shuffle_gap(int cursor_index, int gap_index );

    void update_cursor_on_insert( char character );

    void update_cursor_on_remove( std::vector<char> removed );

    int calculate_line_length( int row );

    int calculate_num_rows();

    void sync_text();

    std::vector<char> text_before_gap;    
    std::vector<char> text_after_gap;
    std::vector<char> text;
    std::string path;
    std::unique_ptr<Cursor> cursor;

  };
  
};

#endif
