#ifndef TETRIS_SRC_SCREEN_HPP
#define TETRIS_SRC_SCREEN_HPP

#include <string>
#include <vector>

namespace tetris
{
  class Screen
  {
    private:
      // value
      std::vector<std::vector<int> > screen_array_;
      std::vector<const std::string> MARKER_CHAR_ = {
        "🔳", // WALL_MARKER_
        "　", // BLANK_MAEKER_
        "◻️ ", // MINO_MARKER_
        "◻️ "  // FALLEN_MINO_MARKER_
      };

      // function
      void create_first_wall();
      void delete_row(const int &);
      void copy_row_to_under(const int &);

    public:
      // value
      enum {
        WALL_MARKER_,
        BLANK_MARKER_,
        MINO_MARKER_,
        FALLEN_MINO_MARKER_,
        MARKER_NUMBER_
      };

      const int SCREEN_HEIGHT_ = 21;
      const int SCREEN_WIDTH_  = 12;

      // function
      Screen();
      void load_mino(const int &, const int &);
      void print_screen();
      void set_mino_to_screen(
          const int &, const int &,
          const int &, const int &,
          const std::vector<std::vector<int> >);
      void erase_mino_on_screen();
      void delete_row_processing(const int &);
      const std::vector<std::vector<int> > get_screen_array();
  };
} // namespace tetris

#endif
