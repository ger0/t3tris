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
#include "shift.hpp"
#include "pack.hpp"

ShaderProgram	*sp;
GLuint		tex;
// funky camera
glm::vec3 cameraPos = glm::vec3(0.f, 0.f, 5.f);

// debug
Pack *pack = NULL;
Pack *next = NULL;

Pack *buff = NULL;

// mouse 
float pitch = 0.0f, yaw = 0.0f;
float lastX = 400, lastY = 350;

// temp
bool canSwap = true;

// sets current / next piece 
void setPieces() {
    // fresh start 
    unsigned var = rand() % PIECES;
    if (pack == NULL) {
	next = new Pack(Block(var + 1), Pieces::piece[var]);	
	var = rand() % PIECES;
	pack = new Pack(Block(var + 1), Pieces::piece[var]);
    } else {
	delete pack;
	pack = next;
	next = new Pack(Block(var + 1), Pieces::piece[var]);
    }
    printf("NEXT PIECE: %u\n", var + 1);
    canSwap = true;
}
// callbacks	-------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.005f;
    xoffset *= sensitivity;
    yoffset *= sensitivity; 
    yaw -= xoffset;
    pitch += yoffset;
}
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
	// srs rotation
	if (key == GLFW_KEY_Z) {
	    pack->rotate(glm::vec3(0,0,1));
	}
	if (key == GLFW_KEY_UP) {
	    pack->rotate(glm::vec3(0,0,-1));
	}
	if (key == GLFW_KEY_S) {
	    pack->rotate(glm::vec3(1,0,0));
	}
	if (key == GLFW_KEY_X) {
	    pack->rotate(glm::vec3(-1,0,0));
	}

	// shift - position
	if (key == GLFW_KEY_LEFT) {
	    setShift(Left, pack);
	    //pack->move(Position{-1,0,0});
	}
	if (key == GLFW_KEY_RIGHT) {
	    setShift(Right, pack);
	    //pack->move(Position{1,0,0});
	}
	if (key == GLFW_KEY_Q) {
	    setShift(Far, pack);
	    //pack->move(Position{0,0,1});
	}
	if (key == GLFW_KEY_W) {
	    setShift(Close, pack);
	    //pack->move(Position{0,0,-1});
	}
	if (key == GLFW_KEY_DOWN) {
	    setShiftDown();
	    //pack->move(Position{0,-1,0});
	}
	// hard drop
	if (key == GLFW_KEY_SPACE) {
	    while (pack->move(Position{0,-1,0}));
	    pack->pushPiece();
	    setPieces();
	}
	// buffer swapping 
	if (key == GLFW_KEY_LEFT_SHIFT) {
	    if (canSwap) {
		if (buff == NULL) {
		    buff = pack;
		    setPieces();
		} else {
		    pack->resetPos();
		    Pack *temp = pack;
		    pack = buff;
		    buff = temp;
		}
	    canSwap = false;
	    }
	}
	if (key == GLFW_KEY_ENTER) {
	    pack->pushPiece();
	}
    }
    if (act == GLFW_RELEASE) {
	if (key == GLFW_KEY_LEFT) {
	    resetShift(Left);
	}
	if (key == GLFW_KEY_RIGHT) {
	    resetShift(Right);
	}
	if (key == GLFW_KEY_W) {
	    resetShift(Close);
	}
	if (key == GLFW_KEY_Q) {
	    resetShift(Far);
	}
	if (key == GLFW_KEY_DOWN) {
	    resetShift(Down);
	}
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

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return tex0;
}
// --------------------------------------------------------------------
void initProgram(GLFWwindow* window) {
    // initialise the program
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glm::mat4 V = 
	    glm::lookAt(
		cameraPos,
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
    V = glm::rotate(V, yaw, glm::vec3(0.0f, 1.0f, 0.0f));
    V = glm::rotate(V, pitch, glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 P = 
	glm::perspective(50.0f * (float)PI / 180.0f,
		(float)MAP_WIDTH / (float)MAP_HEIGHT, 0.01f, 50.0f);
    
    glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
    glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix3fv(sp->u("cameraPos"), 1, false, glm::value_ptr(cameraPos));

    drawGrid(sp, tex, pack->grid, pack);
    drawGrid(sp, tex, map::data);
    
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
   
    setPieces();

    double time_after	= glfwGetTime();
    double time_before	= glfwGetTime();
    double timer	= time_after;
    double delta	= 0;

    double time_cap = 1.0 / 60.0;
    //
    // main game loop
    while (!glfwWindowShouldClose(window)) {
	time_after = glfwGetTime();
	delta += (time_after - time_before) / time_cap;
	time_before = time_after;

	glfwPollEvents();
	while (delta >= 1.0) { 
	    // update board
	    if (shiftUpdate(pack)) {
		setPieces();
	    }
	    delta--;
	}
	drawScene(window);
	if (glfwGetTime() - timer > 1.0) {
            timer++;
        }
    }
    freeProgram();
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
