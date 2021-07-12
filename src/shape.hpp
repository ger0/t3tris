#pragma once 

// 1 CELL for now
const static int vertCount = 6;
const float verts[4 * vertCount] = {
    // first
    -1.0f, -1.0f, 0.f, 1.f,
     1.0f, -1.0f, 0.f, 1.f,
     1.0f,  1.0f, 0.f, 1.f,
    // second
    -1.0f, -1.0f, 0.f, 1.f,
     1.0f,  1.0f, 0.f, 1.f,
    -1.0f,  1.0f, 0.f, 1.f
};
const float vertCol[4 * vertCount] = {
    1.f, 1.f, 1.f, 1.f,
    1.f, 1.f, 1.f, 1.f,
    1.f, 1.f, 1.f, 1.f,

    1.f, 1.f, 1.f, 1.f,
    1.f, 1.f, 1.f, 1.f,
    1.f, 1.f, 1.f, 1.f
};
const float texCoords[2 * vertCount] = {
    // first
     0.0f,  0.0f,
     1.0f,  0.0f,
     1.0f,  1.0f,
    // second
     0.0f,  0.0f,
     1.0f,  1.0f,
     0.0f,  1.0f
};
