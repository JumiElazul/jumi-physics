#pragma once
#include <cassert>
#include <cmath>

struct vec2 {
    float x;
    float y;

    constexpr float magnitude() const noexcept { return std::sqrt(x * x + y * y); }
    constexpr vec2 normalized() const noexcept { return vec2(x / magnitude(), y / magnitude()); }
    constexpr void normalize() noexcept {
        float mag = magnitude();
        x /= mag;
        y /= mag;
    }

    constexpr vec2& operator+=(vec2 other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    constexpr vec2& operator-=(vec2 other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    constexpr vec2& operator*=(vec2 other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    constexpr vec2& operator/=(vec2 other) {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    static constexpr float dot(vec2 a, vec2 b) { return a.x * b.x + a.y * b.y; }

    static constexpr vec2 interpolated(vec2 a, vec2 b, float t) {
        return {
            std::lerp(a.x, b.x, t),
            std::lerp(a.y, b.y, t),
        };
    }

    static constexpr vec2 up() { return vec2(0.0f, 1.0f); }
    static constexpr vec2 down() { return vec2(0.0f, -1.0f); }
    static constexpr vec2 left() { return vec2(-1.0f, 0.0f); }
    static constexpr vec2 right() { return vec2(1.0f, 0.0f); }
};

constexpr vec2 operator+(vec2 a, vec2 b) {
    return vec2(a.x + b.x, a.y + b.y);
}

constexpr vec2 operator-(vec2 a, vec2 b) {
    return vec2(a.x - b.x, a.y - b.y);
}

constexpr vec2 operator*(vec2 a, float val) {
    return vec2(a.x * val, a.y * val);
}

constexpr vec2 operator*(vec2 a, vec2 b) {
    return vec2(a.x * b.x, a.y * b.y);
}

constexpr vec2 operator/(vec2 a, float val) {
    assert(val != 0.0f && "Vec2 operator/ attempting to divide by 0.0f.");
    return vec2(a.x / val, a.y / val);
}

constexpr vec2 operator/(vec2 a, vec2 b) {
    assert(b.x != 0.0f && b.y != 0.0f && "Vec2 operator/ attempting to divide by 0.0f.");
    return vec2(a.x / b.x, a.y / b.y);
}

constexpr bool operator==(vec2 a, vec2 b) {
    return a.x == b.x && a.y == b.y;
}

constexpr bool operator!=(vec2 a, vec2 b) {
    return a.x != b.x || a.y != b.y;
}

static_assert(vec2(1, 2) + vec2(3, 4) == vec2(4, 6));
static_assert(vec2(2, 4) / 2.0f == vec2(1, 2));
static_assert(vec2::up() == vec2(0.0f, 1.0f));
static_assert(vec2::down() == vec2(0.0f, -1.0f));
static_assert(vec2::left() == vec2(-1.0f, 0.0f));
static_assert(vec2::right() == vec2(1.0f, 0.0f));
