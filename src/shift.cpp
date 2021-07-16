#include "shift.hpp"

Shift shiftDir = None;

bool canShiftDown = false; 
bool canShift 	  = false;

unsigned gameCycles = 20;

unsigned dasCycles = 0;
unsigned arrCycles = 0;
unsigned cycles	   = 0;

void shiftDown(Tetromino &curr) {
    map::chkCollision(curr, {0, -1}, 0);
}

void shiftPiece(Tetromino &curr) {
    map::chkCollision(curr, {shiftDir, 0}, 0);
}
//
// ------------------------------------------------

void resetShift(Shift dir) {
    if (dir == shiftDir) {
	shiftDir = None;
	canShift = false;
    } if (dir == Down) {
	canShiftDown = false;
    }
}

void setShift(Shift dir, Tetromino &curr) {
    shiftDir = dir;
    shiftPiece(curr);
    canShift = false;

    arrCycles = 0;
    dasCycles = 0;
}

void shiftUpdate(Tetromino &curr) {
    if (dasCycles > DAS) {
	if (shiftDir != None && !canShift) {
	    canShift = true;
	}
	dasCycles = 0;
    }
    if (arrCycles > ARR) {
	if (canShift != None) {
	    shiftPiece(curr);
	}
	arrCycles = 0;
    }
    if (cycles >= gameCycles / SDF && canShiftDown) {
	shiftDown(curr);
	cycles = 0;
    }

    dasCycles++;
    arrCycles++;
    cycles++;
}

void setShiftDown() {
    canShiftDown = true;
}
