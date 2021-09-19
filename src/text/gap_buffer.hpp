#ifndef JAREDALL_REBAR_HICKEY_BUFFER
#define JAREDALL_REBAR_HICKEY_BUFFER

namespace rebarhickey::text
{
  class GapBuffer
  {
  public:

    GapBuffer();

  private:

    std::vector<char> characters;
    
  };
};

#endif
