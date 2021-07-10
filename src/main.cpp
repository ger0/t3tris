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

#include "shaderprogram.hpp"
#include "shape.hpp"
#include "board.hpp"
#include "t3tris.hpp"

int move = 0;
int hmov = 0;
int rotation = 0;

ShaderProgram *sp;

Tetromino curr_piece;
Tetromino next_piece;

void setPiece(Tetromino &piece) {
    unsigned var = rand() % PIECES;
    piece.type = T_type(var);
    memcpy(piece.data, t_types + BND_AREA * var, BND_AREA);
    printf("%i\n", piece.type);
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
	if (key == GLFW_KEY_Z)	rotation = unsigned(rotation - 1) % 4;	
	if (key == GLFW_KEY_UP)	rotation = (rotation + 1) % 4;	

	if (key == GLFW_KEY_ENTER) {
	    setPiece(curr_piece);
	}

	if (key == GLFW_KEY_LEFT)	move += -1;	
	if (key == GLFW_KEY_RIGHT)	move += 1;	

	//if (key == GLFW_KEY_UP)		hmov += 1;	
	if (key == GLFW_KEY_DOWN)	hmov += -1;	
    }
    if (act == GLFW_RELEASE) {
    }
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
    // textures later on...
    sp = new ShaderProgram("src/vshad.glsl", "src/fshad.glsl");
}
void freeProgram(GLFWwindow* window) {
    // free shaders etc.
    delete sp;
}
// --------------------------------------------------------------------
void drawScene(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT);
    // z buffer will be needed later on

    drawGrid(window, sp, curr_piece.data, {0 + move, 0 + hmov}, rotation);

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

    // main game loop
    while (!glfwWindowShouldClose(window)) {
	glfwPollEvents();
	if (glfwGetTime() - time_step >= 0.05) {
	    time_step = glfwGetTime();
	    
	    //move = 0;
	}
	if (glfwGetTime() >= 1) {
	    time_step = 0;
	    glfwSetTime(0);
	}
	drawScene(window);
    }

    freeProgram(window);
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
