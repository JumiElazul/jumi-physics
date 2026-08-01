#pragma once
#include "types.hpp"
#include <cassert>
#include <memory>
#include <typeindex>
#include <unordered_map>

class icomponent_array {
public:
    virtual ~icomponent_array() = default;
    virtual void entity_destroyed(entity ent) = 0;
};

template<typename T>
class component_array : public icomponent_array {
public:
    void insert_data(entity ent, T component) {
        assert(_entity_to_index.find(ent) == _entity_to_index.end() &&
               "Component added to same entity more than once.");

        size_t new_index = _size;
        _entity_to_index[ent] = new_index;
        _index_to_entity[new_index] = ent;
        _components[new_index] = component;
        ++_size;
    }

    void remove_data(entity ent) {
        assert(_entity_to_index.find(ent) != _entity_to_index.end() &&
               "Removing non-existent component.");

        size_t removal_index = _entity_to_index[ent];
        size_t last_index = _size - 1;
        _components[removal_index] = _components[last_index];

        entity last_entity = _index_to_entity[last_index];
        _entity_to_index[last_entity] = removal_index;
        _index_to_entity[removal_index] = last_entity;

        _entity_to_index.erase(ent);
        _index_to_entity.erase(last_index);

        --_size;
    }

    [[nodiscard]] T& get_data(entity ent) {
        assert(_entity_to_index.find(ent) != _entity_to_index.end() &&
               "Retrieving non-existent component.");
        return _components[_entity_to_index[ent]];
    }

    void entity_destroyed(entity ent) override {
        if (_entity_to_index.find(ent) != _entity_to_index.end()) {
            remove_data(ent);
        }
    }

private:
    std::array<T, MAX_ENTITIES> _components{};
    std::unordered_map<entity, uint32_t> _entity_to_index{};
    std::unordered_map<entity, uint32_t> _index_to_entity{};
    size_t _size{};
};

class component_manager {
public:
    template<typename T>
    void register_component() {
        std::type_index index(typeid(T));

        assert(_component_arrays.find(index) == _component_arrays.end() &&
               "Registering component type more than once.");

        _component_types.insert({index, _next_component_type});
        _component_arrays.insert({index, std::make_unique<component_array<T>>()});

        ++_next_component_type;
    }

    template<typename T>
    component_type get_component_type() {
        std::type_index index(typeid(T));
        return _component_types[index];
    }

    template<typename T>
    void add_component(entity ent, T component) {
        get_component_array<T>()->insert_data(ent, component);
    }

    template<typename T>
    void remove_component(entity ent) {
        get_component_array<T>()->remove_data(ent);
    }

    template<typename T>
    [[nodiscard]] T& get_component(entity ent) {
        return get_component_array<T>()->get_data(ent);
    }

    void entity_destroyed(entity ent) {
        for (const auto& pair : _component_arrays) {
            const auto& component = pair.second;
            component->entity_destroyed(ent);
        }
    }

private:
    std::unordered_map<std::type_index, component_type> _component_types;
    std::unordered_map<std::type_index, std::unique_ptr<icomponent_array>> _component_arrays;
    component_type _next_component_type{};

    template<typename T>
    component_array<T>* get_component_array() {
        std::type_index index(typeid(T));
        return static_cast<component_array<T>*>(_component_arrays[index].get());
    }
};
