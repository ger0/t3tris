#include "board.hpp"

byte map::data[MAP_WIDTH * MAP_HEIGHT] = {0};

void map::initMap() {
    if (MAP_WIDTH) {
	for (unsigned i = 0; i < MAP_HEIGHT; i++) {
	    map::data[i * MAP_WIDTH] = 8;
	    map::data[i * MAP_WIDTH + MAP_WIDTH - 1] = 8;
	}
	for (unsigned i = 0; i < MAP_WIDTH; i++) {
	    map::data[i + MAP_WIDTH * (MAP_HEIGHT - 1)] = 8;
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
		if (map::data[coord] != 0) {
		    return true;
		}
	    }
	}
    }
    tet.pos.x += mov.x;
    tet.pos.y += mov.y;
    if (rot)
	tet.rot = unsigned(tet.rot + rot) % 4;
    return false;
}

void lineCheck() {
    bool isFull;
    for (unsigned y = 0; y < (MAP_HEIGHT - 1); y++) {
	isFull = true;
	for (unsigned x = 0; x < MAP_WIDTH; x++) {
	    if (!map::data[y * MAP_WIDTH + x]) {
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
		    map::data[i] = 8;
		else 
		    map::data[i] = 0;
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

// TODO: get rid of this 
inline float* getTexCoords(unsigned type) {
    float *new_coords = (float*)malloc(sizeof(float) * 2 * vertCount);
    for (int i = 0; i < vertCount; i++) {
	new_coords[i * 2] = (texCoords[i * 2] + (int)type - 1) / (PIECES + 1);
	new_coords[i * 2 + 1] = texCoords[i * 2 + 1];
    }
    return new_coords;
}

// TODO: replace both drawGrid functions
void drawGrid(ShaderProgram *sp, GLuint tex, 
	    byte grid[], Position pos) {
    float x_shift = (MAP_WIDTH - 1) / 2.0f;
    float y_shift = (MAP_HEIGHT - 1) / 2.0f;

    float *tileTexCoords;

    for (int y = 0; y < MAP_HEIGHT; y++) {
	for (int x = 0; x < MAP_WIDTH; x++) {
	    tileTexCoords = getTexCoords((unsigned)grid[y * MAP_WIDTH + x]);
	    // replace
	    if (grid[y * MAP_WIDTH + x] != 0) {
		sp->use();

		glm::mat4 M = glm::mat4(1.f);
		
		M = glm::scale(M, glm::vec3(1.0f / MAP_WIDTH, 1.0f / MAP_HEIGHT, 1.f / MAP_WIDTH));
		M = glm::translate(M, glm::vec3(
		    2 * (float)(pos.x + x - x_shift),
		    2 * (float)(pos.y - y + y_shift), 0.f));

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
    free(tileTexCoords);
}

// draws tetromino
void drawGrid(ShaderProgram *sp, GLuint tex, Tetromino &tet) {
    float x_shift = (MAP_WIDTH - 1) / 2.0f;
    float y_shift = (MAP_HEIGHT - 1) / 2.0f;
    float *tileTexCoords = getTexCoords((unsigned)tet.type);

    for (int y = 0; y < BND_SIZE; y++) {
	for (int x = 0; x < BND_SIZE; x++) {
	    // replace
	    if (((tet.data[y * BND_SIZE + x] >> tet.rot) & 1) != 0) {
		sp->use();

		glm::mat4 M = glm::mat4(1.f);
		
		M = glm::scale(M, glm::vec3(1.0f / MAP_WIDTH, 1.0f / MAP_HEIGHT, 1.f / MAP_WIDTH));
		M = glm::translate(M, glm::vec3(
		    2 * (float)(tet.pos.x + x - x_shift),
		    2 * (float)(tet.pos.y - y + y_shift), 0.f));

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
    free(tileTexCoords);
}
