#include "t3tris.hpp"
std::vector<glm::vec3> Pieces::O {
	glm::vec3(1, 1, 2),
	glm::vec3(2, 1, 2),
	glm::vec3(1, 2, 2),
	glm::vec3(2, 2, 2),
	glm::vec3(1, 2, 1),
	glm::vec3(2, 2, 1),
	glm::vec3(1, 1, 1),
	glm::vec3(2, 1, 1)
};
std::vector<glm::vec3> Pieces::I {
	glm::vec3(0, 2, 2),
	glm::vec3(1, 2, 2),
	glm::vec3(2, 2, 2),
	glm::vec3(3, 1, 2)
};
std::vector<glm::vec3> Pieces::L {
	glm::vec3(1, 2, 2),
	glm::vec3(2, 2, 2),
	glm::vec3(3, 2, 2),
	glm::vec3(3, 1, 2)
};
