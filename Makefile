CXX=clang++
MAIN_SOURCES=src/main.cpp src/shaderprogram.cpp src/board.cpp src/lodepng/lodepng.cpp src/srs.cpp src/shift.cpp
MAIN_OBJS=$(MAIN_SOURCES:%.cpp=build/%.cpp.o)
CCFLAGS=-g -Wextra -Wall -pedantic -Wall -Iinclude -I. -O0 
CXXFLAGS=$(CCFLAGS)
LDFLAGS=-lGL -lglfw -lGLEW

.PHONY : run clean

build : t3tris

run : build
	./t3tris

rd : build
	gdb -ex run ./t3tris

t3tris : $(MAIN_OBJS)
	$(CXX) $(CXX_FLAGS) -o $@ $^ $(LDFLAGS)

build/%.cpp.o : %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MD -MP $< -c -o $@ 

FORCE:

-include $(MAIN_OBJS:.o=.d)
