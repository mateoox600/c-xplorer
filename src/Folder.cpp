
#include "Folder.hpp"

#include "raylib-cpp.hpp"

Folder::Folder(std::string name) : name(name) {

}

void Folder::update() {

}

void Folder::draw(int idx, int yOffset) {
    DrawRectangle(20, yOffset + 2 + idx * 30, 26, 26, raylib::Color(255, 231, 146));
    raylib::DrawText(name, 52, yOffset + 4 + idx * 30, 22, WHITE);
}