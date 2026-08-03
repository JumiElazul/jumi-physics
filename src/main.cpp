#include "components.hpp"
#include "entity_component_system.hpp"
#include "fixed_timestep.hpp"
#include "systems.hpp"
#include "utils.hpp"
#include "window_handler.hpp"
#include <algorithm>
#include <cassert>
#include <raylib.h>

enum class threading_mode {
    single,
    multi,
};

const char* threading_mode_tostr(threading_mode mode) {
    switch (mode) {
        case threading_mode::single: {
            return "singlethreaded";
        }
        case threading_mode::multi: {
            return "multithreaded";
        }
    }

    return "";
}

static threading_mode current_threading_mode = threading_mode::single;

namespace {

void spawn_circles(entity_component_system& ecs, const window_handler& window, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        entity ent = ecs.create_entity();

        float x = random_number(0.0f, static_cast<float>(window.params().width));
        float y = random_number(0.0f, static_cast<float>(window.params().height));

        ecs.add_component<transform>(ent, transform{vec2{x, y}, vec2{x, y}});
        ecs.add_component<velocity>(
            ent, velocity{random_number(-100.0f, 100.0f), random_number(-100.0f, 100.0f)});
        ecs.add_component<circle_shape>(ent,
                                        circle_shape{random_number(10.0f, 40.0f), random_color()});
    }
}

void draw_frame(circle_render_system* circles, rect_render_system* rects, float alpha) {
    BeginDrawing();
    ClearBackground(BLACK);

    circles->update(alpha);
    rects->update(alpha);

    DrawFPS(10, 10);
    DrawText(threading_mode_tostr(current_threading_mode), 10, 30, 20, RAYWHITE);

    EndDrawing();
}

} // namespace

int main() {
    window_params params;
    window_handler window(params);

    entity_component_system& ecs = entity_component_system::instance();

    ecs.register_component<transform>();
    ecs.register_component<velocity>();
    ecs.register_component<circle_shape>();
    ecs.register_component<rect_shape>();

    physics_system* physics = ecs.register_system<physics_system>();
    ecs.set_system_signature<physics_system>(make_signature<transform, velocity>());

    circle_render_system* circle_render = ecs.register_system<circle_render_system>();
    ecs.set_system_signature<circle_render_system>(make_signature<transform, circle_shape>());

    rect_render_system* rect_render = ecs.register_system<rect_render_system>();
    ecs.set_system_signature<rect_render_system>(make_signature<transform, rect_shape>());

    spawn_circles(ecs, window, 10);

    fixed_timestep clock{};

    while (!WindowShouldClose()) {
        clock.begin_frame(GetFrameTime());

        while (clock.step()) {
            physics->update(clock.tick_rate());
        }

        draw_frame(circle_render, rect_render, clock.alpha());
    }

    CloseWindow();
}
