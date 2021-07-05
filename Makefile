LIBS=-lGL -lglfw -lGLEW
HEADERS=shaderprogram.hpp shape.hpp entity.hpp constants.hpp clock.hpp
FILES=main.cpp shaderprogram.cpp entity.cpp

main_file: $(FILES) $(HEADERS)
	g++ -o tetris $(FILES) $(LIBS) -I.
