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

std::vector<std::unique_ptr<EditorNode>> Cursor::get_sub_nodes()
{
  return {};
}

EditorNode& Cursor::get_parent()
{
  return *this;
}

void Cursor::update()
{
}

void Cursor::update( InputEvent& event )
{
}

bool Cursor::accepting_input()
{
  return false;
}

int Cursor::get_height()
{
  return 0;
}

int Cursor::get_width()
{
  return 0;
}

void Cursor::accept_renderer( HickeyRenderer& renderer )
{
}

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
