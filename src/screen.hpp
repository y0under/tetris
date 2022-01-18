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
        "🔳", // WALL_MARKER_
        "　", // BLANK_MAEKER_
        "◻️ "  // MINO_MARKER_
      };

      // function
      void create_first_wall ();
      void delete_row (int y);
      void copy_row_to_under (int y);

    public:
      // value
      const int SCREEN_HEIGHT_ = 21;
      const int SCREEN_WIDTH_  = 12;

      // function
      Screen ();
      void set_wall (const int y, const int x);
      void print_screen ();
      void set_mino_to_screen (
          const int left_top_x, const int left_top_y,
          const int height, const int width,
          const std::vector<std::vector<int> > mino_matrix);
      void erase_mino_on_screen ();
      void delete_row_processing ();
      const std::vector<std::vector<int> > get_screen_array ();
      int get_wall_marker ();

  };
} // namespace tetris

#endif
