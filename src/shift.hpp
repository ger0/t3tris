#pragma once

#include "t3tris.hpp"
#include "board.hpp"

extern unsigned gameCycles;

const unsigned DAS = 10;
const unsigned ARR = 2;
const unsigned SDF = 6;

enum Shift {
    Left	= -1,
    None	= 0,
    Right	= 1,
    Down	= 3
};

void resetShift(Shift dir);
void setShift(Shift dir, Tetromino &curr);
void shiftUpdate(Tetromino &curr);
void setShiftDown();
