#include "glyph_node.hpp"
#include "hickey_renderer.hpp"

using std::vector;
using std::unique_ptr;

namespace rebarhickey::text
{
  GlyphNode::GlyphNode(
    int param_row,
    int param_column,
    std::unique_ptr<Glyph> param_glyph
    ) :
    row( param_row ),
    column( param_column ),
    glyph( std::move( param_glyph ) )
  {
    glyph -> set_x( column * glyph -> get_w() );
    glyph -> set_y( row * glyph -> get_h() );
  }

  vector<unique_ptr<EditorNode>> GlyphNode::get_sub_nodes()
  {
    return {};
  }

  EditorNode& GlyphNode::get_parent()
  {
    return *this;
  }

  void GlyphNode::update(){}

  void GlyphNode::update( rebarhickey::engine::input::InputEvent& event ){}
  
  bool GlyphNode::accepting_input()
  {
    return false;
  }
        
  void GlyphNode::accept_renderer( rebarhickey::engine::HickeyRenderer& renderer )
  {
    renderer.render_component( *glyph );
  }

  int GlyphNode::get_height()
  {
    return glyph -> get_h();
  }

  int GlyphNode::get_width()
  {
    return glyph -> get_w();
  }

  int GlyphNode::get_row() const
  {
    return row;
  }

  int GlyphNode::get_column() const
  {
    return column;
  }
  
  const std::unique_ptr<Glyph>& GlyphNode::get_glyph() const
  {
    return glyph;
  }
}
