#include "pack.hpp"

inline void clearGrid(byte *grid) { 
    for (unsigned i = 0; i < GR_WIDTH * GR_HEIGHT * GR_DEPTH; i++) {
	grid[i] = (byte)Block::EMPTY;
    }
}
inline int round(float f) {
    return (int)(f + 0.8f);
}
inline Position vec3_to_pos(glm::vec3 vec) {
    return Position{round(vec.x), round(vec.y), round(vec.z)};
}

int getIndex(int x, int y, int z) {
    if (x < 0 || y < 0 || z < 0 ||
	    x >= GR_WIDTH || y >= GR_HEIGHT || z >= GR_DEPTH) {
	printf("ERROR WHILE GETTING INDEX: x: %u, y: %u, z %u\n", x, y, z);
	return 0;
    } else {
	return y * GR_WIDTH + x + GR_WIDTH * GR_HEIGHT * z;
    }
}

Pack::Pack(Block t, std::vector<glm::vec3> b) : 
    cells(b), type(t) {
    //pos = Position{(MAP_WIDTH - 1) / 2, (MAP_HEIGHT - GR_HEIGHT), (MAP_DEPTH - 1) / 2};
    pos = Position{(MAP_WIDTH - GR_WIDTH) / 2, (MAP_HEIGHT - GR_HEIGHT), (MAP_DEPTH - GR_DEPTH) / 2};
    rotPivot = glm::vec3(
	    (GR_WIDTH  - 1) / 2, 
	    (GR_HEIGHT - 1) / 2, 
	    (GR_DEPTH  - 1) / 2
	    );

    grid = (byte*)malloc(sizeof(byte) * GR_WIDTH * GR_HEIGHT * GR_DEPTH);

    // ghetto check
    for (auto i : cells) { 
	if (i.x >= GR_WIDTH  ||
		i.y >= GR_HEIGHT ||
		i.z >= GR_DEPTH) {
	    printf("Pack ERROR\n");
	}
    }
    clearGrid(grid);
    update();
}

Pack::~Pack() {
    free(grid);
    cells.clear();
}

void Pack::update() {
    clearGrid(grid);
    for (glm::vec3 i : cells) {
	grid[getIndex(round(i.x), round(i.y), round(i.z))] = (byte)type;
	    //printf("%f, %f, %f\n",i.x,i.y,i.z);
    }
}
void Pack::rotate(glm::vec3 rot) {
    glm::mat4 rotMat(1);
    rotMat = glm::translate(rotMat, rotPivot);
    rotMat = glm::rotate(rotMat, PI / 2, rot);
    rotMat = glm::translate(rotMat, -rotPivot);
    
    Position t = {0, 0, 0}; 			// test
    std::vector<glm::vec3> new_cells;
    glm::vec3 vec;

    for (auto old : cells) {
	vec = glm::vec3(rotMat * glm::vec4(old, 1.f));

	t = vec3_to_pos(vec);
	t = t + pos;

	if (map::isColliding(t)) {
	    return;
	}
	new_cells.push_back(vec);
    }
    cells = new_cells;
    update();
}

bool Pack::move(Position add_pos) {
    Position coord;
    for (auto i : cells) {
	coord = ((pos + vec3_to_pos(i)) + add_pos);
	if (map::isColliding(coord)) {
	    return false;
	}
    }
    pos = pos + add_pos;
    return true;
}
void Pack::pushPiece() {
    for (auto i : cells) {
	map::pushPiece(type, vec3_to_pos(i) + pos);
    }
    map::lineCheck();
}
//debug
void Pack::print_pos() { 
    printf("x %i, y %i, z %i\n", this->pos.x, this->pos.y, this->pos.z);
}
