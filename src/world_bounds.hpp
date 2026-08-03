#pragma once
#include "vector.hpp"

struct world_bounds {
    float min_x;
    float min_y;
    float max_x;
    float max_y;

    constexpr float width() const noexcept { return max_x - min_x; }
    constexpr float height() const noexcept { return max_y - min_y; }
    constexpr vec2 size() const noexcept { return vec2(width(), height()); }

    constexpr vec2 center() const noexcept {
        return vec2((min_x + max_x) * 0.5f, (min_y + max_y) * 0.5f);
    }

    constexpr bool contains(vec2 point) const {
        return point.x >= min_x && point.x <= max_x && point.y >= min_y && point.y <= max_y;
    }
};
