#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

float aspectRatio = 1;

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
    }
    if (act == GLFW_RELEASE) {
    }
}
// --------------------------------------------------------------------
void initProgram(GLFWwindow* window) {
    // initialise the program
    glClearColor(0, 0, 0, 1);
    //glEnable(GL_DEPTH_TEST);
    glfwSetWindowSizeCallback(window, windowResizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    // textures later on...
}
void freeProgram(GLFWwindow* window) {
    // free shaders etc.
}
// --------------------------------------------------------------------
void drawScene(GLFWwindow* window) {
    // draw a frame
    glClear(GL_COLOR_BUFFER_BIT);
    // z buffer will be needed later on
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

    if (glewInit() != GLEW_OK) {
	fprintf(stderr, "Cannot initialise GLEW.\n");
	exit(EXIT_FAILURE);
    }
    initProgram(window);
    
    while (!glfwWindowShouldClose(window)) {
	// main game loop
	drawScene(window);
	glfwPollEvents();
    }

    freeProgram(window);
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
