#include "fixed_timestep.hpp"
#include <cstdint>

fixed_timestep::fixed_timestep(float ticks_per_second, float max_frame_time)
    : _tick_delta(1.0f / ticks_per_second)
    , _max_frame_time(max_frame_time) {
}

void fixed_timestep::begin_frame(float real_dt) {
    if (real_dt > _max_frame_time) {
        real_dt = _max_frame_time;
    }
    _accumulator += real_dt;
}

bool fixed_timestep::step() noexcept {
    if (_accumulator < _tick_delta) {
        return false;
    }

    _accumulator -= _tick_delta;
    ++_tick_count;
    return true;
}

float fixed_timestep::tick_rate() const noexcept {
    return _tick_delta;
}

float fixed_timestep::alpha() const noexcept {
    return _accumulator / _tick_delta;
}

std::uint64_t fixed_timestep::tick_count() const noexcept {
    return _tick_count;
}
