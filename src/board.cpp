#include "board.hpp"

byte map::data[MAP_WIDTH * MAP_HEIGHT] = {Block::EMPTY};

void map::initMap() {
    if (MAP_WIDTH && MAP_HEIGHT && MAP_DEPTH) {
	for (unsigned i = 0; i < MAP_HEIGHT; i++) {
	    map::data[i * MAP_WIDTH] = Block::WALL;
	    map::data[i * MAP_WIDTH + MAP_WIDTH - 1] = Block::WALL;
	}
	for (unsigned i = 0; i < MAP_WIDTH; i++) {
	    map::data[i + MAP_WIDTH * (MAP_HEIGHT - 1)] = Block::WALL;
	}
    }
}

inline bool chkBND(Tetromino &tet, unsigned &x, unsigned &y, int rot = 0) {
    if ((tet.data[y * BND_SIZE + x] >> unsigned(tet.rot + rot) % 4) & 1) {
	return true;
    }
    else 
	return false;
}

bool map::chkCollision(Tetromino &tet, Position mov, int rot) { 
    for (unsigned y = 0; y < BND_SIZE; y++) {
	for (unsigned x = 0; x < BND_SIZE; x++) {
	    if (chkBND(tet, x, y, rot)) {
		int coord = (y - (tet.pos.y + mov.y)) * MAP_WIDTH 
				+ x + tet.pos.x + mov.x;
		if (map::data[coord] != Block::EMPTY) {
		    return true;
		}
	    }
	}
    }
    tet.pos.x += mov.x;
    tet.pos.y += mov.y;
    tet.pos.z += mov.z;
    if (rot)
	tet.rot = unsigned(tet.rot + rot) % 4;
    return false;
}

void lineCheck() {
    bool isFull;
    for (unsigned y = 0; y < (MAP_HEIGHT - 1); y++) {
	isFull = true;
	for (unsigned x = 0; x < MAP_WIDTH; x++) {
	    if (map::data[y * MAP_WIDTH + x] == Block::EMPTY) {
		isFull = false;
	    }
	}
	if (isFull) {
	    printf("full line\n");
	    byte temp[MAP_WIDTH * MAP_HEIGHT];
	    memcpy(temp, map::data, MAP_HEIGHT * MAP_WIDTH);
	    // copies data from lines above the removed line
	    memcpy(map::data + MAP_WIDTH, temp, y * MAP_WIDTH);
	    for (unsigned i = 0; i < MAP_WIDTH; i++) {
		if (i == 0 || i == MAP_WIDTH - 1)
		    map::data[i] = Block::WALL;
		else 
		    map::data[i] = Block::EMPTY;
	    }
	}
    }
}

void map::pushPiece(Tetromino &tet) {
    for (unsigned y = 0; y < BND_SIZE; y++) {
	for (unsigned x = 0; x < BND_SIZE; x++) {
	    if (chkBND(tet, x, y)) {
		map::data[(y - tet.pos.y) * MAP_WIDTH + (x + tet.pos.x)] = (byte)tet.type;
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
	    byte grid[], Tetromino *tet) {

    float x_shift = (MAP_WIDTH - 1) / 2.0f;
    float y_shift = (MAP_HEIGHT - 1) / 2.0f;

    float *tileTexCoords;

    Position pos = {0, 0, 0};
    int	rot = 0;
    // size of bounding box
    Position size;
    if (tet != NULL) {
	pos = tet->pos;
	rot = tet->rot;
	size = {BND_SIZE, BND_SIZE};
	tileTexCoords = getTexCoords((unsigned)tet->type);
    } else {
	size = {MAP_WIDTH, MAP_HEIGHT};
    }
    unsigned block;

    for (int y = 0; y < size.y; y++) {
	for (int x = 0; x < size.x; x++) {
	    block = grid[y * size.x + x];
	    if (tet == NULL) {
		if (x != 0 && x != size.x - 1)
		    tileTexCoords = getTexCoords(block);
		else
		    continue;
	    }
	    if (((block >> rot) & 1) != 0 ||
		(tet == NULL && block)) {
		{
		    sp->use();

		    glm::mat4 M = glm::mat4(1.f);
		    
		    M = glm::scale(M, glm::vec3(1.f / SCALE, 1.f / SCALE, 1.f / SCALE));
		    M = glm::translate(M, glm::vec3(
			2 * (float)(pos.x + x - x_shift),
			2 * (float)(pos.y - y + y_shift), 
			(float)pos.z));

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
		}
	    }
	}
    }
    free(tileTexCoords);
}
