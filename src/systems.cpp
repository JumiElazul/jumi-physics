#include "systems.hpp"
#include "components.hpp"
#include "entity_component_system.hpp"

void physics_system::update(float dt) {
    entity_component_system& ecs = entity_component_system::instance();

    for (entity ent : entities) {
        transform& trans = ecs.get_component<transform>(ent);
        velocity& vel = ecs.get_component<velocity>(ent);
        trans.x += vel.dx * dt;
        trans.y += vel.dy * dt;
    }
}

void circle_render_system::update() {
    entity_component_system& ecs = entity_component_system::instance();
    for (entity ent : entities) {
        const transform& trans = ecs.get_component<transform>(ent);
        const circle_shape& shape = ecs.get_component<circle_shape>(ent);
        DrawCircleV({trans.x, trans.y}, shape.radius, shape.color);
    }
}

void rect_render_system::update() {
    entity_component_system& ecs = entity_component_system::instance();
    for (entity ent : entities) {
        const transform& trans = ecs.get_component<transform>(ent);
        const rect_shape& shape = ecs.get_component<rect_shape>(ent);
        DrawRectangleV({trans.x - shape.width * 0.5f, trans.y - shape.height * 0.5f},
                       {shape.width, shape.height}, shape.color);
    }
}
