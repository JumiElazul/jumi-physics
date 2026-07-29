#pragma once
#include "types.hpp"
#include <raylib.h>

constexpr uint32_t MAX_COMPONENTS = 32;

struct transform {
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
};
