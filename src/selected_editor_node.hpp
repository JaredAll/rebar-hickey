#ifndef SELECTED_EDITOR_NODE
#define SELECTED_EDITOR_NODE

#include "editor_node.hpp"
#include "selected_highlight.hpp"
#include <memory>

namespace rebarhickey
{
  class SelectedEditorNode : public EditorNode
  {
  public:

    SelectedEditorNode( std::unique_ptr<EditorNode>, std::unique_ptr<SelectedHighlight> );

    std::vector<std::unique_ptr<EditorNode>> get_sub_nodes() override;

    EditorNode& get_parent() override;

    void update() override;

    void update( rebarhickey::engine::input::InputEvent& event ) override;
    
    bool accepting_input() override;
    
    int get_height() override;
    
    int get_width() override;

    int get_x() override;
    
    int get_y() override;
    
    ~SelectedEditorNode() = default;
    
    void accept_renderer( rebarhickey::engine::HickeyRenderer& renderer ) override;

  private:

    const std::unique_ptr<EditorNode> delegate;
    const std::unique_ptr<SelectedHighlight> highlight;

  };
}

#endif
