#pragma once
#include <bitset>
#include <cstdint>

using std::int16_t;
using std::int32_t;
using std::int64_t;
using std::int8_t;
using std::uint16_t;
using std::uint32_t;
using std::uint64_t;
using std::uint8_t;

using entity = uint32_t;
constexpr entity MAX_ENTITIES = 5000;

using component_type = uint8_t;
constexpr component_type MAX_COMPONENTS = 32;

using signature = std::bitset<MAX_COMPONENTS>;
