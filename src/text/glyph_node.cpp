#include "glyph_node.hpp"
#include "hickey_renderer.hpp"

using std::vector;
using std::unique_ptr;

namespace rebarhickey::text
{
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
    
  int GlyphNode::get_height()
  {
    return glyphs.at( 0 ) -> get_h();
  }
    
  int GlyphNode::get_width()
  {
    return glyphs.at( 0 ) -> get_w();
  }
        
  void GlyphNode::accept_renderer( rebarhickey::engine::HickeyRenderer& renderer )
  {
    renderer.render_all( glyphs );
  }
}
