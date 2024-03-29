#include "board.hpp"

byte map::data[MAP_WIDTH * MAP_HEIGHT * MAP_DEPTH] = {Block::EMPTY};

inline unsigned getMapIndex(unsigned x, unsigned y, unsigned z) {
    return y * MAP_WIDTH + x + MAP_WIDTH * MAP_HEIGHT * z;
}

void map::initMap() {
    // temp
}

bool map::isColliding(Position pos) {
    if (pos.x >= MAP_WIDTH  || pos.x < 0 ||
	    pos.y >= MAP_HEIGHT || pos.y < 0 ||
	    pos.z >= MAP_DEPTH  || pos.z < 0) {
	/*
	printf("COLLISION: position outside map box, x: %i, y: %i, z: %i\n", 
		pos.x, pos.y, pos.z);
		*/
	return true;
    } else if (map::data[getMapIndex(pos.x, pos.y, pos.z)] != Block::EMPTY) {
	return true;
    } else {
	return false;
    }
}
// tutaj
void map::lineCheck() {
    bool isFull;
    byte temp[MAP_WIDTH * MAP_HEIGHT];
    for (unsigned y = MAP_HEIGHT - 1; y < UINT_MAX; y--) {
	isFull = true;
	for (unsigned z = 0; z < MAP_DEPTH; z++) {
	    for (unsigned x = 0; x < MAP_WIDTH; x++) {
		if (map::data[getMapIndex(x, y, z)] == Block::EMPTY) {
		    isFull = false;
		}
	    }
	}
	if (isFull) {
	    printf("full line\n");
	    for (unsigned z = 0; z < MAP_DEPTH; z++) {
		// copies data from lines above the removed line
		memcpy(
			temp, 
			map::data + z * MAP_HEIGHT * MAP_WIDTH, 
			MAP_HEIGHT * MAP_WIDTH
			);
		memcpy(
			map::data + y * MAP_WIDTH + z * MAP_HEIGHT * MAP_WIDTH,
			temp + (y + 1) * MAP_WIDTH,
			(MAP_HEIGHT - (y + 1)) * MAP_WIDTH
			);
		// free at the top of the map
		for (unsigned x = 0; x < MAP_WIDTH; x++) {
		    map::data[getMapIndex(x, MAP_HEIGHT - 1, z)] = Block::EMPTY;
		}
	    }
	}
    }
}

void map::pushPiece(Block b, Position pos) {
    map::data[getMapIndex(pos.x, pos.y, pos.z)] = (byte)b;
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
	    byte grid[], Pack *p) {
    float x_shift = (MAP_WIDTH 	- 1) / 2.0f;
    float y_shift = (MAP_HEIGHT - 1) / 2.0f;
    float z_shift = (MAP_DEPTH  - 1) / 2.0f;
    bool sh_free = false;

    float *tileTexCoords;

    Position pos = {0, 0, 0};
    // size of bounding box
    Dimensions size;
    if (p != NULL) {
	pos	= p->pos;
	size	= p->size;
	tileTexCoords = getTexCoords(p->type);
    } else {
	size = Dimensions{MAP_WIDTH, MAP_HEIGHT, MAP_DEPTH};

	sh_free = true;
    }
    unsigned block;

    for (int z = 0; z < size.z; z++) {
	for (int y = 0; y < size.y; y++) {
	    for (int x = 0; x < size.x; x++) {
		block = grid[(y * size.x + x) + size.x * size.y * z];
		if (block != 0) {
		    if (p == NULL) {
			tileTexCoords = getTexCoords(block);
		    }
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
		    if (sh_free) {
			free(tileTexCoords);
		    }
		}
	    }
	}
    }
    if (!sh_free) {
	free(tileTexCoords);
    }
}
