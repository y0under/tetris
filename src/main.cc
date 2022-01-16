#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#ifdef _WINDOWS
#include <conio.h>
#else
#include "../util/y0_conio.h"
#endif

#include "mino.hpp"
#include "screen.hpp"

namespace tetris
{
  class Tetris
  {
    private:
      Screen screen;
    public:
      void tetris_processing ();
  };
}// namespace tetris

void tetris::
Tetris::tetris_processing ()
{
  while (1) {
    screen.print_screen ();
    getch ();
  }
}


int main ()
{
  tetris::Tetris tetris;
  tetris.tetris_processing ();

  return 0;
}
