#include "Tab.hpp"

#include <algorithm>
#include "math.h"

#include "Constants.hpp"
#include "Global.hpp"

using namespace Constants;

Tab::Tab() {
}

void Tab::init() {
    nameStringWidth = MeasureTextEx(global.mainFont, "Name", 22, 0).x;
    typeStringWidth = MeasureTextEx(global.mainFont, "Type", 22, 0).x;
    sizeStringWidth = MeasureTextEx(global.mainFont, "Size", 22, 0).x;
}

void Tab::update() {
    if(elements.size() <= 0) {
        std::vector<std::string> folderContent = getCurrentFolderContent();
        for(int i = 0; i < folderContent.size(); i++) {
            std::string element = folderContent[i];
            if(IsPathFile(element.c_str())) {
                elements.push_back(TabElement(FILE, element));
            }else {
                elements.push_back(TabElement(FOLDER, element));
            }
        }
        sortElements();
    }

    scrolled -= GetMouseWheelMove();
    scrolled = std::max(std::min(scrolled, (int) elements.size() - 1), 0);

    if(IsMouseButtonPressed(MOUSE_BUTTON_SIDE)) {
        currentPath = currentPath.substr(0, currentPath.size() - 1);
        currentPath = currentPath.substr(0, currentPath.find_last_of("/") + 1);
        refresh();
    }

    raylib::Vector2 mousePosition = GetMousePosition();
    int xNamePosition = nameWidth + nameStringWidth + 14;
    int xTypePosition = xNamePosition + 14 + typeWidth + typeStringWidth;
    int xSizePosition = xTypePosition + 14 + sizeWidth + sizeStringWidth;
    if(mousePosition.x >= xNamePosition - 4 && mousePosition.x < xNamePosition + 4 && mousePosition.y >= yOffset + 6 - 4 && mousePosition.y < yOffset + 6 + 30 + 4) {
        SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            changingNameWidth = true;
        }
    }else if(mousePosition.x >= xTypePosition - 4 && mousePosition.x < xTypePosition + 4 && mousePosition.y >= yOffset + 6 - 4 && mousePosition.y < yOffset + 6 + 30 + 4) {
        SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            changingTypeWidth = true;
        }
    }else if(mousePosition.x >= xSizePosition - 4 && mousePosition.x < xSizePosition + 4 && mousePosition.y >= yOffset + 6 - 4 && mousePosition.y < yOffset + 6 + 30 + 4) {
        SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            changingSizeWidth = true;
        }
    }else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        if(changingNameWidth) {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            changingNameWidth = false;
        }else if(changingTypeWidth) {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            changingTypeWidth = false;
        }else if(changingSizeWidth) {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            changingSizeWidth = false;
        }
    }

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        raylib::Vector2 mousePosition = GetMousePosition();
        if(changingNameWidth) {
            nameWidth = std::max((int) mousePosition.x - nameStringWidth - 14, 0);
        }else if(changingTypeWidth) {
            int xNamePosition = nameWidth + nameStringWidth + 14;
            typeWidth = std::max((int) mousePosition.x - xNamePosition - 14 - typeStringWidth, 0);
        }else if(changingSizeWidth) {
            int xNamePosition = nameWidth + nameStringWidth + 14;
            int xTypePosition = xNamePosition + typeWidth + typeStringWidth + 14;
            sizeWidth = std::max((int) mousePosition.x - xTypePosition - 14 - sizeStringWidth, 0);
        }
    }

    bool oneSelected = false;
    for(int i = scrolled; i < elements.size(); i++) {
        TabElement* element = &elements[i];
        bool wasSelected = element->update(i, yOffset + headerHeight - scrolled * 26, nameWidth + nameStringWidth + 14 + typeWidth + typeStringWidth, changingNameWidth);
        if(wasSelected) {
            oneSelected = true;
            if(element->isSelected() && element->getSelectAt() + 0.5 > GetTime()) {
                element->trigger();
            }else {
                resetSelected();
                element->select();
            }
        }
    }
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !oneSelected) {
        resetSelected();
    }

    if(IsKeyPressed(KEY_F5)) {
        refresh();
    }
}

void Tab::draw() {
    raylib::DrawTextEx(global.mainFont, currentPath, raylib::Vector2(10, 10), 22, 0, WHITE);

    DrawRectangle(6, yOffset, screenWidth - 12, screenHeight - yOffset - 6, raylib::Color(32, 32, 32));
    DrawRectangleLines(6, yOffset, screenWidth - 12, screenHeight - yOffset - 6, raylib::Color(43, 43, 43));

    raylib::DrawTextEx(global.mainFont, "Name", raylib::Vector2(16, yOffset + 10), 22, 0, WHITE);
    int nameOffset = nameWidth + nameStringWidth + 16;
    DrawRectangle(nameOffset, yOffset + 6, 1, 30, WHITE);

    raylib::DrawTextEx(global.mainFont, "Type", raylib::Vector2(nameOffset + 14, yOffset + 10), 22, 0, WHITE);
    int typeOffset = nameOffset + 14 + typeWidth + typeStringWidth;
    DrawRectangle(typeOffset, yOffset + 6, 1, 30, WHITE);

    raylib::DrawTextEx(global.mainFont, "Size", raylib::Vector2(typeOffset + 14, yOffset + 10), 22, 0, WHITE);
    int sizeOffset = typeOffset + 14 + sizeWidth + sizeStringWidth;
    DrawRectangle(sizeOffset, yOffset + 6, 1, 30, WHITE);

    int elementsWidth = nameWidth + nameStringWidth + 14 + typeWidth + typeStringWidth + 14 + sizeWidth + sizeStringWidth;
    for(int i = scrolled; i < elements.size(); i++) {
        elements[i].draw(i, yOffset + headerHeight - scrolled * 26, elementsWidth, nameOffset + 16, typeOffset + 16);
    }

}

void Tab::resetSelected() {
    for(int i = 0; i < elements.size(); i++) {
        elements[i].deselect();
    }
}

void Tab::refresh() {
    elements.clear();
    scrolled = 0;
}

bool sortElement(TabElement el1, TabElement el2) {
    if(el1.getType() == FOLDER && el2.getType() == FILE) return true;
    else if(el1.getType() == FILE && el2.getType() == FOLDER) return false;

    return el1.getName().compare(el2.getName()) == -1 ? true : false;
}

void Tab::sortElements() {
    std::sort(elements.begin(), elements.end(), sortElement);
}

void Tab::navigate(std::string path) {
    currentPath += path;
    refresh();
}

std::vector<std::string> Tab::getCurrentFolderContent() {
    return raylib::LoadDirectoryFiles(currentPath);
}
