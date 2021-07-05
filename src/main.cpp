#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

#include "shaderprogram.hpp"
#include "shape.hpp"
#include "entity.hpp"
#include "t3tris.hpp"

float aspectRatio = 1;

int move = 0;
int rotation = 0;

ShaderProgram *sp;

// callbacks	-------------------------------------------------------
void errCallback(int error, const char* description) {
	fputs(description, stderr);
}
void windowResizeCallback(GLFWwindow* window, int width, int height) {
    if (height == 0)
	return;
    float aspectRatio = (float)width / float(height);
    glViewport(0, 0, width, height);
}
void keyCallback(GLFWwindow* wnd, int key, int scancode, int act, int mod) {
    if (act == GLFW_PRESS) {
	if (key == GLFW_KEY_Z)	rotation = -1;	
	if (key == GLFW_KEY_UP)	rotation = 1;	

	if (key == GLFW_KEY_LEFT)	move = -1;	
	if (key == GLFW_KEY_RIGHT)	move = 1;	
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
    sp = new ShaderProgram("vshad.glsl", "fshad.glsl");
}
void freeProgram(GLFWwindow* window) {
    // free shaders etc.
    delete sp;
}
// --------------------------------------------------------------------
void drawScene(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT);
    // z buffer will be needed later on
    // swap buffers
    glfwSwapBuffers(window);
}
int main() {
    GLFWwindow* window;
    glfwSetErrorCallback(errCallback);
    if (!glfwInit()) {
	fprintf(stderr, "Cannot initialise GLFW.\n");
	exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(800, 800, "Tetris", NULL, NULL);
    if (!window) {
	fprintf(stderr, "Cannot create window.\n");
	glfwTerminate();
	exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glViewport(0,0,800,800);

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

	    move = 0;
	    rotation = 0;
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
