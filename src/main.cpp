#include "components.hpp"
#include "entity_component_system.hpp"
#include "fixed_timestep.hpp"
#include "systems.hpp"
#include "utils.hpp"
#include "window_handler.hpp"
#include "world_bounds.hpp"
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

void spawn_circles(entity_component_system& ecs, const world_bounds& bounds, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        entity ent = ecs.create_entity();

        float x = random_number(bounds.min_x, bounds.max_x);
        float y = random_number(bounds.min_y, bounds.max_y);

        ecs.add_component<transform>(ent, transform{vec2{x, y}, vec2{x, y}});
        ecs.add_component<velocity>(
            ent, velocity{random_number(-100.0f, 100.0f), random_number(-100.0f, 100.0f)});
        ecs.add_component<circle_shape>(ent,
                                        circle_shape{random_number(10.0f, 40.0f), random_color()});
    }
}

void draw_frame(circle_render_system* circles, rect_render_system* rects,
                const world_bounds& bounds, float alpha) {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawRectangle(bounds.min_x, bounds.min_y, bounds.width(), bounds.height(), RED);
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

    world_bounds bounds{500, 500, 1000, 1000};

    spawn_circles(ecs, bounds, 10);

    Camera2D cam{};
    cam.target = {bounds.center().y, bounds.center().y};
    cam.offset = {GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f};
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;

    fixed_timestep clock{};

    while (!WindowShouldClose()) {
        clock.begin_frame(GetFrameTime());

        while (clock.step()) {
            physics->update(clock.tick_rate(), bounds);
        }

        draw_frame(circle_render, rect_render, bounds, clock.alpha());
    }

    CloseWindow();
}
