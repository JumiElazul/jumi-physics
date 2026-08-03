#pragma once
#include "system.hpp"
#include <raylib.h>

struct world_bounds;

class physics_system : public system {
public:
    void update(float step, const world_bounds& bounds);
};

class circle_render_system : public system {
public:
    void update(float alpha);
};

class rect_render_system : public system {
public:
    void update(float alpha);
};
