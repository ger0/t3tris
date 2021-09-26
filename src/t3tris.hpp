#pragma once

#include <vector>
#include <glm/glm.hpp>

// map definitions
#define CELL_SIZE	64

#define MAP_WIDTH	10
#define MAP_HEIGHT	15
#define MAP_DEPTH	5

#define SCALE		10

// default window size
#define WND_WIDTH	CELL_SIZE * MAP_WIDTH
#define WND_HEIGHT	CELL_SIZE * MAP_HEIGHT

#define PI 3.141592653589793f

// tetromino boundary 
#define PIECES 7

typedef unsigned char byte;

// rounds a float
inline int round(float f) {
    return (int)(f + 0.5f);
}

class Pack;

// position on the map 
struct Position {
    int x;
    int y;
    int z = 0;

    Position operator+(Position a);
    Position operator%(int a);
    bool isNegative();
};

// for clarity
typedef Position Dimensions;

// different shapes for tetrominos
enum Block {
    EMPTY = 0,
    O = 1,
    I = 2,
    L = 3,
    J = 4,
    S = 5,
    Z = 6,
    T = 7,
    WALL = 8 
};
// 3D shapes
// hardcoded to a bounding box of size 5
namespace Pieces {
const std::vector<std::vector<glm::vec3>> piece {
    // O
    std::vector<glm::vec3> {
	glm::vec3(1, 1, 2),
	glm::vec3(2, 1, 2),
	glm::vec3(1, 2, 2),
	glm::vec3(2, 2, 2),
	glm::vec3(1, 2, 1),
	glm::vec3(2, 2, 1),
	glm::vec3(1, 1, 1),
	glm::vec3(2, 1, 1)
    },
    // I
    std::vector<glm::vec3> {
	glm::vec3(0, 3, 2),
	glm::vec3(1, 3, 2),
	glm::vec3(2, 3, 2),
	glm::vec3(3, 3, 2)
    },
    // L
    std::vector<glm::vec3> {
	glm::vec3(1, 2, 2),
	glm::vec3(2, 2, 2),
	glm::vec3(3, 2, 2),
	glm::vec3(3, 3, 2)
    },
    // J
    std::vector<glm::vec3> {
	glm::vec3(1, 2, 2),
	glm::vec3(1, 3, 2),
	glm::vec3(2, 2, 2),
	glm::vec3(3, 2, 2)
    },
    // Z
    std::vector<glm::vec3> {
	glm::vec3(1, 3, 2),
	glm::vec3(2, 3, 2),
	glm::vec3(2, 2, 2),
	glm::vec3(3, 2, 2)
    },
    // S
    std::vector<glm::vec3> {
	glm::vec3(1, 2, 2),
	glm::vec3(2, 2, 2),
	glm::vec3(2, 3, 2),
	glm::vec3(3, 3, 2)
    },
    // T
    std::vector<glm::vec3> {
	glm::vec3(1, 2, 2),
	glm::vec3(2, 2, 2),
	glm::vec3(2, 3, 2),
	glm::vec3(2, 2, 3)
    }
};
};
