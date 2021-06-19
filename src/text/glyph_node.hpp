#ifndef REBARHICKEY_TEXT_GLYPH_NODE
#define REBARHICKEY_TEXT_GLYPH_NODE

#include "editor_node.hpp"
#include "glyph.hpp"

namespace rebarhickey::text
{
  class GlyphNode : public EditorNode
  {
  public:
    
    std::vector<std::unique_ptr<EditorNode>> get_sub_nodes() override;

    EditorNode& get_parent() override;

    void update() override;

    void update( rebarhickey::engine::input::InputEvent& event ) override;
    
    bool accepting_input() override;
    
    int get_height() override;
    
    int get_width() override;
    
    ~GlyphNode() = default;
    
    void accept_renderer( rebarhickey::engine::HickeyRenderer& renderer ) override;

  private:

    std::vector<std::unique_ptr<Glyph>> glyphs;

  };
}

#endif
