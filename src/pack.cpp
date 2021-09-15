#include "pack.hpp"

inline void clearGrid(byte *grid) { 
    for (unsigned i = 0; i < GR_WIDTH * GR_HEIGHT * GR_DEPTH; i++) {
	grid[i] = (byte)Block::EMPTY;
    }
}
inline int round(float f) {
    return (int)(f + 0.5f);
}
int getIndex(int x, int y, int z) {
    /*
    printf("\n");
    printf("x: %i, y: %i, z: %i +++++++++++++++++++++++++++\n", x, y, z);
    */
    if (x < 0 || y < 0 || z < 0) {
	printf("ERROR WHILE GETTING INDEX\n");
	return 0;
    } else {
	return y * GR_WIDTH + x + GR_WIDTH * GR_HEIGHT * z;
    }
}

Pack::Pack(Position p, Block t, std::vector<glm::vec3> b) : 
    cells(b), pos(p), type(t) {
    rotPivot = glm::vec3(
	    (GR_WIDTH  - 1) / 2, 
	    (GR_HEIGHT - 1) / 2, 
	    (GR_DEPTH  - 1) / 2
	    );

    grid = (byte*)malloc(sizeof(byte) * GR_WIDTH * GR_HEIGHT * GR_DEPTH);

    for (glm::vec3 i : cells) { 
	if (i.x >= GR_WIDTH  ||
		i.y >= GR_HEIGHT ||
		i.z >= GR_DEPTH) {
	    printf("Pack ERROR\n");
	}
    }
    update();
}

Pack::~Pack() {
    free(grid);
}

void Pack::update() {
    clearGrid(grid);
    for (glm::vec3 i : cells) {
	grid[getIndex(round(i.x), round(i.y), round(i.z))] = (byte)type;
    }
}

void Pack::rotate() {
    glm::mat4 rotMat(1);
    rotMat = glm::translate(rotMat, rotPivot);
    rotMat = glm::rotate(rotMat, PI / 2, glm::vec3(1.f, 0.f, 0.f));
    rotMat = glm::translate(rotMat, -rotPivot);
    
    Position t = {0, 0, 0}; 			// test tition
    bool can_replace = true;
    std::vector<glm::vec3> new_cells;

    for (glm::vec3 old : cells) {
	glm::vec3 vec = glm::vec3(rotMat * glm::vec4(old, 1.f));

	printf("x %f, y %f, z %f\n",vec.x,vec.y,vec.z);
	
	t.x = round(vec.x);
	t.y = round(vec.y);
	t.z = round(vec.z);
	//t = t + pos;

	printf("x %i, y %i, z %i\n", t.x, t.y, t.z);

	if (map::isColliding(pos)) {
	    can_replace = false;
	    break;
	}
	printf("\n");
	new_cells.push_back(vec);
    }
    if (can_replace) {
	cells = new_cells;
	update();
    }
}
//debug
void Pack::print_pos() { 
    printf("x %i, y %i, z %i\n", this->pos.x, this->pos.y, this->pos.z);
}
