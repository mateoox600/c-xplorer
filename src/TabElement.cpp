
#include "TabElement.hpp"

#include "raylib-cpp.hpp"

#include "Global.hpp"

TabElement::TabElement(int type, std::string name, std::string ext) : type(type), name(name), ext(ext) {

}

bool TabElement::update(int idx, int yOffset, int width, bool disable) {
    int height = 30;
    int minX = 16;
    int minY = yOffset + idx * height;
    raylib::Vector2 mousePosition = GetMousePosition();
    bool wasSelected = false;

    if(!disable && mousePosition.x >= minX && mousePosition.x < minX + width && mousePosition.y >= minY && mousePosition.y < minY + height) {
        hovered = true;
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {    
            wasSelected = true;
        }
    }else if(hovered) {
        hovered = false;
    }

    return wasSelected;
}

void TabElement::draw(int idx, int yOffset, int width) {
    int height = 30;
    int minX = 16;
    int minY = yOffset + idx * height;

    raylib::Color background(0, 0, 0, 0);
    if(selected) {
        background = raylib::Color(119, 119, 119);
    }else if(hovered) {
        background = raylib::Color(77, 77, 77);
    }
    DrawRectangle(minX, minY, width, height, background);

    std::string fullName;
    raylib::Color color;

    switch (type) {
        case FOLDER:
            fullName = name;
            color = raylib::Color(255, 231, 146);
            break;
        case FILE:
            fullName = name + ext;
            color = raylib::Color(255, 0, 0);
            break;
    }

    DrawRectangle(minX + 6, minY + 4, 22, 22, color);
    raylib::DrawText(fullName, minX + 36, minY + 4, 22, WHITE);
}

void TabElement::trigger() {
    switch (type) {
        case FOLDER:
            global.tab.navigate(name + "/");
            break;
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