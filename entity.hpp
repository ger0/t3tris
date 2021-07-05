#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "constants.hpp"
#include "shaderprogram.hpp"

struct Position {
    int x;
    int y;
};

class Entity {
private:
    Position pos = {0, 0};
    float angle = 0.f;
    // model matrix
    glm::mat4 M = glm::mat4(1.0f);

    const static int vertCount = 6;
    const float verts[4 * vertCount] = {
	// first
	-0.5f, -0.5f, 0.f, 1.f,
	0.5f, -0.5f, 0.f, 1.f,
	0.5f, 0.5f, 0.f, 1.f,
	// second
	-0.5f, -0.5f, 0.f, 1.f,
	0.5f, 0.5f, 0.f, 1.f,
	-0.5f, 0.5f, 0.f, 1.f
    };
    const float vertCol[4 * vertCount] = {
	1.f, 1.f, 1.f, 1.f,
	1.f, 1.f, 1.f, 1.f,
	1.f, 1.f, 1.f, 1.f,

	1.f, 1.f, 1.f, 1.f,
	1.f, 1.f, 1.f, 1.f,
	1.f, 1.f, 1.f, 1.f
    };
public:
    void draw(GLFWwindow *window, ShaderProgram *sp);
    void update(int move, int rotat);
    bool tick();
    Entity(int x, int y);
};
