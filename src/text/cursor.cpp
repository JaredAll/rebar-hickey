#include "cursor.hpp"
#include "editor_node.hpp"
#include "hickey_renderer.hpp"
#include "input_event.hpp"

using rebarhickey::text::Cursor;
using rebarhickey::EditorNode;
using rebarhickey::engine::input::InputEvent;
using rebarhickey::engine::HickeyRenderer;

Cursor::Cursor( int param_row, int param_column )
  : row( param_row ), column( param_column )
{}

int Cursor::get_row() const
{
  return row;
}

int Cursor::get_column() const
{
  return column;
}

void Cursor::set_row( int param_row )
{
  row = param_row;
}

void Cursor::set_column( int param_column )
{
  column = param_column;
}
