#ifndef JAREDALL_REBAR_HICKEY_BUFFER
#define JAREDALL_REBAR_HICKEY_BUFFER

#include <vector>

namespace rebarhickey::text
{
  class GapBuffer
  {
  public:

    GapBuffer();

    void insert( char character );

    std::vector<char> get_text() const;

  private:

    std::vector<char> text;
    
  };
};

#endif
