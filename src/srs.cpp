#include "srs.hpp"

inline Position getKickData(unsigned &i, Tetromino &tet, int &rot, const Position *data) {
    unsigned rotation = i + TEST_COUNT * (unsigned(tet.rot + rot) % ROTATIONS);
    if (rot >= 0) {
	return data[rotation];
    } else {
	return Position{-data[rotation].x, -data[rotation].y};
    }
}

void pieceRotate(Tetromino &tet, int rot) {
    unsigned i = 0;
    if (tet.type == I) {
	while (map::chkCollision(tet, 
		    getKickData(i, tet, rot, kick_data_I),
		    rot)) {
	    i++;
	}
    } else if (tet.type != O) {
	while (map::chkCollision(tet,
		    getKickData(i, tet, rot, kick_data),
		    rot)) {
	    i++;
	}
    }
}

