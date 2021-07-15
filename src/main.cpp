#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include "lodepng/lodepng.h"

#include "shaderprogram.hpp"
#include "shape.hpp"
#include "board.hpp"
#include "t3tris.hpp"
#include "srs.hpp"

ShaderProgram	*sp;
GLuint		tex;

Tetromino curr_piece;
Tetromino next_piece;

// td move outside main
void setPieces() {
    curr_piece = next_piece;

    unsigned var = rand() % PIECES;
    next_piece.type = T_type(var + 1);
    memcpy(next_piece.data, t_types + BND_AREA * var, BND_AREA);
    next_piece.pos = {(MAP_WIDTH - 1) / 2, 0};
    printf("NEXT PIECE: %i\n", next_piece.type);
}
// callbacks	-------------------------------------------------------
void errCallback(int error, const char* description) {
	fputs(description, stderr);
}
void windowResizeCallback(GLFWwindow* window, int width, int height) {
    if (height == 0)
	return;
    glViewport(0, 0, width, height);
}
void keyCallback(GLFWwindow* wnd, int key, int scancode, int act, int mod) {
    if (act == GLFW_PRESS) {
	// rotation
	if (key == GLFW_KEY_Z)
	    pieceRotate(curr_piece, -1);
	if (key == GLFW_KEY_UP)
	    pieceRotate(curr_piece, 1);
	if (key == GLFW_KEY_A)
	    map::chkCollision(curr_piece, {0, 0}, 2);

	// position
	if (key == GLFW_KEY_LEFT)
	    map::chkCollision(curr_piece, {-1, 0}, 0);
	if (key == GLFW_KEY_RIGHT)
	    map::chkCollision(curr_piece, {1, 0}, 0);
	if (key == GLFW_KEY_DOWN)
	    map::chkCollision(curr_piece, {0, -1}, 0);
	// hard drop
	if (key == GLFW_KEY_SPACE) {
	    while (!map::chkCollision(curr_piece, {0, -1}, 0));
	    map::pushPiece(curr_piece);
	    setPieces();
	}
	// debug
	/*
	if (key == GLFW_KEY_ENTER) {
	    map::pushPiece(curr_piece);
	    setPieces();
	}
	*/
    }
    if (act == GLFW_RELEASE) {
    }
}
GLuint readTexture(const char* filename) {
    GLuint tex0;
    glActiveTexture(GL_TEXTURE0);

    std::vector<byte> image;
    unsigned width, height;
    unsigned error = lodepng::decode(image, width, height, filename);
    if (error) {
	printf("Texture loading error: %u\n", error);
    }

    glGenTextures(1, &tex0);
    glBindTexture(GL_TEXTURE_2D, tex0);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, 
	    GL_RGBA, GL_UNSIGNED_BYTE, (byte*)image.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return tex0;
}
// --------------------------------------------------------------------
void initProgram(GLFWwindow* window) {
    // initialise the program
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 1);
    //glEnable(GL_DEPTH_TEST);

    glfwSetWindowSizeCallback(window, windowResizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    tex = readTexture("assets/tileset.png");
    sp = new ShaderProgram("src/vshad.glsl", "src/fshad.glsl");
    map::initMap();
}
void freeProgram() {
    // free shaders etc.
    delete sp;
}
// --------------------------------------------------------------------
void drawScene(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT);
    // z buffer will be needed later on

    drawGrid(sp, tex, map::data, {0, 0});
    drawGrid(sp, tex, curr_piece);

    // swap buffers
    glfwSwapBuffers(window);
}
int main() {
    srand(time(NULL));

    GLFWwindow* window;
    glfwSetErrorCallback(errCallback);
    if (!glfwInit()) {
	fprintf(stderr, "Cannot initialise GLFW.\n");
	exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(WND_WIDTH, WND_HEIGHT, "Tetris", NULL, NULL);
    if (!window) {
	fprintf(stderr, "Cannot create window.\n");
	glfwTerminate();
	exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glViewport(0,0,WND_WIDTH,WND_HEIGHT);

    if (glewInit() != GLEW_OK) {
	fprintf(stderr, "Cannot initialise GLEW.\n");
	exit(EXIT_FAILURE);
    }
    initProgram(window);
   
    auto time_step = glfwGetTime();

    // lol
    int temp = 0;
    setPieces();
    setPieces();

    // main game loop
    while (!glfwWindowShouldClose(window)) {
	glfwPollEvents();
	if (glfwGetTime() - time_step >= 0.10) {
	    time_step = glfwGetTime();
	}
	if (glfwGetTime() >= 0.75) {
	    time_step = 0;

	    if (temp == 1) {
		map::pushPiece(curr_piece);
		setPieces();
		temp = 0;
	    }
	    if (map::chkCollision(curr_piece, {0, -1}, 0)) {
		temp++;
	    }
	    glfwSetTime(0);
	}
	drawScene(window);
    }
    freeProgram();
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
