#include "window_handler.hpp"
#include <raylib.h>

window_handler::window_handler(window_params params)
    : _params(params) {
    InitWindow(params.width, params.height, params.title);
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
}
