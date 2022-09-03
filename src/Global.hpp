#pragma once

#include "raylib-cpp.hpp"

#include "Tab.hpp"

struct Global {

    Global() { }
    Global(raylib::Window* window) : window(window) { }

    raylib::Window* window;

    Tab tab;

};

extern Global global;