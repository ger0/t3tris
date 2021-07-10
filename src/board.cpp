#include "board.hpp"

byte map::data[MAP_WIDTH * MAP_HEIGHT] = {0};

void map::initMap() {
    if (MAP_WIDTH) {
	for (unsigned i = 0; i < MAP_HEIGHT; i++) {
	    map::data[i * MAP_WIDTH] = 15;
	    map::data[i * MAP_WIDTH + MAP_WIDTH - 1] = 15;
	}
    }
}

inline bool chkBND(Tetromino &tet, unsigned &x, unsigned &y, int rot = 0) {
    if ((tet.data[y * BND_SIZE + x] >> unsigned((tet.rot + rot) % 4)) & 1) {
	return true;
    }
    else 
	return false;
}

void map::chkCollision(Tetromino &tet, Position mov, int rot) { 
    bool isPossible = true;
    for (unsigned y = 0; y < BND_SIZE; y++) {
	for (unsigned x = 0; x < BND_SIZE; x++) {
	    if (chkBND(tet, x, y, rot)) {

		int coord = (y - (tet.pos.y + mov.y)) * MAP_WIDTH 
				+ x + tet.pos.x + mov.x;
		if (map::data[coord] != 0) {
		    //
		    printf("Collision at: %i\n", (y - (tet.pos.y + mov.y)) * MAP_WIDTH 
				    + (x + (tet.pos.x + mov.x)));
		    isPossible = false;
		}
	    }
	}
    }
    if (isPossible) {
	tet.pos.x += mov.x;
	tet.pos.y += mov.y;
	if (rot)
	    tet.rot = unsigned(tet.rot + rot) % 4;
    }
}

void map::pushPiece(Tetromino &tet) {
    for (unsigned y = 0; y < BND_SIZE; y++) {
	for (unsigned x = 0; x < BND_SIZE; x++) {
	    if (chkBND(tet, x, y)) {
		map::data[(y - tet.pos.y) * MAP_WIDTH + (x + tet.pos.x)] = 1;
	    }
	}
    }
}

// todo: replace function
void drawGrid(GLFWwindow *wnd, ShaderProgram *sp, byte grid[],
		Position pos, int rot, Position dim) {
    float x_shift = (MAP_WIDTH - 1) / 2.0f;
    float y_shift = (MAP_HEIGHT - 1) / 2.0f;

    for (int y = 0; y < dim.y; y++) {
	for (int x = 0; x < dim.x; x++) {
	    if (((grid[y * dim.x + x] >> rot) & 1) != 0) {
		sp->use();

		glm::mat4 M = glm::mat4(1.f);
		
		M = glm::scale(M, glm::vec3(1.0f / MAP_WIDTH, 1.0f / MAP_HEIGHT, 1.f));
		M = glm::translate(M, glm::vec3(
		    2 * (float)(pos.x + x - x_shift),
		    2 * (float)(pos.y - y + y_shift), 0.f));

		glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

		glEnableVertexAttribArray(sp->a("color"));
		glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, vertCol);

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


