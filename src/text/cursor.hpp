#ifndef JAREDALL_REBAR_HICKEY_CURSOR
#define JAREDALL_REBAR_HICKEY_CURSOR

#include "editor_node.hpp"

namespace rebarhickey::text
{
  class Cursor : public EditorNode
  {
  public:

    Cursor( int row, int column );

    ~Cursor() = default;

    virtual std::vector<std::unique_ptr<EditorNode>> get_sub_nodes() override;
    
    virtual EditorNode& get_parent() override;

    virtual void update() override;

    virtual void update( engine::input::InputEvent& event ) override;

    virtual bool accepting_input() override;

    virtual int get_height() override;

    virtual int get_width() override;

    virtual void accept_renderer( engine::HickeyRenderer& renderer ) override;

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
