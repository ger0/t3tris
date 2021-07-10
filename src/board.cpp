#include "board.hpp"

int map::board[MAP_WIDTH * MAP_HEIGHT] = {0};

bool map::chkCollision(Tetromino &tet) { 
    for (unsigned y = 0; y < MAP_HEIGHT; y++) {
	for (unsigned x = 0; x < MAP_WIDTH; x++) {
	    if (tet.data[MAP_HEIGHT * y + x] != 0 
		    && map::board[MAP_HEIGHT * y + x] != 0) {
		return true;
	    }
	}
    }
    return false;
}

void drawGrid(GLFWwindow *window, ShaderProgram *sp, unsigned char grid[],
		Position pos, int rot) {
    float x_shift = (MAP_WIDTH - 1) / 2.0f;
    float y_shift = (MAP_HEIGHT - 1) / 2.0f;

    for (int y = 0; y < BND_SIZE; y++) {
	for (int x = 0; x < BND_SIZE; x++) {
	    if (((grid[y * BND_SIZE + x] >> rot) & 1) != 0) {
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


