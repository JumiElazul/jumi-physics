#pragma once
#include <raylib.h>

struct transform {
    float x;
    float y;
};

struct velocity {
    float dx;
    float dy;
};

struct circle_shape {
    float radius;
    Color color;
};

struct rect_shape {
    float width;
    float height;
    Color color;
};
