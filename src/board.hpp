#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "t3tris.hpp"
#include "shape.hpp"
#include "shaderprogram.hpp"

namespace map {
    extern int	board[MAP_WIDTH * MAP_HEIGHT];
    bool	chkCollision(Tetromino &tet);
}

//Position rotate(int grid[], int size, float angle);

void drawGrid(GLFWwindow *window, ShaderProgram *sp, 
		unsigned char grid[], Position pos, int rot);
