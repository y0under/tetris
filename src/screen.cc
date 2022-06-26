#include "screen.h"

/*
 * date: 2022/01/20
 * what: constructor
 * prepare first screen
 */
tetris::
Screen::Screen()
{
  screen_array_.resize(SCREEN_HEIGHT_);
  for (int i = 0; i < SCREEN_HEIGHT_; ++i)
    screen_array_.at(i).resize(SCREEN_WIDTH_);
  // all blank
  for (int i = 0; i < SCREEN_HEIGHT_; ++i)
    for (int j = 0; j < SCREEN_WIDTH_; ++j)
      screen_array_.at(i).at(j) = BLANK_MARKER_;

  create_first_wall();
}

/*
 * data: 2022/01/20
 * what: look at function name
 * called constructor
 */
void tetris::
Screen::create_first_wall()
{
  // floor
  for (int i = 0; i < SCREEN_WIDTH_; ++i)
    screen_array_.at(SCREEN_HEIGHT_ - 1).at(i) = WALL_MARKER_;
  // wall
  for (int i = 0; i < SCREEN_HEIGHT_ - 1; ++i) {
    screen_array_.at(i).at(0)                 = WALL_MARKER_;
    screen_array_.at(i).at(SCREEN_WIDTH_ - 1) = WALL_MARKER_;
  }
}

/*
 * data: 2022/06/26
 * what: look at function name
 */
void tetris::
Screen::print_screen()
{
  printf("\033[%dA\n", SCREEN_HEIGHT_ + 2);
  for (int i = 0; i < SCREEN_HEIGHT_; ++i) {
    for (int j = 0; j < SCREEN_WIDTH_; ++j) {
      printf("%s", MARKER_CHAR_.at(screen_array_.at(i).at(j)).c_str());
    }
    printf("\n");
  }
}

/*
 * data: 2022/01/20
 * what: look at function name
 */
const std::vector<std::vector<int> >
tetris::Screen::get_screen_array()
{
  return screen_array_;
}

/*
 * data: 2022/01/20
 * what: look at function name
 */
void tetris::
Screen::load_mino(const int &y, const int &x)
{
  screen_array_.at(y).at(x) = FALLEN_MINO_MARKER_;
}

/*
 * data: 2022/01/20
 * what: set point of mino
 *       to screen_array_
 */
void tetris::
Screen::set_mino_to_screen(
    const int &left_top_x,
    const int &left_top_y,
    const int &height,
    const int &width,
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

/*
 * data: 2022/01/20
 * what: rewrite to blank on screen_array_
 *       for print screen
 */
void tetris::
Screen::erase_mino_on_screen()
{
  for (int i = 0; i < SCREEN_HEIGHT_; ++i)
    for (int j = 0; j < SCREEN_WIDTH_; ++j)
      if (MINO_MARKER_ == screen_array_.at(i).at(j))
        screen_array_.at(i).at(j) = BLANK_MARKER_;
}

/*
 * data: 2022/01/20
 * what: look at function name
 */
void tetris::
Screen::delete_row_processing(const int &row_number)
{
  delete_row(row_number);
  copy_row_to_under(row_number);
}

/*
 * data: 2022/01/20
 * what: look at function name
 */
void tetris::
Screen::delete_row(const int &y)
{
  for (int i = 1; i < SCREEN_WIDTH_ - 1; ++i)
    screen_array_.at(y).at(i) = BLANK_MARKER_;
}

/*
 * data: 2022/01/20
 * what: if delete row,
 *       pad blank row by up row
 */
void tetris::
Screen::copy_row_to_under(const int &y)
{
  for (int i = y; i != 0; --i)
    for (int j = 1; j < SCREEN_WIDTH_ - 1; ++j)
      screen_array_.at(i).at(j) =
        screen_array_.at(i - 1).at(j);
}
