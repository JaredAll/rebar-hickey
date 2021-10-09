#ifndef JAREDALL_REBAR_HICKEY_CURSOR
#define JAREDALL_REBAR_HICKEY_CURSOR

#include "editor_node.hpp"

namespace rebarhickey::text
{
  class Cursor
  {
  public:

    Cursor( int row, int column );

    ~Cursor() = default;

    int get_row() const;

    int get_column() const;

    void set_row( int row );

    void set_column( int column );

  private:
    int row;
    int column;
  };
}

#endif
