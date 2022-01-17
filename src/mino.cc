#include "mino.hpp"

tetris::
Mino::Mino ()
{
  mino_initializer ();
}

void tetris::
Mino::mino_initializer ()
{
  mino_initialize_I ();
  mino_initialize_O ();
  mino_initialize_S ();
  mino_initialize_Z ();
  mino_initialize_J ();
  mino_initialize_L ();
  mino_initialize_T ();
}

void tetris::
Mino::mino_initialize_I ()
{
  mino_array_.push_back ({
      4, 4, {
      {0, 0, 0, 0},
      {1, 1, 1, 1},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}});
}

void tetris::
Mino::mino_initialize_O ()
{
  mino_array_.push_back ({
      2, 2, {
      {1, 1},
      {1, 1}}});
}

void tetris::
Mino::mino_initialize_S ()
{
  mino_array_.push_back ({
      3, 3, {
      {0, 1, 1},
      {1, 1, 0},
      {0, 0, 0}}});
}

void tetris::
Mino::mino_initialize_Z ()
{
  mino_array_.push_back ({
      3, 3, {
      {1, 1, 0},
      {0, 1, 1},
      {0, 0, 0}}});
}

void tetris::
Mino::mino_initialize_J ()
{
  mino_array_.push_back ({
      3, 3, {
      {1, 1, 1},
      {0, 0, 1},
      {0, 0, 0}}});
}

void tetris::
Mino::mino_initialize_L ()
{
  mino_array_.push_back ({
      3, 3, {
      {1, 1, 1},
      {1, 0, 0},
      {0, 0, 0}}});
}

void tetris::
Mino::mino_initialize_T ()
{
  mino_array_.push_back ({
      3, 3, {
      {1, 1, 1},
      {0, 1, 0},
      {0, 0, 0}}});
}

int tetris::
Mino::get_number_of_types_mino ()
{
  return NUMBER_OF_TYPES_MINO_;
}

tetris::Mino::MinoStatus
tetris::Mino::get_mino_status (int mino_type)
{
  return mino_array_.at(mino_type);
}
