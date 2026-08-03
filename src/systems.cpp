#include "systems.hpp"
#include "components.hpp"
#include "entity_component_system.hpp"
#include <cmath>

void physics_system::update(float step) {
    entity_component_system& ecs = entity_component_system::instance();

    for (entity ent : entities) {
        transform& trans = ecs.get_component<transform>(ent);
        velocity& vel = ecs.get_component<velocity>(ent);

        trans.save();

        trans.current.x += vel.dx * step;
        trans.current.y += vel.dy * step;
    }
}

void circle_render_system::update(float alpha) {
    entity_component_system& ecs = entity_component_system::instance();
    for (entity ent : entities) {
        const transform& trans = ecs.get_component<transform>(ent);
        const circle_shape& shape = ecs.get_component<circle_shape>(ent);

        vec2 pos = trans.interpolated(alpha);
        DrawCircleV({pos.x, pos.y}, shape.radius, shape.color);
    }
}

void rect_render_system::update(float alpha) {
    entity_component_system& ecs = entity_component_system::instance();
    for (entity ent : entities) {
        const transform& trans = ecs.get_component<transform>(ent);
        const rect_shape& shape = ecs.get_component<rect_shape>(ent);

        vec2 pos = trans.interpolated(alpha);
        DrawRectangleV({pos.x - shape.width * 0.5f, pos.y - shape.height * 0.5f},
                       {shape.width, shape.height}, shape.color);
    }
}
