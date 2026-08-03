#pragma once
#include <cstdint>

class fixed_timestep {
public:
    explicit fixed_timestep(float ticks_per_second = 60.0f, float max_frame_time = 0.25f)
        : _tick_delta(1.0f / ticks_per_second)
        , _max_frame_time(max_frame_time) {}

    void begin_frame(float real_dt) {
        if (real_dt > _max_frame_time) {
            real_dt = _max_frame_time;
        }
        _accumulator += real_dt;
    }

    bool step() {
        if (_accumulator < _tick_delta) {
            return false;
        }

        _accumulator -= _tick_delta;
        ++_tick_count;
        return true;
    }

    float tick_rate() const { return _tick_delta; }

    float alpha() const { return _accumulator / _tick_delta; }

    std::uint64_t tick_count() const { return _tick_count; }

private:
    float _tick_delta;
    float _max_frame_time;
    float _accumulator = 0.0f;
    std::uint64_t _tick_count = 0;
};
