#ifndef REBARHICKEY
#define REBARHICKEY

#include <memory>
#include "engine.hpp"
#include "gap_buffer.hpp"
#include "glyph_alphabet.hpp"
#include "glyph_node.hpp"
#include "buffer_action.hpp"
#include "hickey_action_factory.hpp"
#include "hickey_highlights.hpp"

using rebarhickey::engine::Engine;
using rebarhickey::text::GapBuffer;
using rebarhickey::text::GlyphAlphabet;
using rebarhickey::text::GlyphNode;

namespace rebarhickey
{
  
  class Hickey
  {
  public:

    Hickey();

    int run();

    std::unique_ptr<GapBuffer> read( const std::string& path );

    void write( const std::string& path, const GapBuffer& gap_buffer ) const;

    std::vector<std::unique_ptr<EditorNode>> nodify( GapBuffer& gap_buffer );
    
    GapBuffer& get_current_buffer() const;

  private:

    std::unique_ptr<Engine> engine;
    std::unique_ptr<GlyphAlphabet> alphabet;
    std::unique_ptr<HickeyHighlights> highlights;
    std::unique_ptr<HickeyActionFactory> hickey_action_factory;
    std::unique_ptr<GapBuffer> gap_buffer;

  };

}

#endif
