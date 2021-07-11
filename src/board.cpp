#include "board.hpp"

byte map::data[MAP_WIDTH * MAP_HEIGHT] = {0};

void map::initMap() {
    if (MAP_WIDTH) {
	for (unsigned i = 0; i < MAP_HEIGHT; i++) {
	    map::data[i * MAP_WIDTH] = 15;
	    map::data[i * MAP_WIDTH + MAP_WIDTH - 1] = 15;
	}
	for (unsigned i = 0; i < MAP_WIDTH; i++) {
	    map::data[i + MAP_WIDTH * (MAP_HEIGHT - 1)] = 15;
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
	    memcpy(temp, map::data, (y - 1) * MAP_WIDTH);
	    // copies data from lines above the removed line
	    memcpy(map::data + (MAP_WIDTH) * 2, temp, (y - 1) * MAP_WIDTH);
	}
    }
}

void map::pushPiece(Tetromino &tet) {
    for (unsigned y = 0; y < BND_SIZE; y++) {
	for (unsigned x = 0; x < BND_SIZE; x++) {
	    if (chkBND(tet, x, y)) {
		map::data[(y - tet.pos.y) * MAP_WIDTH + (x + tet.pos.x)] = (byte)tet.type;
		printf("dondon: %u \n", (byte)tet.type);
	    }
	}
    }
    lineCheck();
}

// todo: replace function
void drawGrid(GLFWwindow *wnd, ShaderProgram *sp, byte grid[],
		Position pos) {
    float x_shift = (MAP_WIDTH - 1) / 2.0f;
    float y_shift = (MAP_HEIGHT - 1) / 2.0f;

    for (int y = 0; y < MAP_HEIGHT; y++) {
	for (int x = 0; x < MAP_WIDTH; x++) {
	    glm::vec3 color(
		    (grid[y * MAP_WIDTH + x] % 1),
		    (grid[y * MAP_WIDTH + x] % 2),
		    (grid[y * MAP_WIDTH + x] % 3));
	    // replace
	    if (grid[y * MAP_WIDTH + x] != 0) {
		sp->use();

		glm::mat4 M = glm::mat4(1.f);
		
		M = glm::scale(M, glm::vec3(1.0f / MAP_WIDTH, 1.0f / MAP_HEIGHT, 1.f));
		M = glm::translate(M, glm::vec3(
		    2 * (float)(pos.x + x - x_shift),
		    2 * (float)(pos.y - y + y_shift), 0.f));

		glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

		//glEnableVertexAttribArray(sp->a("color"));
		//glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, vertCol);
		glUniform3fv(sp->u("color"), 1, glm::value_ptr(color));

		glEnableVertexAttribArray(sp->a("vertex"));
		glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, verts);

		// draw
		glDrawArrays(GL_TRIANGLES, 0, vertCount);

		// disable attributes
		glDisableVertexAttribArray(sp->a("color"));
		glDisableVertexAttribArray(sp->a("vertex"));
	    }
	}
    }
}

void drawGrid(GLFWwindow *wnd, ShaderProgram *sp, Tetromino &tet) {
    float x_shift = (MAP_WIDTH - 1) / 2.0f;
    float y_shift = (MAP_HEIGHT - 1) / 2.0f;

    for (int y = 0; y < BND_SIZE; y++) {
	for (int x = 0; x < BND_SIZE; x++) {
	    glm::vec3 color(
		    (tet.type % 1),
		    (tet.type % 2),
		    (tet.type % 3));
	    // replace
	    if (((tet.data[y * BND_SIZE + x] >> tet.rot) & 1) != 0) {
		sp->use();

		glm::mat4 M = glm::mat4(1.f);
		
		M = glm::scale(M, glm::vec3(1.0f / MAP_WIDTH, 1.0f / MAP_HEIGHT, 1.f));
		M = glm::translate(M, glm::vec3(
		    2 * (float)(tet.pos.x + x - x_shift),
		    2 * (float)(tet.pos.y - y + y_shift), 0.f));

		glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

		//glEnableVertexAttribArray(sp->a("color"));
		//glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, vertCol);
		glUniform3fv(sp->u("color"), 1, glm::value_ptr(color));

		glEnableVertexAttribArray(sp->a("vertex"));
		glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, verts);

		// draw
		glDrawArrays(GL_TRIANGLES, 0, vertCount);

		// disable attributes
		glDisableVertexAttribArray(sp->a("color"));
		glDisableVertexAttribArray(sp->a("vertex"));
	    }
	}
    }
}
