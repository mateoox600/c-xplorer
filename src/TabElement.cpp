
#include "TabElement.hpp"

#include "raylib-cpp.hpp"

#include "Global.hpp"

TabElement::TabElement(int type, std::string name, std::string ext) : type(type), name(name), ext(ext) {

}

bool TabElement::update(int idx, int yOffset, int width, bool disableHover) {
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

void TabElement::draw(int idx, int yOffset, int width, bool disableHover) {
    int height = 30;
    int minX = 16;
    int minY = yOffset + idx * height;
    raylib::Vector2 mousePosition = GetMousePosition();
    if(selected) {
        DrawRectangle(minX, minY, width, height, raylib::Color(119, 119, 119));
    }else if(!disableHover && mousePosition.x >= minX && mousePosition.x < minX + width && mousePosition.y >= minY && mousePosition.y < minY + height) {
        DrawRectangle(minX, minY, width, height, raylib::Color(77, 77, 77));
    }
    if(type == 0) {
        DrawRectangle(minX + 6, minY + 4, 22, 22, raylib::Color(255, 231, 146));
        raylib::DrawText(name, minX + 36, minY + 4, 22, WHITE);
    }else if(type == 1) {
        DrawRectangle(minX + 6, minY + 4, 22, 22, raylib::Color(255, 0, 0));
        raylib::DrawText(name + ext, minX + 36, minY + 4, 22, WHITE);
    }
}

void TabElement::trigger() {
    if(type == 0) {
        global.tab.navigate(name + "/");
        global.tab.refresh();
    }
}

int TabElement::getType() {
    return type;
}

std::string TabElement::getName() {
    return name;
}

std::string TabElement::getExt() {
    return ext;
}

bool TabElement::isSelected() {
    return selected;
}

void TabElement::deselect() {
    selected = false;
}

void TabElement::select() {
    selected = true;
    selectedAt = GetTime();
}

double TabElement::getSelectAt() {
    return selectedAt;
}