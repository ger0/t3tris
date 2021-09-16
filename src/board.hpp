#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "t3tris.hpp"
#include "shape.hpp"
#include "pack.hpp"
#include "shaderprogram.hpp"

namespace map {
    extern byte data[MAP_WIDTH * MAP_HEIGHT * MAP_DEPTH];
    void	initMap();
    bool	isColliding(Position pos);
    void	pushPiece(Block b, Position pos);

    void	pushPiece(Tetromino &tet);
    bool	chkCollision(Tetromino &tet, Position mov, int rot);
}

// draws a grid 
void drawGrid(ShaderProgram *sp, GLuint tex, byte grid[],
	Tetromino *tet = NULL, Pack *p = NULL);
