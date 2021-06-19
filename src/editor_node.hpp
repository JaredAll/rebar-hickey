#ifndef REBARHICKEY_EDITOR_NODE
#define REBARHICKEY_EDITOR_NODE

#include "hickey_component.hpp"

namespace rebarhickey
{

  class EditorNode: public engine::HickeyComponent
  {
  public:

    virtual std::vector<std::unique_ptr<EditorNode>> get_sub_nodes() = 0;

    virtual EditorNode& get_parent() = 0;

  };

}

#endif
