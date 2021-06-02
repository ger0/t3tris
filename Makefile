LIBS=-lGL -lglfw -lGLEW
HEADERS=
FILES=main.cpp

main_file: $(FILES) $(HEADERS)
	g++ -o tetris $(FILES) $(LIBS) -I.
