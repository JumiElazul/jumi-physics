#pragma once
#include "types.hpp"
#include <array>
#include <cassert>
#include <queue>

class entity_manager {
public:
    entity_manager() {
        for (entity ent = 0; ent < MAX_ENTITIES; ++ent) {
            _entities.push(ent);
        }
    }

    [[nodiscard]] entity create_entity() {
        assert(_living_entity_count < MAX_ENTITIES && "Too many entities in existence.");
        entity ent = _entities.front();
        _entities.pop();
        ++_living_entity_count;

        return ent;
    }

    void destroy_entity(entity ent) {
        assert(ent < MAX_ENTITIES && "Entity out of range.");

        _signatures[ent].reset();
        _entities.push(ent);
        --_living_entity_count;
    }

    void set_signature(entity ent, signature sig) {
        assert(ent < MAX_ENTITIES && "Entity out of range.");
        _signatures[ent] = sig;
    }

    signature get_signature(entity ent) {
        assert(ent < MAX_ENTITIES && "Entity out of range.");
        return _signatures[ent];
    }

private:
    std::queue<entity> _entities{};
    std::array<signature, MAX_ENTITIES> _signatures{};
    uint32_t _living_entity_count{};
};
