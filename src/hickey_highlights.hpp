#ifndef REBARHICKEY_HICKEY_HIGHLIGHTS
#define REBARHICKEY_HICKEY_HIGHLIGHTS

#include <memory>
#include <map>
#include "SDL_render.h"
#include "glyph.hpp"
#include "engine.hpp"
#include "hickey_renderer.hpp"
#include "selected_highlight.hpp"

namespace rebarhickey
{

  class HickeyHighlights
  {
  public:

    HickeyHighlights( engine::HickeyRenderer& );

    std::unique_ptr<SelectedHighlight> get_highlight();

  private:

    std::map<std::string, std::shared_ptr<SDL_Texture>> highlight_map;
    engine::HickeyRenderer& renderer;

  };

}

#endif
