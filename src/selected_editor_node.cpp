#include "selected_editor_node.hpp"
#include "SDL_rect.h"
#include "editor_node.hpp"
#include "selected_highlight.hpp"
#include "hickey_renderer.hpp"

using rebarhickey::SelectedEditorNode;
using rebarhickey::EditorNode;

SelectedEditorNode::SelectedEditorNode(
  std::unique_ptr<EditorNode> param_delegate,
  std::unique_ptr<SelectedHighlight> param_highlight
  ) : delegate( std::move( param_delegate ) ),
      highlight( std::move( param_highlight ) )
{
  std::shared_ptr<SDL_Rect> highlight_destination = std::make_shared<SDL_Rect>();
  
  highlight_destination -> x = delegate -> get_x();
  highlight_destination -> y = delegate -> get_y();
  highlight_destination -> w = delegate -> get_width();
  highlight_destination -> h = delegate -> get_height();

  highlight -> set_destination( highlight_destination );
}

std::vector<std::unique_ptr<EditorNode>> SelectedEditorNode::get_sub_nodes()
{
  return delegate -> get_sub_nodes();
}

EditorNode& SelectedEditorNode::get_parent()
{
  return delegate -> get_parent();
}

void SelectedEditorNode::update()
{
  delegate -> update();
}

void SelectedEditorNode::update( rebarhickey::engine::input::InputEvent& event )
{
  delegate -> update( event );
}

bool SelectedEditorNode::accepting_input()
{
  return delegate -> accepting_input();
}

int SelectedEditorNode::get_height()
{
  return delegate -> get_height();
}

int SelectedEditorNode::get_width()
{
  return delegate -> get_width();
}

int SelectedEditorNode::get_x()
{
  return delegate -> get_x();
}

int SelectedEditorNode::get_y()
{
  return delegate -> get_y();
}

void SelectedEditorNode::accept_renderer( rebarhickey::engine::HickeyRenderer& renderer )
{
  renderer.render_component( *highlight );
  delegate -> accept_renderer( renderer );
}
