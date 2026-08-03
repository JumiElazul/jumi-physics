#pragma once
#include <cstdint>

class fixed_timestep {
public:
    explicit fixed_timestep(float ticks_per_second = 60.0f, float max_frame_time = 0.25f);

    void begin_frame(float real_dt);
    [[nodiscard]] bool step() noexcept;
    [[nodiscard]] float tick_rate() const noexcept;
    [[nodiscard]] float alpha() const noexcept;
    [[nodiscard]] std::uint64_t tick_count() const noexcept;

private:
    float _tick_delta;
    float _max_frame_time;
    float _accumulator = 0.0f;
    std::uint64_t _tick_count = 0;
};
