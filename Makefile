LIBS=-lGL -lglfw -lGLEW
HEADERS=shaderprogram.hpp
FILES=main.cpp shaderprogram.cpp

main_file: $(FILES) $(HEADERS)
	g++ -o tetris $(FILES) $(LIBS) -I.
