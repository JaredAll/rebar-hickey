#include "hickey_highlights.hpp"
#include "selected_highlight.hpp"
#include <utility>

using rebarhickey::HickeyHighlights;
using rebarhickey::SelectedHighlight;

HickeyHighlights::HickeyHighlights( engine::HickeyRenderer& param_renderer )
  : renderer( param_renderer )
{
  std::string white_block_path = "/home/jared/rebar-hickey/resources/white_block.png";

  highlight_map.insert(
    std::make_pair(
      "white",
      renderer.create_texture( white_block_path )
      )
    );
}

std::unique_ptr<SelectedHighlight> HickeyHighlights::get_highlight()
{
  SDL_Color white { 255, 255, 255 };

  return std::make_unique<SelectedHighlight>(
      0,
      0,
      25,
      25,
      (*highlight_map.find( "white" )).second
    );
}
