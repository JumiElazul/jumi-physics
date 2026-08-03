#pragma once
#include "vector.hpp"
#include <cmath>
#include <raylib.h>

struct transform {
    vec2 current;
    vec2 previous;

    vec2 interpolated(float t) const {
        return {
            std::lerp(previous.x, current.x, t),
            std::lerp(previous.y, current.y, t),
        };
    }

    void save() { previous = current; }
    void place(vec2 p) { current = previous = p; }
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
