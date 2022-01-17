#include <cstdio>
#include <ctime>
#include <random>
#include <string>
#include <vector>

//#include <iostream>

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
      const int FPS      = 5;
      const int INTERVAL = 1'000'000 / FPS;

      // function
      void generate_mino (std::uint32_t random_number, const int type_of_mino);
      void create_wall (
          const int mino_height,
          const int mino_witdh,
          const std::vector<std::vector<int> > mino_matrix);
      void keybord_processing ();
      bool is_intersect_mino_wall (
          const int mino_height,
          const int mino_witdh,
          const std::vector<std::vector<int> > mino_matrix);

    public:
      // function
      void tetris_processing ();
  };
}// namespace tetris

void tetris::
Tetris::tetris_processing ()
{
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());

  clock_t last_clock = clock ();
  clock_t now_clock;

  while (1) {
    generate_mino (engine (), mino_.get_number_of_types_mino ());
    screen_.print_screen ();
    auto mino_status
      = mino_.get_mino_status (mino_type_);
      mino_left_top_x_
        = (screen_.SCREEN_WIDTH_ - mino_status.width_) / 2;
      mino_left_top_y_ = 0;
    while (1) {
      int befor_y = mino_left_top_y_;
      int befor_x = mino_left_top_x_;
      if (kbhit ()) {
        keybord_processing ();
        if (is_intersect_mino_wall (
              mino_status.height_, mino_status.width_, mino_status.mino_matrix_)) {
          mino_left_top_y_ = befor_y;
          mino_left_top_x_ = befor_x;
        }

        screen_.erase_mino_on_screen ();

        screen_.set_mino_to_screen (
            mino_left_top_x_, mino_left_top_y_,
            mino_status.height_, mino_status.width_,
            mino_status.mino_matrix_);

        screen_.print_screen ();
      }

      now_clock = clock ();
      if (INTERVAL > now_clock - last_clock)
        continue;

      last_clock = now_clock;

      screen_.erase_mino_on_screen ();

      screen_.set_mino_to_screen (
          mino_left_top_x_, mino_left_top_y_,
          mino_status.height_, mino_status.width_,
          mino_status.mino_matrix_);

      screen_.print_screen ();

      ++mino_left_top_y_;

      if (is_intersect_mino_wall (
            mino_status.height_, mino_status.width_, mino_status.mino_matrix_)) {
        --mino_left_top_y_;
        create_wall (
            mino_status.height_, mino_status.width_, mino_status.mino_matrix_);
        break;
      }
    }
  }
}

void tetris::
Tetris::generate_mino (std::uint32_t random_number, const int type_of_mino)
{
  mino_type_ = random_number % type_of_mino;
}

bool tetris::
Tetris::is_intersect_mino_wall (
    const int mino_height,
    const int mino_witdh,
    const std::vector<std::vector<int> > mino_matrix)
{
  auto screen_array = screen_.get_screen_array ();

  for (int i = 0; i < mino_height; ++i) {
    for (int j = 0; j < mino_witdh; ++j) {
      if (1 == mino_matrix.at(i).at(j) &&
          (screen_.get_wall_marker () ==
           screen_array.at(mino_left_top_y_ + i).at(mino_left_top_x_ + j)))
        return true;
    }
  }
  return false;
}

void tetris::
Tetris::create_wall (
    const int mino_height,
    const int mino_witdh,
    const std::vector<std::vector<int> > mino_matrix)
{
  auto screen_array = screen_.get_screen_array ();
  for (int i = 0; i < mino_height; ++i) {
    for (int j = 0; j < mino_witdh; ++j) {
      if (0 == mino_matrix.at(i).at(j))
        continue;
      screen_.set_wall (mino_left_top_y_ + i, mino_left_top_x_ + j);
    }
  }
}

void tetris::
Tetris::keybord_processing ()
{
  switch (getch ()) {
    case 'a':
      --mino_left_top_x_;
      break;
    case 'd':
      ++mino_left_top_x_;
      break;
    case 's':
      ++mino_left_top_y_;
      break;
  }
}

int main ()
{
  tetris::Tetris tetris;
  tetris.tetris_processing ();

  return 0;
}

