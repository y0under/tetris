cc_version    = -std=c++20
debug_options = -Wall -g --pedantic-errors $(cc_version)
options       = $(debug_options)
out_dir       = bin
bin_name      = tetris
objects       = $(out_dir)/screen.o $(out_dir)/mino.o $(out_dir)/tetris.o

$(out_dir)/$(bin_name): src/main.cc $(objects)
	mkdir -p $(out_dir)
	clang++ -o $(out_dir)/$(bin_name) $< $(options) $(objects)

$(out_dir)/tetris.o: src/tetris.cc src/tetris.h
	clang++ -c -o $@ $< $(options)

$(out_dir)/screen.o: src/screen.cc src/screen.h
	mkdir -p $(out_dir)
	clang++ -c -o $@ $< $(options)

$(out_dir)/mino.o: src/mino.cc src/mino.h
	clang++ -c -o $@ $< $(options)

debug_run:
	./$(out_dir)/$(bin_name)

run:
	./$(out_dir)/tetris

