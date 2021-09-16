#include "board.hpp"

byte map::data[MAP_WIDTH * MAP_HEIGHT * MAP_DEPTH] = {Block::EMPTY};

inline unsigned getMapIndex(unsigned x, unsigned y, unsigned z) {
    return y * MAP_WIDTH + x + MAP_WIDTH * MAP_HEIGHT * z;
}

void map::initMap() {
    // bottom wall
    for (unsigned z = 0; z < MAP_DEPTH; z++) {
	for (unsigned x = 0; x < MAP_WIDTH; x++) {
	    map::data[getMapIndex(x, 0, z)] = (byte)Block::WALL;
	}
    }
    // side walls 
    // x = 0 & x = max
    for (unsigned z = 0; z < MAP_DEPTH; z++) {
	for (unsigned y = 0; y < MAP_HEIGHT; y++) {
	    map::data[getMapIndex(0, y, z)] = (byte)Block::WALL;
	    map::data[getMapIndex(MAP_WIDTH - 1, y, z)] = (byte)Block::WALL;
	}
    }
    // z = 0 & z = max
    for (unsigned y = 0; y < MAP_HEIGHT; y++) {
	for (unsigned x = 0; x < MAP_WIDTH; x++) {
	    map::data[getMapIndex(x, y, 0)] = (byte)Block::WALL;
	    map::data[getMapIndex(x, y, MAP_DEPTH - 1)] = (byte)Block::WALL;
	}
    }
   // debug 
    map::data[getMapIndex(1,0,1)] = Block::O;
    map::data[getMapIndex(MAP_WIDTH - 2,MAP_HEIGHT - 1, MAP_DEPTH - 2)] = Block::I;
}

inline bool chkBND(Tetromino &tet, unsigned &x, unsigned &y, int rot = 0) {
    if ((tet.data[y * BND_SIZE + x] >> unsigned(tet.rot + rot) % 4) & 1) {
	return true;
    }
    else 
	return false;
}
bool map::isColliding(Position pos) {
    if (pos.x >= MAP_WIDTH  || pos.x < 0 ||
	    pos.y >= MAP_HEIGHT || pos.y < 0 ||
	    pos.z >= MAP_DEPTH  || pos.z < 0) {
	printf("COLLISION: position outside map box, x: %i, y: %i, z: %i\n", 
		pos.x, pos.y, pos.z);
	return true;
    } else if (map::data[getMapIndex(pos.x, pos.y, pos.z)] != Block::EMPTY) {
	return true;
    } else {
	return false;
    }
}

bool map::chkCollision(Tetromino &t, Position mov, int rot) { 
    for (unsigned y = 0; y < BND_SIZE; y++) {
	for (unsigned x = 0; x < BND_SIZE; x++) {
	    if (chkBND(t, x, y, rot)) {
		int coord = getMapIndex(x + t.pos.x + mov.x, y - (t.pos.y + mov.y), t.pos.z + mov.z);
		if (map::data[coord] != Block::EMPTY) {
		    return true;
		}
	    }
	}
    }
    t.pos = t.pos + mov;
    if (rot)
	t.rot = unsigned(t.rot + rot) % 4;
    return false;
}
// tutaj
void lineCheck() {
    bool isFull;
    byte temp[MAP_WIDTH * MAP_HEIGHT];
    for (unsigned y = 0; y < (MAP_HEIGHT - 1); y++) {
	isFull = true;
	for (unsigned z = 1; z < (MAP_DEPTH - 1); z++) {
	    for (unsigned x = 0; x < MAP_WIDTH; x++) {
		if (map::data[getMapIndex(x, y, z)] == Block::EMPTY) {
		    isFull = false;
		}
	    }
	}
	if (isFull) {
	    printf("full line\n");
	    for (unsigned i = 1; i < MAP_DEPTH - 1; i++) {
		memcpy(temp, map::data + i * MAP_HEIGHT * MAP_WIDTH, MAP_HEIGHT * MAP_WIDTH);
		// copies data from lines above the removed line
		memcpy(map::data + MAP_WIDTH + i * MAP_HEIGHT * MAP_WIDTH, temp, y * MAP_WIDTH);
		for (unsigned j = 0; j < MAP_DEPTH; j++) {
		    if (j == 0 || j == MAP_WIDTH - 1)
			map::data[j + MAP_WIDTH * MAP_HEIGHT * i] = Block::WALL;
		    else 
			map::data[j + MAP_WIDTH * MAP_HEIGHT * i] = Block::EMPTY;
		    }
	    }
	}
    }
}

void map::pushPiece(Block b, Position pos) {
    map::data[getMapIndex(pos.x, pos.y, pos.z)] = (byte)b;
}

void map::pushPiece(Tetromino &t) {
    for (unsigned y = 0; y < BND_SIZE; y++) {
	for (unsigned x = 0; x < BND_SIZE; x++) {
	    if (chkBND(t, x, y)) {
		map::data[getMapIndex(x + t.pos.x, y - t.pos.y, t.pos.z)] = (byte)t.type;
	    }
	}
    }
    lineCheck();
}

inline float* getTexCoords(unsigned type) {
    float *new_coords = (float*)malloc(sizeof(float) * 2 * vertCount);
    for (int i = 0; i < vertCount; i++) {
	new_coords[i * 2] = (texCoords[i * 2] + (int)type - 1) / (PIECES + 1); // + wall type
	new_coords[i * 2 + 1] = texCoords[i * 2 + 1];
    }
    return new_coords;
}

void drawGrid(ShaderProgram *sp, GLuint tex,
	    byte grid[], Tetromino *tet, Pack *p) {
    float x_shift = (MAP_WIDTH 	- 1) / 2.0f;
    float y_shift = (MAP_HEIGHT - 1) / 2.0f;
    float z_shift = (MAP_DEPTH  - 1) / 2.0f;

    float *tileTexCoords;

    Position pos = {0, 0, 0};
    int	rot = 0;
    // size of bounding box
    Dimensions size;
    if (tet != NULL) {
	pos = tet->pos;
	rot = tet->rot;
	size = {BND_SIZE, BND_SIZE, 1};
	tileTexCoords = getTexCoords((unsigned)tet->type);
    } else if (p != NULL) {
	pos	= p->pos;
	size	= p->size;
	tileTexCoords = getTexCoords(p->type);
    } else {
	size = Dimensions{MAP_WIDTH, MAP_HEIGHT, MAP_DEPTH};
    }
    unsigned block;

    for (int z = 0; z < size.z; z++) {
	for (int y = 0; y < size.y; y++) {
	    for (int x = 0; x < size.x; x++) {
		block = grid[(y * size.x + x) + size.x * size.y * z];
		if (tet == NULL && p == NULL) {
		    if (x != 0 && x != size.x - 1
			    && z != 0 && z != size.z - 1)
			tileTexCoords = getTexCoords(block);
		    else
			continue;
		}
		if (((block >> rot) & 1) != 0 ||
		    (tet == NULL && block)) {
		    sp->use();

		    glm::mat4 M = glm::mat4(1.f);
		    
		    M = glm::scale(M, glm::vec3(1.f / SCALE, 1.f / SCALE, 1.f / SCALE));
		    M = glm::translate(M, glm::vec3(
			2 * (float)(pos.x + x - x_shift),
			2 * (float)(pos.y + y - y_shift), 
			2 * (float)(pos.z + z - z_shift)));

		    glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

		    glEnableVertexAttribArray(sp->a("normal"));
		    glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, vertNormal);

		    glActiveTexture(GL_TEXTURE0);
		    glBindTexture(GL_TEXTURE_2D, tex);
		    glUniform1i(sp->u("texMap"), 0);
		    glEnableVertexAttribArray(sp->a("texCoord"));
		    glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, 
			    false, 0, tileTexCoords);

		    glEnableVertexAttribArray(sp->a("vertex"));
		    glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, verts);

		    // draw
		    glDrawArrays(GL_TRIANGLES, 0, vertCount);

		    // disable attributes
		    glDisableVertexAttribArray(sp->a("normal"));
		    glDisableVertexAttribArray(sp->a("texCoord"));
		    glDisableVertexAttribArray(sp->a("vertex"));
		    if (tet == NULL && p == NULL)
			free(tileTexCoords);
		}
	    }
	}
    }
    if (tet != NULL || p != NULL)
	free(tileTexCoords);
}
