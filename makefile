cc_version      = -std=c++17
debug_options   = -Wall -g
debug_dir       = bin/debug
debug_bin       = debug
debug_objects   = $(debug_dir)/screen.o $(debug_dir)/mino.o $(debug_dir)/tetris.o
release_dir     = bin/release
release_bin     = tetris
release_objects = $(release_dir)/screen.o $(release_dir)/mino.o $(release_dir)/tetris.o

debug: $(debug_objects)
	clang++ -o $(debug_dir)/$(debug_bin) src/main.cc $(cc_version) $(debug_options) $^

debug_objects:
	clang++ -c -o $(debug_dir)/tetris.o src/tetris.cc $(cc_version) $(debug_options)
	clang++ -c -o $(debug_dir)/screen.o src/screen.cc $(cc_version) $(debug_options)
	clang++ -c -o $(debug_dir)/mino.o src/mino.cc $(cc_version) $(debug_options)

release: $(release_objects)
	clang++ -c -o $(release_dir)/tetris.o src/tetris.cc $(cc_version) $(release_options)
	clang++ -c -o $(release_dir)/screen.o src/screen.cc $(cc_version) $(release_options)
	clang++ -c -o $(release_dir)/mino.o src/mino.cc $(cc_version) $(release_options)
	clang++ -o $(release_dir)/$(release_bin) src/main.cc $(cc_version) $(release_options) $^


debug_run:
	./$(debug_dir)/$(debug_bin)
