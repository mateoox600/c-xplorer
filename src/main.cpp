
#include "raylib-cpp.hpp"

#include "Constants.hpp"
#include "Tab.hpp"

int main(int argc, char *argv[]) {

    raylib::Window window(Constants::screenWidth, Constants::screenHeight, "c-xplorer");

    window.SetTargetFPS(60);

    Tab currentTab;

    while(!window.ShouldClose()) {

        // Update
        // --------------------
        currentTab.update();

        // Draw
        // --------------------
        window.BeginDrawing();
            window.ClearBackground(raylib::Color(25, 25, 25));

            currentTab.draw();

        window.EndDrawing();

    }

    return 0;
}