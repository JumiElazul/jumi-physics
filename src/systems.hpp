#pragma once
#include "system.hpp"
#include <raylib.h>

class physics_system : public system {
public:
    void update(float step);
};

class circle_render_system : public system {
public:
    void update(float alpha);
};

class rect_render_system : public system {
public:
    void update(float alpha);
};
