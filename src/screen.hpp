#ifndef TETRIS_SRC_SCREEN_HPP
#define TETRIS_SRC_SCREEN_HPP

#include <string>
#include <vector>

namespace tetris
{
  class Screen
  {
    private:
      enum {
        WALL_MARKER_,
        BLANK_MAEKER_,
        MINO_MARKER_,
        MARKER_NUMBER_
      };

      // value
      std::vector<std::vector<int> > screen_array_;
      std::vector<const std::string> MARKER_CHAR_ = {
        "◻️ ", // WALL_MARKER_
        "　", // BLANK_MAEKER_
        "◻️ "  // MINO_MARKER_
      };

      const int SCREEN_HEIGHT_ = 21;
      const int SCREEN_WIDTH_  = 12;

      // function
      void set_wall ();
      void set_mino_to_screen ();

    public:
      // function
      Screen ();
      void print_screen (const int left_top_x, const int left_top_y
          const int height, const int width);
  };
} // namespace tetris

#endif
