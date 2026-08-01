#pragma once
#include "types.hpp"

struct window_params {
    int width = 1920;
    int height = 1080;
    const char* title = "Jumi Physics";
};

class window_handler {
public:
    window_handler(window_params params);

    [[nodiscard]] const window_params& params() const noexcept { return _params; }

private:
    window_params _params;
};
