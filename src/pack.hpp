#pragma once 

#include "t3tris.hpp"
#include "board.hpp"

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const int GR_WIDTH  = 5;
const int GR_HEIGHT = 5;
const int GR_DEPTH  = 5;


class Pack {
private:
    std::vector<glm::vec3>	cells;		// shape definition
    glm::vec3 			rotPivot;	// rotation pivot around the middle of the bounding box
public:
    // variables
    Position 			pos;		// current position
    Block			type;		// type of the block 

    void update(); // updates grid on rotation 
    void rotate(glm::vec3 rot); 		// rotates all positions of the cells
    bool move(Position add_pos);		// moves to a certain position
    byte *grid;

    Pack(Position p, Block t, std::vector<glm::vec3> b);
    ~Pack();
    
    // size of the grid[]
    Dimensions size = {GR_WIDTH, GR_HEIGHT, GR_DEPTH};
    // debug 
    void print_pos();
};
