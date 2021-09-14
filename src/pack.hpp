#pragma once 

#include "t3tris.hpp"

#include <iostream>
#include <vector>

const int GR_WIDTH  = BND_SIZE;
const int GR_HEIGHT = BND_SIZE;
const int GR_DEPTH  = 3;


class Pack {
private:
    std::vector<Position>	cells;		// shape definition
public:
    // variables
    Position 			pos;		// current position
    Position 			nextPos;
    Position 			rotAnch;	// rotation anchor
    Block			type;		// type of the block 

    void update(); // updates grid on rotation 
    byte *grid;

    Pack(Position p, Block t, std::vector<Position> blocks);
    ~Pack();
    
    // size of the grid[]
    Dimensions size = {GR_WIDTH, GR_HEIGHT, GR_DEPTH};
    // debug 
    void print_pos();
};
