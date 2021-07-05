#include "entity.hpp"

Entity::Entity(int x, int y) {
    pos = {x, y};
}
void Entity::draw(GLFWwindow *window, ShaderProgram *sp) {
    sp->use();

    M = glm::mat4(1.f);
   M = glm::translate(M, glm::vec3(
	       pos.x * 1.6f / CTRL::WIDTH - 0.8f,
	       pos.y * 1.6f / CTRL::HEIGHT - 0.8f, 0.f)); 
   M = glm::scale(M, glm::vec3(1.f / CTRL::WIDTH, 1.f / CTRL::HEIGHT, 1.f));

    glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

    glEnableVertexAttribArray(sp->a("color"));
    glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, vertCol);

    glEnableVertexAttribArray(sp->a("vertex"));
    glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, verts);

    // draw
    glDrawArrays(GL_TRIANGLES, 0, vertCount);
    
    // disable attributes
    glDisableVertexAttribArray(sp->a("color"));
    glDisableVertexAttribArray(sp->a("vertex"));
}

void Entity::update(int move, int rotat) {
    if (!(pos.x + move > CTRL::WIDTH ||
		pos.x + move < 0)) {
	pos.x += move;
    }
    angle += rotat * CTRL::PI;
}

bool Entity::tick() {
    if (pos.y - 1 >= 0) {
        pos.y -= 1;
	return true;
    } else 
	return false;
}

