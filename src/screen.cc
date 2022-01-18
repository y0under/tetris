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

  create_first_wall ();
}

void tetris::
Screen::create_first_wall ()
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

  // set_screen ();
  for (int i = 0; i < SCREEN_HEIGHT_; ++i) {
    for (int j = 0; j < SCREEN_WIDTH_; ++j) {
      printf ("%s", MARKER_CHAR_.at (screen_array_.at(i).at(j)).c_str ());
    }
    puts ("");
  }
}

const std::vector<std::vector<int> >
tetris::Screen::get_screen_array ()
{
  return screen_array_;
}
/*
void tetris::
Screen::set_screen ()
{
  // clear_screen ();
  set_mino_to_screen ();
}
*/

int tetris::
Screen::get_wall_marker ()
{
  return WALL_MARKER_;
}

void tetris::
Screen::set_wall (const int y, const int x)
{
  screen_array_.at(y).at(x) = WALL_MARKER_;
}

void tetris::
Screen::set_mino_to_screen (
    const int left_top_x,
    const int left_top_y,
    const int height,
    const int width,
    const std::vector<std::vector<int> > mino_matrix)
{
  for (int i = 0; i < height; ++i)
    for (int j = 0; j < width; ++j)
      if (1 == mino_matrix.at(i).at(j) &&
          (WALL_MARKER_ !=
           screen_array_.at(left_top_y + i).at(left_top_x + j))) {
        screen_array_.at(left_top_y + i).at(left_top_x + j)
          = MINO_MARKER_;
      }
}

void tetris::
Screen::erase_mino_on_screen ()
{
  for (int i = 0; i < SCREEN_HEIGHT_; ++i)
    for (int j = 0; j < SCREEN_WIDTH_; ++j)
      if (MINO_MARKER_ == screen_array_.at(i).at(j))
        screen_array_.at(i).at(j) = BLANK_MAEKER_;
}

void tetris::
Screen::delete_row_processing ()
{
  for (int i = 0; i < SCREEN_HEIGHT_ - 1; ++i) {
    for (int j = 1; j < SCREEN_WIDTH_ - 1; ++ j) {
      if (WALL_MARKER_ != screen_array_.at(i).at(j))
        break;
      if (SCREEN_WIDTH_ - 2 == j) {
        delete_row (i);
        copy_row_to_under (i);
      }
    }
  }
}

void tetris::
Screen::delete_row (int y)
{
  for (int i = 1; i < SCREEN_WIDTH_ - 1; ++i)
    screen_array_.at(y).at(i) = BLANK_MAEKER_;
}

void tetris::
Screen::copy_row_to_under (int y)
{
  for (int i = y; i != 0; --i)
    for (int j = 1; j < SCREEN_WIDTH_ - 1; ++j)
      screen_array_.at(i).at(j) =
        screen_array_.at(i - 1).at(j);
}
