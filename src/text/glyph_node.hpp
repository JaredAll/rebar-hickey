#ifndef REBARHICKEY_TEXT_GLYPH_NODE
#define REBARHICKEY_TEXT_GLYPH_NODE

#include "editor_node.hpp"
#include "glyph.hpp"
#include <memory>

namespace rebarhickey::text
{
  class GlyphNode : public EditorNode
  {
  public:

    GlyphNode( int row, int column, std::unique_ptr<Glyph> glyph );

    std::vector<std::unique_ptr<EditorNode>> get_sub_nodes() override;

    EditorNode& get_parent() override;

    void update() override;

    void update( rebarhickey::engine::input::InputEvent& event ) override;
    
    bool accepting_input() override;
    
    int get_height() override;
    
    int get_width() override;

    int get_x() override;
    
    int get_y() override;
    
    ~GlyphNode() = default;
    
    void accept_renderer( rebarhickey::engine::HickeyRenderer& renderer ) override;

    int get_row() const;

    int get_column() const;

    const std::unique_ptr<Glyph>& get_glyph() const;

  private:

    const int row;
    const int column;
    const std::unique_ptr<Glyph> glyph;

    inline const static std::string whitespace_chars = " \n";

  };
}

#endif
