#include "t3tris.hpp"

Position Position::operator+(Position a) {
    return Position{
	this->x + a.x,
	this->y + a.y, 
	this->z + a.z
    };
}

// why?
Position Position::operator%(int a) {
    return Position{
	(int)((unsigned)(this->x) % a),
	(int)((unsigned)(this->y) % a), 
	(int)((unsigned)(this->z) % a)
    };
}
bool Position::isNegative() {
    if (this->x < 0 
	    || this ->y < 0 
	    || this -> z < 0) {
	return true;
    } else {
	return false;
    }
}
