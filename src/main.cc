#include <cstdio>
#include <ctime>
#include <random>
#include <string>
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

      // function
      void generate_mino (std::uint32_t random_number, const int type_of_mino);
      void create_wall ();
      void set_point_mino_top ();
      void keybord_processing ();
      void when_any_input_form_keybord ();
      void input_processing_from_keybord ();
      void print_screen_processing ();
      void arrive_bottom_processing ();
      bool is_intersect_mino_wall ();

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
    set_point_mino_top ();
    if (is_intersect_mino_wall ())
      break;
    while (1) {
      keybord_processing ();
      now_clock = clock ();
      if (INTERVAL > now_clock - last_clock)
        continue;

      last_clock = now_clock;
      ++mino_left_top_y_;

      if (is_intersect_mino_wall ()) {
        arrive_bottom_processing ();
        break;
      }
      print_screen_processing ();
    }
    screen_.delete_row_processing ();
    screen_.print_screen ();
  }
}

void tetris::
Tetris::print_screen_processing ()
{
  auto mino_status = mino_.get_mino_status (mino_type_);
  screen_.erase_mino_on_screen ();
  screen_.set_mino_to_screen (
      mino_left_top_x_,
      mino_left_top_y_,
      mino_status.height_,
      mino_status.width_,
      mino_status.mino_matrix_);
  screen_.print_screen ();
}

void tetris::
Tetris::generate_mino (std::uint32_t random_number, const int type_of_mino)
{
  mino_type_ = random_number % type_of_mino;
}

bool tetris::
Tetris::is_intersect_mino_wall ()
{
  auto mino_status  = mino_.get_mino_status (mino_type_);
  auto screen_array = screen_.get_screen_array ();

  for (int i = 0; i < mino_status.height_; ++i) {
    for (int j = 0; j < mino_status.width_; ++j) {
      if (1 == mino_status.mino_matrix_.at(i).at(j) &&
          (screen_.get_wall_marker () ==
           screen_array.at(mino_left_top_y_ + i).at(mino_left_top_x_ + j)))
        return true;
    }
  }
  return false;
}

void tetris::
Tetris::create_wall ()
{
  auto mino_status  = mino_.get_mino_status (mino_type_);
  auto screen_array = screen_.get_screen_array ();

  for (int i = 0; i < mino_status.height_; ++i) {
    for (int j = 0; j < mino_status.width_; ++j) {
      if (0 == mino_status.mino_matrix_.at(i).at(j))
        continue;
      screen_.set_wall (mino_left_top_y_ + i, mino_left_top_x_ + j);
    }
  }
}

void tetris::
Tetris::set_point_mino_top ()
{
  auto mino_status = mino_.get_mino_status (mino_type_);
  mino_left_top_x_
    = (screen_.SCREEN_WIDTH_ - mino_status.width_) / 2;
  mino_left_top_y_ = 0;
}

void tetris::
Tetris::keybord_processing ()
{
  if (!kbhit ())
    return ;
  when_any_input_form_keybord ();
  screen_.erase_mino_on_screen ();
  print_screen_processing ();
}

void tetris::
Tetris::when_any_input_form_keybord ()
{
  auto mino_status = mino_.get_mino_status (mino_type_);
  int befor_y = mino_left_top_y_;
  int befor_x = mino_left_top_x_;

  input_processing_from_keybord ();
  if (is_intersect_mino_wall ()) {
    mino_left_top_y_ = befor_y;
    mino_left_top_x_ = befor_x;
  }

}

void tetris::
Tetris::input_processing_from_keybord ()
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
    case 'l':
      mino_.rotation_mino (mino_type_, mino_.LEFT_ROT_);
      break;
    case 'r':
      mino_.rotation_mino (mino_type_, mino_.RIGHT_ROT_);
      break;
  }
}

void tetris::
Tetris::arrive_bottom_processing ()
{
  --mino_left_top_y_;
  create_wall ();
}

int main ()
{
  tetris::Tetris tetris;
  tetris.tetris_processing ();

  return 0;
}

