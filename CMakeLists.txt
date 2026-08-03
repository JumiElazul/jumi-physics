cmake_minimum_required(VERSION 3.25)

project(jumi-physics VERSION 0.0.1 LANGUAGES CXX)

find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG QUIET)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
    "main.cpp"
    
    "entity_manager.hpp"
    "components.hpp"
    "component_manager.hpp"
    "fixed_timestep.hpp"
    "fixed_timestep.cpp"
    "system.hpp"
    "system_manager.hpp"
    "systems.hpp"
    "systems.cpp"
    "entity_component_system.hpp"
    "types.hpp"
    "utils.hpp"
    "vector.hpp"
    "window_handler.hpp"
    "window_handler.cpp"
    "world_bounds.hpp"
)
list(TRANSFORM SOURCES PREPEND "src/")

add_executable(jumi-physics ${SOURCES})
target_compile_features(jumi-physics PRIVATE cxx_std_23)
target_link_libraries(jumi-physics PRIVATE raylib)
if(TARGET glfw)
    target_link_libraries(jumi-physics PRIVATE glfw)
endif()
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT jumi-physics)
