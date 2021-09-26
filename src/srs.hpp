#pragma once

#include "t3tris.hpp"
#include <cstdio>

#define TEST_COUNT	5
#define ROTATIONS	4

// J, L, S, T, Z Tetromino Wall Kick Data (x, y)
// 0 > 1 is just -(1 > 0)
typedef Position Rotation;

const Position kick_data[] = {
//  test1	  test2		  test3		  test4		  test5
    {0, 0}, 	 {-1, 0}, 	 {-1, 1}, 	  {0,-2}, 	 {-1,-2}, // 0 > 1
    {0, 0}, 	  {1, 0}, 	  {1,-1}, 	  {0, 2}, 	  {1, 2}, // 1 > 2
    {0, 0}, 	  {1, 0}, 	  {1, 1}, 	  {0,-2}, 	  {1,-2}, // 2 > 3
    {0, 0}, 	 {-1, 0}, 	 {-1,-1}, 	  {0, 2}, 	 {-1, 2}  // 3 > 0
};

// I Tetromino Wall Kick data (x, y)
const Position kick_data_I[] = {
//  test1	  test2		  test3		  test4		  test5
    {0, 0}, 	 {-2, 0}, 	  {1, 0}, 	 {-2,-1}, 	  {1, 2}, // 0 > 1
    {0, 0}, 	 {-1, 0}, 	  {2, 0}, 	 {-1, 2}, 	  {2,-1}, // 1 > 2
    {0, 0}, 	  {2, 0}, 	 {-1, 0}, 	  {2, 1}, 	 {-1,-2}, // 2 > 3
    {0, 0}, 	  {1, 0}, 	 {-2, 0}, 	  {1,-2}, 	 {-2, 1}  // 3 > 0
};

//void pieceRotate(Tetromino &tet, int rot);
// i?
Position getRotShift(Block b, unsigned i, Rotation newRot, Rotation rot);
