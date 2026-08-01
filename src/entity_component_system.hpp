#pragma once
#include "component_manager.hpp"
#include "entity_manager.hpp"
#include "system_manager.hpp"
#include "types.hpp"
#include <memory>

class entity_component_system {
public:
    static entity_component_system& instance() {
        static entity_component_system instance;
        return instance;
    }

    [[nodiscard]] entity create_entity() { return _entity_manager->create_entity(); }

    void destroy_entity(entity ent) {
        _entity_manager->destroy_entity(ent);
        _component_manager->entity_destroyed(ent);
        _system_manager->entity_destroyed(ent);
    }

    template<typename T>
    void register_component() {
        _component_manager->register_component<T>();
    }

    template<typename T>
    void add_component(entity ent, T component) {
        _component_manager->add_component<T>(ent, component);

        signature ent_sig = _entity_manager->get_signature(ent);
        ent_sig.set(_component_manager->get_component_type<T>(), true);
        _entity_manager->set_signature(ent, ent_sig);

        _system_manager->entity_signature_changed(ent, ent_sig);
    }

    template<typename T>
    void remove_component(entity ent, T component) {
        _component_manager->remove_component<T>(ent);

        signature ent_sig = _entity_manager->get_signature(ent);
        ent_sig.set(_component_manager->get_component_type<T>(), false);
        _entity_manager->set_signature(ent, ent_sig);

        _system_manager->entity_signature_changed(ent, ent_sig);
    }

    template<typename T>
    [[nodiscard]] bool has_component(entity ent) {
        return _entity_manager->get_signature(ent).test(
            _component_manager->get_component_type<T>());
    }

    template<typename T>
    [[nodiscard]] T& get_component(entity ent) {
        return _component_manager->get_component<T>(ent);
    }

    template<typename T>
    component_type get_component_type() {
        return _component_manager->get_component_type<T>();
    }

    template<typename T>
    [[nodiscard]] T* register_system() {
        return static_cast<T*>(_system_manager->register_system<T>());
    }

    template<typename T>
    void set_system_signature(signature sig) {
        _system_manager->set_signature<T>(sig);
    }

private:
    std::unique_ptr<entity_manager> _entity_manager;
    std::unique_ptr<component_manager> _component_manager;
    std::unique_ptr<system_manager> _system_manager;

    entity_component_system()
        : _entity_manager(std::make_unique<entity_manager>())
        , _component_manager(std::make_unique<component_manager>())
        , _system_manager(std::make_unique<system_manager>()) {}
};

template<typename... Ts>
[[nodiscard]] signature make_signature() {
    entity_component_system& ecs = entity_component_system::instance();

    signature sig;
    (sig.set(ecs.get_component_type<Ts>(), true), ...);
    return sig;
}
