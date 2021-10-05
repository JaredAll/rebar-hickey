#ifndef REBARHICKEY
#define REBARHICKEY

#include <memory>
#include "engine.hpp"
#include "gap_buffer.hpp"
#include "glyph_alphabet.hpp"
#include "glyph_node.hpp"

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

    std::optional<char> handle_input();

    std::vector<std::unique_ptr<GlyphNode>> nodify( const GapBuffer& gap_buffer );

  private:

    std::unique_ptr<Engine> engine;
    std::unique_ptr<GlyphAlphabet> alphabet;

  };

}

#endif
