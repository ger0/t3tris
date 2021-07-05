#pragma once

#include "t3tris.hpp"

// TO DO: move to a different header
struct tetromino {
    TET_TYPE	type;
    int		data[BND_SIZE * BND_SIZE];	
};

bool chkCollision(tetromino &tet) {
    for (unsigned y = 0; y < MAP_HEIGH; y++) {
	for (unsigned x = 0; x < MAP_WIDTH; x++) {
	    if (tet.data[MAP_HEIGH * y + x] != 0 
		    && board[MAP_HEIGH * y + x] != 0) {
		return true
	    }
	}
    }
    return false;
}

namespace map {
    int board[MAP_WIDTH * MAP_HEIGHT] = { 0 };
}
