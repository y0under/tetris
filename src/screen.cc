#include "screen.hpp"

tetris::
Screen::Screen ()
{
  screen_array_.resize (SCREEN_HEIGHT_);
  for (int i = 0; i < SCREEN_HEIGHT_; ++i)
    screen_array_.at(i).resize (SCREEN_WIDTH_);
  // all blank
  for (int i = 0; i < SCREEN_HEIGHT_; ++i)
    for (int j = 0; j < SCREEN_WIDTH_; ++j)
      screen_array_.at(i).at(j) = BLANK_MAEKER_;

  set_wall ();
}

void tetris::
Screen::set_wall ()
{
  // floor
  for (int i = 0; i < SCREEN_WIDTH_; ++i)
    screen_array_.at(SCREEN_HEIGHT_ - 1).at(i) = WALL_MARKER_;
  // wall
  for (int i = 0; i < SCREEN_HEIGHT_; ++i) {
    screen_array_.at(i).at(0)                 = WALL_MARKER_;
    screen_array_.at(i).at(SCREEN_WIDTH_ - 1) = WALL_MARKER_;
  }
}

void tetris::
Screen::print_screen ()
{
#ifdef _WINDOWS
  std::system ("cls");
#else
  std::system ("clear");
#endif

  set_screen ();
  for (int i = 0; i < SCREEN_HEIGHT_; ++i) {
    for (int j = 0; j < SCREEN_WIDTH_; ++j) {
      printf ("%s", MARKER_CHAR_.at (screen_array_.at(i).at(j)).c_str ());
    }
    puts ("");
  }
}

void tetris::
Screen::set_mino_to_screen (
    const int left_top_x,
    const int left_top_y,
    const int height,
    const int width
    const std::vector<std::vector<int> > mino_matrix)
{
  for (int i = left_top_y; i < left_top_y + height; ++i)
    for (int j = left_top_x; j < left_top_x + width; ++j)
      if (1 == mino_matrix.at(i).at(j)) {
        screen_array_.at(i).at(j) = MINO_MARKER_;
}
