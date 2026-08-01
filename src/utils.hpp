#pragma once
#include <cstdlib>
#include <random>
#include <raylib.h>

inline std::mt19937& global_rng() {
    static thread_local std::mt19937 engine{std::random_device{}()};
    return engine;
}

inline float random_number(float min, float max) {
    std::uniform_real_distribution dist(min, max);
    return dist(global_rng());
}

inline int random_number(int min, int max) {
    std::uniform_int_distribution dist(min, max);
    return dist(global_rng());
}

inline Color random_color(int low = 0, int high = 255) {
    return Color(random_number(low, high), random_number(low, high), random_number(low, high), 255);
}
