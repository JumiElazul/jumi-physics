#pragma once
#include "system.hpp"
#include "types.hpp"
#include <cassert>
#include <memory>
#include <set>
#include <typeindex>
#include <unordered_map>

class system_manager {
public:
    template<typename T>
    [[nodiscard]] T* register_system() {
        std::type_index index(typeid(T));
        auto [it, inserted] = _systems.insert({index, std::make_unique<T>()});

        assert(inserted && "System registered twice.");

        return static_cast<T*>(it->second.get());
    }

    template<typename T>
    void set_signature(signature sig) {
        std::type_index index(typeid(T));

        _signatures.insert({index, sig});
    }

    void entity_destroyed(entity ent) {
        for (const auto& pair : _systems) {
            const auto& system = pair.second;
            system->entities.erase(ent);
        }
    }

    void entity_signature_changed(entity ent, signature ent_sig) {
        for (const auto& [type, system] : _systems) {
            const auto& sys_sig = _signatures[type];

            if ((ent_sig & sys_sig) == sys_sig) {
                system->entities.insert(ent);
            } else {
                system->entities.erase(ent);
            }
        }
    }

private:
    std::unordered_map<std::type_index, signature> _signatures;
    std::unordered_map<std::type_index, std::unique_ptr<class system>> _systems;
};
