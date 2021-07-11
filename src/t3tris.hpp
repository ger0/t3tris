#pragma once

// default window size
#define WND_WIDTH	500
#define WND_HEIGHT	1000

// map definitions
#define MAP_WIDTH	10
#define MAP_HEIGHT	20

#define PI 3.141592653589793

// tetromino boundary 
#define BND_SIZE 4
#define BND_AREA 16
#define PIECES 7

typedef unsigned char byte;

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
struct Tetromino {
    T_type	type;
    Position	pos;
    int		rot;
    byte	data[BND_AREA];	
};
// 4 bits are used - 1 bit for every rotation 
// Will be removed later on
const byte t_types[PIECES * BND_AREA] = {
    // O shape
	0, 0,  0,  0,
	0, 15, 15, 0,
	0, 15, 15, 0,
	0, 0,  0,  0, 
    // I shape
	0, 8,  2, 0,
	1, 9,  3, 1,
	4, 12, 6, 4,
	0, 8,  2, 0,
    // L shape
	8, 10, 1, 0,
	5, 15, 5, 0,
	4, 10, 2, 0,
	0, 0,  0, 0,
    // J shape
	1, 10, 2, 0,
	5, 15, 5, 0,
	8, 10, 4, 0,
	0, 0,  0, 0,
    // Z shape
	1,  9,  2, 0,
	12, 15, 3, 0,
	8,  6,  4, 0,
	0,  0,  0, 0,
    // S shape
	8, 3,  1, 0,
	9, 15, 6, 0,
	4, 12, 2, 0,
	0, 0,  0, 0,
    // T shape
	 0, 11, 0, 0,
	13, 15, 7, 0,
	 0, 14, 0, 0,
	 0, 0,  0, 0
};

