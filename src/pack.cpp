#include "pack.hpp"

inline unsigned getIndex(unsigned x, unsigned y, unsigned z) {
    return y * GR_WIDTH + x + GR_WIDTH * GR_HEIGHT * z;
}
 

Pack::Pack(Position p, Block t, std::vector<Position> blocks) : 
    cells(blocks), pos(p), type(t) {
    grid = (byte*)malloc(sizeof(byte) * GR_WIDTH * GR_HEIGHT * GR_DEPTH);

    for (Position i : cells) { 
	if (i.x >= GR_WIDTH  ||
		i.y >= GR_HEIGHT ||
		i.z >= GR_DEPTH) {
	    printf("Pack ERROR\n");
	}
    }
    for (int z = 0; z < GR_DEPTH; z++) {
	for (int y = 0; y < GR_DEPTH; y++) {
	    for (int x = 0; x < GR_DEPTH; x++) {
		grid[getIndex(x, y, z)] = (byte)Block::EMPTY;
	    }
	}
    }
    update();
}

Pack::~Pack() {
    free(grid);
}

void Pack::update() {
    for (Position i : cells) {
	grid[getIndex(i.x, i.y, i.z)] = (byte)type;
	printf("thing: %i\n", (int)grid[getIndex(i.x, i.y, i.z)]);
    }
}
//debug
void Pack::print_pos() { 
    printf("x %i, y %i, z %i\n", this->pos.x, this->pos.y, this->pos.z);
}
