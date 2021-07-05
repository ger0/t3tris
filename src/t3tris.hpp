#pragma once

// map definitions
#define MAP_WIDTH 10
#define MAP_HEIGH 20

// tetromino boundary 
#define BND_SIZE 5

// position on the map 
struct Position {
    int x;
    int y;
};

// different shapes for tetrominos
enum TET_TYPE {
    O,
    I,
    L,
    J,
    S,
    Z,
    T
};

// 1 - cell, 2 - center of rotation
namespace tetromino {
    // O shape shouldn't rotate at all
    const int O[BND_SIZE * BND_SIZE] = {
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 1, 1, 0,
	0, 0, 1, 1, 0,
	0, 0, 0, 0, 0
    };
    const int I[BND_SIZE * BND_SIZE] = {
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 1, 2, 1, 1,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0
    };
    const int L[BND_SIZE * BND_SIZE] = {
	0, 0, 0, 0, 0,
	0, 0, 1, 0, 0,
	1, 1, 2, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0
    };
    const int J[BND_SIZE * BND_SIZE] = {
	0, 0, 0, 0, 0,
	0, 0, 1, 0, 0,
	0, 0, 2, 1, 1,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0
    };
    const int S[BND_SIZE * BND_SIZE] = {
	0, 0, 0, 0, 0,
	0, 1, 0, 0, 0,
	0, 1, 2, 0, 0,
	0, 0, 1, 0, 0,
	0, 0, 0, 0, 0
    };
    const int Z[BND_SIZE * BND_SIZE] = {
	0, 0, 0, 0, 0,
	0, 0, 0, 1, 0,
	0, 0, 2, 1, 0,
	0, 0, 1, 0, 0,
	0, 0, 0, 0, 0
    };
    const int T[BND_SIZE * BND_SIZE] = {
	0, 0, 0, 0, 0,
	0, 0, 1, 0, 0,
	0, 1, 2, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0
    };
}

