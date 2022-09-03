
#include "raylib-cpp.hpp"

#include "Constants.hpp"
#include "Global.hpp"
#include "Tab.hpp"

Global global;

int main(int argc, char *argv[]) {

    raylib::Window window(Constants::screenWidth, Constants::screenHeight, "c-xplorer");

    window.SetTargetFPS(60);

    global = Global{
        &window
    };

    while(!window.ShouldClose()) {

        // Update
        // --------------------
        global.tab.update();

        // Draw
        // --------------------
        window.BeginDrawing();
            window.ClearBackground(raylib::Color(25, 25, 25));

            global.tab.draw();

        window.EndDrawing();

    }

    return 0;
}