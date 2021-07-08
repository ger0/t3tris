#pragma once

// default window size
#define WND_WIDTH	500
#define WND_HEIGHT	1000

// map definitions
#define MAP_WIDTH 10
#define MAP_HEIGHT 20

#define PI 3.141592653589793

// tetromino boundary 
#define BND_SIZE 4

// position on the map 
struct Position {
    int x;
    int y;
};

// different shapes for tetrominos
enum T_type {
    O,
    I,
    L,
    J,
    S,
    Z,
    T
};
// stores information about tetrominos during gameplay
struct tetromino {
    T_type	type;
    int		data[BND_SIZE * BND_SIZE];	
};
// 4 bits are used - 1 bit for every rotation 
// Will be removed later on
namespace t_types {
    // O shape shouldn't rotate at all
    const int O[BND_SIZE * BND_SIZE] = {
	0, 0,  0,  0,
	0, 15, 15, 0,
	0, 15, 15, 0,
	0, 0,  0,  0
    };
    const unsigned char I[BND_SIZE * BND_SIZE] = {
	0, 8,  2, 0,
	1, 9,  3, 1,
	4, 12, 6, 4,
	0, 8,  2, 0
    };
    const unsigned char L[BND_SIZE * BND_SIZE] = {
	8, 10, 1, 0,
	5, 15, 5, 0,
	4, 10, 2, 0,
	0, 0,  0, 0
    };
    const unsigned char J[BND_SIZE * BND_SIZE] = {
	1, 10, 2, 0,
	5, 15, 5, 0,
	8, 10, 4, 0,
	0, 0,  0, 0
    };
    const unsigned char Z[BND_SIZE * BND_SIZE] = {
	1,  9,  2, 0,
	12, 15, 3, 0,
	8,  6,  4, 0,
	0,  0,  0, 0
    };
    const unsigned char S[BND_SIZE * BND_SIZE] = {
	8, 3,  1, 0,
	9, 15, 6, 0,
	4, 12, 2, 0,
	0, 0,  0, 0
    };
    const unsigned char T[BND_SIZE * BND_SIZE] = {
	 0, 11, 0, 0,
	13, 15, 7, 0,
	 0, 14, 0, 0,
	 0, 0,  0, 0
    };
}

