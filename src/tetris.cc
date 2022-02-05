#include "tetris.hpp"

/*
 * date: 2022/01/21
 * what: constructor
 */
tetris::
Tetris::Tetris ()
{
  score_ = 0;
}

/*
 * date: 2022/01/20
 * what: main processing of tetris
 */
void tetris::
Tetris::tetris_processing ()
{
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());

  clock_t last_clock = clock ();
  clock_t now_clock;

  while (1) {
    generate_mino (engine ());
    set_point_mino_top ();
    if (is_intersect_mino_wall ())
      break;
    print_screen_processing ();
    while (1) {
      keybord_processing ();
      now_clock = clock ();
      if (INTERVAL > now_clock - last_clock)
        continue;

      // auto fall
      last_clock = now_clock;
      ++mino_left_top_y_;

      if (is_intersect_mino_wall ()) {
        arrive_bottom_processing ();
        break;
      }
      print_screen_processing ();
    }
  }
}

/*
 * date: 2022/01/20
 * what: look at function name
 */
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
  printf ("score: %d\n", score_);
}

/*
 * date: 2022/01/20
 * what: generate new fallen mino
 *       by std::mt19937
 */
void tetris::
Tetris::generate_mino (std::uint32_t random_number)
{
  mino_type_
    = random_number % mino_.get_number_of_types_mino ();
}

/*
 * date: 2022/01/20
 * what: look at function name
 */
bool tetris::
Tetris::is_intersect_mino_wall ()
{
  auto mino_status  = mino_.get_mino_status (mino_type_);
  auto screen_array = screen_.get_screen_array ();

  for (int i = 0; i < mino_status.height_; ++i) {
    for (int j = 0; j < mino_status.width_; ++j) {
      if (1 != mino_status.mino_matrix_.at(i).at(j))
        continue;
      if (1 > mino_left_top_x_ + j ||
          screen_.SCREEN_WIDTH_ - 2 < mino_left_top_x_ + j)
        return true;
      int screen_cel
        = screen_array.at(mino_left_top_y_ + i).at(mino_left_top_x_ + j);
      if (screen_.get_blank_marker () != screen_cel &&
          screen_.get_mino_marker ()  != screen_cel)
        return true;
    }
  }
  return false;
}

/*
 * date: 2022/01/20
 * what: processing when arrived bottom
 */
void tetris::
Tetris::fallen_mino_processing ()
{
  auto mino_status  = mino_.get_mino_status (mino_type_);

  for (int i = 0; i < mino_status.height_; ++i) {
    for (int j = 0; j < mino_status.width_; ++j) {
      if (0 == mino_status.mino_matrix_.at(i).at(j))
        continue;
      screen_.load_mino (mino_left_top_y_ + i, mino_left_top_x_ + j);
    }
  }
}

/*
 * date: 2022/01/20
 * what: determin origin of fallen mino
 */
void tetris::
Tetris::set_point_mino_top ()
{
  auto mino_status = mino_.get_mino_status (mino_type_);
  mino_left_top_x_
    = (screen_.SCREEN_WIDTH_ - mino_status.width_) / 2;
  mino_left_top_y_ = 0;
}

/*
 * date: 2022/01/20
 * what: sence input from keybord
 */
void tetris::
Tetris::keybord_processing ()
{
  if (!kbhit ())
    return ;

  char input_char = getch ();
  int  befor_y    = mino_left_top_y_;
  int  befor_x    = mino_left_top_x_;

  input_processing_from_keybord (input_char);
  if (is_intersect_mino_wall ())
    undo_input_processing (input_char, befor_y, befor_x);
  print_screen_processing ();
}

/*
 * date: 2022/01/20
 * what: branch by kind of char
 */
void tetris::
Tetris::input_processing_from_keybord (
    const char input_char)
{
  switch (input_char) {
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

/*
 * date: 2022/01/20
 * what: undo user's operation
 * when: intersect mino and wall or mino and loaded mino
 */
void tetris::
Tetris::undo_input_processing (
    const char input_char, const int befor_y, const int befor_x)
{
  switch (input_char) {
    case 'a':
    case 'd':
    case 's':
      mino_left_top_y_ = befor_y;
      mino_left_top_x_ = befor_x;
      break;
    case 'l':
      mino_.rotation_mino (mino_type_, mino_.RIGHT_ROT_);
      break;
    case 'r':
      mino_.rotation_mino (mino_type_, mino_.LEFT_ROT_);
      break;
  }
}

/*
 * date: 2022/01/20
 * what: look at function name
 */
void tetris::
Tetris::arrive_bottom_processing ()
{
  --mino_left_top_y_;
  fallen_mino_processing ();
  delete_row_processing ();
  screen_.print_screen ();
}

/*
 * date: 2022/01/20
 * what: if complete row,
 *       delete it
 */
void tetris::
Tetris::delete_row_processing ()
{
  auto screen_array = screen_.get_screen_array ();
  for (int i = 0; i < screen_.SCREEN_HEIGHT_ - 1; ++i) {
    for (int j = 1; j < screen_.SCREEN_WIDTH_ - 1; ++j) {
      if (screen_.get_fallen_mino_marker () !=
          screen_array.at(i).at(j))
        break;
      if (j == screen_.SCREEN_WIDTH_ - 2) {
        screen_.delete_row_processing (i);
        score_ += SCORE_PER_ONE_ROW_;
      }
    }
  }
}
