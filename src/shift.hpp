#pragma once

#include "t3tris.hpp"
#include "board.hpp"

const unsigned DAS = 9;
const unsigned ARR = 2;
const unsigned SDF = 7;

enum Shift {
    Down,
    None,
    Left,
    Right,
    Far,
    Close	
};

void resetShift(Shift dir);
void setShiftDown();

void setShift(Shift dir, Pack *curr);
bool shiftUpdate(Pack *curr);
