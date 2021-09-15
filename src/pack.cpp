#include "pack.hpp"

inline void clearGrid(byte *grid) { 
    for (unsigned i = 0; i < GR_WIDTH * GR_HEIGHT * GR_DEPTH; i++) {
	grid[i] = (byte)Block::EMPTY;
    }
}
inline int round(float f) {
    return (int)(f + 0.5f);
}
inline Position vec3_to_pos(glm::vec3 vec) {
    return Position{round(vec.x), round(vec.y), round(vec.z)};
}

int getIndex(int x, int y, int z) {
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
void Pack::rotate(glm::vec3 rot) {
    glm::mat4 rotMat(1);
    rotMat = glm::translate(rotMat, rotPivot);
    rotMat = glm::rotate(rotMat, PI / 2, rot);
    rotMat = glm::translate(rotMat, -rotPivot);
    
    Position t = {0, 0, 0}; 			// test tition
    bool can_replace = true;
    std::vector<glm::vec3> new_cells;

    for (glm::vec3 old : cells) {
	glm::vec3 vec = glm::vec3(rotMat * glm::vec4(old, 1.f));

	t = vec3_to_pos(vec);
	t = t + pos;

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

bool Pack::move(Position add_pos) {
    for (auto i : cells) {
	if (map::isColliding((vec3_to_pos(i) + pos) + add_pos)) {
	    return false;
	}
    }
    pos = pos + add_pos;
    return true;
}
//debug
void Pack::print_pos() { 
    printf("x %i, y %i, z %i\n", this->pos.x, this->pos.y, this->pos.z);
}
