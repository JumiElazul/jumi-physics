#include "components.hpp"
#include "entity_component_system.hpp"
#include "systems.hpp"
#include "utils.hpp"
#include "window_handler.hpp"
#include <cassert>
#include <raylib.h>

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

    std::vector<entity> entities;
    for (size_t i = 0; i < 10; ++i) {
        entity ent = ecs.create_entity();
        entities.push_back(ent);

        float rand_x = random_number(0.0f, static_cast<float>(window.params().width));
        float rand_y = random_number(0.0f, static_cast<float>(window.params().height));
        float radius = random_number(10.0f, 40.0f);

        float vel_x = random_number(-100.0f, 100.0f);
        float vel_y = random_number(-100.0f, 100.0f);

        Color color = random_color();

        ecs.add_component<transform>(ent, transform{rand_x, rand_y});
        ecs.add_component<velocity>(ent, velocity{vel_x, vel_y});
        ecs.add_component<circle_shape>(ent, circle_shape{radius, color});
    }

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        physics->update(dt);

        BeginDrawing();
        ClearBackground(BLACK);
        circle_render->update();
        rect_render->update();

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}
