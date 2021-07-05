CXX        = clang++
MAIN_SOURCES    = src/main.cpp src/shaderprogram.cpp
MAIN_OBJS    = $(MAIN_SOURCES:%.cpp=build/%.cpp.o)
export CCFLAGS  = -g -Iinclude -I. -O0
export CXXFLAGS = $(CCFLAGS)
export LDLIBS	= -lGL -lglfw -lGLEW

.PHONY : run clean

build : t3tris

run : build
	./t3tris

rd : build
	gdb -ex run ./t3tris

t3tris : $(MAIN_OBJS)
	$(CXX) $(CXX_FLAGS) $(LDLIBS) -o $@ $^ #add libs here

build/%.cpp.o : %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(LDLIBS) -MD -MP $< -c -o $@

FORCE:

-include $(MAIN_OBJS:.o=.d)
