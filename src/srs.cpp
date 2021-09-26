#include "srs.hpp"

int extract(Rotation newRot, Rotation rot) {
    Rotation t = newRot + rot;
    t = t % 4;
    if (t.x > 0) { 
	return t.x;
    } else if (t.y > 0) {
	return t.y;
    } else {
	return t.z;
    }
}
Position negative(Position old) {
    return {-old.x, -old.y, -old.z};
}

Position getRotShift(Block b, unsigned i, Rotation newRot, Rotation rot) {
    int iter = extract(newRot, rot);
    Position retval;
    if (b == Block::I) {
	retval =  kick_data_I[i + TEST_COUNT * iter];
    } else if (b != Block::O) {
	retval = kick_data[i + TEST_COUNT * iter];
    } else {
	retval = {0, 0, 0};
    }
    if (newRot.isNegative()) {
	return retval;
    } else {
	return negative(retval);
    }
}
