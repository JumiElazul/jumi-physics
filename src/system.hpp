#pragma once
#include "types.hpp"
#include <set>

class system {
public:
    virtual ~system() = default;
    std::set<entity> entities;
};
