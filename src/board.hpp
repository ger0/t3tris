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
    extern byte data[MAP_WIDTH * MAP_HEIGHT];
    void	initMap();
    bool	chkCollision(Tetromino &tet, Position mov, int rot);
    void	pushPiece(Tetromino &tet);
}

// draws a grid of dim dimensions
void drawGrid(GLFWwindow *wnd, ShaderProgram *sp, 
		byte grid[], Position pos, int rot, Position dim);
