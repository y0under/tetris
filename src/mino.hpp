#ifndef TETRIS_SRC_MINO_HPP
#define TETRIS_SRC_MINO_HPP

#include <vector>

namespace tetris
{
  class Mino
  {
    private:
      struct MinoStatus
      {
        int height_;
        int width_;
        std::vector<std::vector<int> > mino_matrix_;
      };

      enum {
        MINO_I_,
        MINO_O_,
        MINO_S_,
        MINO_Z_,
        MINO_J_,
        MINO_L_,
        MINO_T_,
        NUMBER_OF_TYPES_MINO_
      };

      // value
      const int MINO_HEIGHT_ = 4;
      const int MINO_WIDTH_  = 4;

      std::vector<MinoStatus> mino_array_;

      // function
      void mino_initialize_I ();
      void mino_initialize_O ();
      void mino_initialize_S ();
      void mino_initialize_Z ();
      void mino_initialize_J ();
      void mino_initialize_L ();
      void mino_initialize_T ();

    public:
      enum {
        LEFT_ROT_,
        RIGHT_ROT_,
        ROT_TYPES_
      };

      Mino ();
      void mino_initializer ();
      void rotation_mino (int mino_type, int direction);
      int get_number_of_types_mino ();
      MinoStatus get_mino_status (int type);

  };
} // namespace tetris

#endif
