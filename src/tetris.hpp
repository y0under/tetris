#ifndef TETRIS_SRC_TETRIS_HPP
#define TETRIS_SRC_TETRIS_HPP

#include <cstdio>
#include <ctime>
#include <random>
#include <vector>

#ifdef _WINDOWS
#include <conio.h>
#include <kbhit.h>
#else
#include "../util/y0_conio.h"
#include "../util/y0_kbhit.h"
#endif

#include "mino.hpp"
#include "screen.hpp"

namespace tetris
{
  class Tetris
  {
    private:
      // value
      Screen screen_;
      Mino   mino_;
      int mino_left_top_x_;
      int mino_left_top_y_;
      int mino_type_;
      const int FPS      = 2;
      const int INTERVAL = 1'000'000 / FPS;
      const int SCORE_PER_ONE_ROW_ = 10;
      unsigned int score_;

      // function
      void generate_mino(std::uint32_t random_number);
      void fallen_mino_processing();
      void set_point_mino_top();
      void keybord_processing();
      void input_processing_from_keybord(const char input_char);
      void undo_input_processing(
          const char input_char, const int befor_y, const int befor_x);
      void print_screen_processing();
      void arrive_bottom_processing();
      bool is_intersect_mino_wall();
      void delete_row_processing();

    public:
      // function
      Tetris();
      void tetris_processing();
  };
}// namespace tetris

#endif
