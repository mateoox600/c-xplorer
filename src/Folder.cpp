
#include "Folder.hpp"

#include "raylib-cpp.hpp"

Folder::Folder(std::string name) : name(name) {

}

bool Folder::update(int idx, int yOffset, int width, bool disableHover) {
    int height = 30;
    int minX = 16;
    int minY = yOffset + idx * height;
    raylib::Vector2 mousePosition = GetMousePosition();

    bool wasSelected = false;
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {    
        if(mousePosition.x >= minX && mousePosition.x < minX + width && mousePosition.y >= minY && mousePosition.y < minY + height) {
            wasSelected = true;
        }
    }

    return wasSelected;
}

void Folder::draw(int idx, int yOffset, int width, bool disableHover) {
    int height = 30;
    int minX = 16;
    int minY = yOffset + idx * height;
    raylib::Vector2 mousePosition = GetMousePosition();
    if(selected) {
        DrawRectangle(minX, minY, width, height, raylib::Color(119, 119, 119));
    }else if(!disableHover && mousePosition.x >= minX && mousePosition.x < minX + width && mousePosition.y >= minY && mousePosition.y < minY + height) {
        DrawRectangle(minX, minY, width, height, raylib::Color(77, 77, 77));
    }
    DrawRectangle(minX + 6, minY + 4, 22, 22, raylib::Color(255, 231, 146));
    raylib::DrawText(name, minX + 36, minY + 4, 22, WHITE);
}

std::string Folder::getName() {
    return name;
}

bool Folder::isSelected() {
    return selected;
}

void Folder::deselect() {
    selected = false;
}

void Folder::select() {
    selected = true;
    selectedAt = GetTime();
}

double Folder::getSelectAt() {
    return selectedAt;
}