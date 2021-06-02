#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>

#include "shaderprogram.hpp"

float aspectRatio = 1;

ShaderProgram *sp;

int vertCount = 3;
float verts[] = {
    0.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f
};
float vertCol[] = {
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f
};

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

    sp->use();

    // set uniforms/ attributes
    //glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
    //glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));

    glEnableVertexAttribArray(sp->a("color"));
    glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, vertCol);

    glEnableVertexAttribArray(sp->a("vertex"));
    glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, verts);

    // draw
    glDrawArrays(GL_TRIANGLES, 0, vertCount);

    // disable attributes
    glDisableVertexAttribArray(sp->a("color"));
    glDisableVertexAttribArray(sp->a("vertex"));

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
