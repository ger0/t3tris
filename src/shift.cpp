#include "shift.hpp"

Shift shiftDir = None;

bool canShiftDown = false; 
bool canShift 	  = false;

int gameCycles = 100;

// TODO maybe change this?
unsigned cycles		= 0;
unsigned dasCycles	= 0;
unsigned arrCycles	= 0;
unsigned downCycles	= 0;
unsigned stuckCycles	= 0;

unsigned clearedLines 	= 0;

/*
void shiftDown(Tetromino &curr) {
    map::chkCollision(curr, {0, -1}, 0);
}
*/
bool shiftDown(Pack *curr) {
    if (curr->move(Position{0, -1, 0})) {
	return false;
    } else {
	return true;
    }
}

/*
void shiftPiece(Tetromino &curr) {
    if (shiftDir == Left)
	map::chkCollision(curr, {-1, 0, 0}, 0);
    else if (shiftDir == Right)
	map::chkCollision(curr, {1, 0, 0}, 0);
    else if (shiftDir == Far)
	map::chkCollision(curr, {0, 0, 1}, 0);
    else if (shiftDir == Close)
	map::chkCollision(curr, {0, 0, -1}, 0);
}
*/
void shiftPiece(Pack *curr) {
    if (shiftDir == Left)
	curr->move(Position{-1, 0, 0});
    else if (shiftDir == Right)
	curr->move(Position{1, 0 , 0});
    else if (shiftDir == Far)
	curr->move(Position{0, 0 , 1});
    else if (shiftDir == Close)
	curr->move(Position{0, 0 , -1});
}
//
// ------------------------------------------------

void resetShift(Shift dir) {
    if (dir == Down) {
	canShiftDown = false;
    } else if (dir == shiftDir) {
	shiftDir = None;
	canShift = false;
    }
}

/*
void setShift(Shift dir, Tetromino &curr) {
    shiftDir = dir;
    shiftPiece(curr);
    canShift = false;

    arrCycles = 0;
    dasCycles = 0;
}
*/
void setShift(Shift dir, Pack *curr) {
    shiftDir = dir;
    shiftPiece(curr);
    canShift = false;

    arrCycles = 0;
    dasCycles = 0;
}

bool shiftUpdate(Pack *curr) {
    if (dasCycles >= DAS) {
	if (shiftDir != None && !canShift) {
	    canShift = true;
	}
	dasCycles = 0;
    }
    if (arrCycles >= ARR) {
	if (canShift) {
	    shiftPiece(curr);
	}
	arrCycles = 0;
    }
    if (downCycles >= gameCycles / SDF && canShiftDown) {
	shiftDown(curr);
	downCycles = 0;
    }
    dasCycles++;
    arrCycles++;
    downCycles++;
    cycles++;

    if (clearedLines == 10) {
	gameCycles -= 5;
	clearedLines = 0;
    }
    if (cycles > (unsigned)gameCycles) {
	if (shiftDown(curr)) {
	    if (stuckCycles >= 2) {
		curr->pushPiece();
		stuckCycles = 0;
		clearedLines++;
		return true;
	    } else {
		stuckCycles++;
	    }
	} else {
	    stuckCycles = 0;
	}
	cycles = 0;
    }
    return false;
}

/*
bool shiftUpdate(Tetromino &curr) {
    if (dasCycles >= DAS) {
	if (shiftDir != None && !canShift) {
	    canShift = true;
	}
	dasCycles = 0;
    }
    if (arrCycles >= ARR) {
	if (canShift) {
	    shiftPiece(curr);
	}
	arrCycles = 0;
    }
    if (downCycles >= gameCycles / SDF && canShiftDown) {
	shiftDown(curr);
	downCycles = 0;
    }
    dasCycles++;
    arrCycles++;
    downCycles++;
    cycles++;

    if (clearedLines == 10) {
	gameCycles -= 5;
	clearedLines = 0;
    }
    if (cycles > (unsigned)gameCycles) {
	if (map::chkCollision(curr, {0, -1}, 0)) {
	    if (stuckCycles >= 2) {
		map::pushPiece(curr);
		stuckCycles = 0;
		clearedLines++;
		return true;
	    } else 
		stuckCycles++;
	} else
	    stuckCycles = 0;
	cycles = 0;
    }
    return false;
}
*/

void setShiftDown() {
    canShiftDown = true;
}
