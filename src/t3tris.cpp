#include "t3tris.hpp"
const std::vector<std::vector<glm::vec3>> Pieces::piece {
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
	glm::vec3(0, 2, 2),
	glm::vec3(1, 2, 2),
	glm::vec3(2, 2, 2),
	glm::vec3(3, 2, 2)
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
	glm::vec3(2, 1, 2),
	glm::vec3(2, 2, 3)
    }
};
