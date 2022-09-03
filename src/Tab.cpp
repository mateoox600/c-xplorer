#include "Tab.hpp"

#include "math.h"

#include "Constants.hpp"

using namespace Constants;

Tab::Tab() {

}

void Tab::update() {
    if(elements.size() <= 0) {
        std::vector<std::string> folderContent = getCurrentFolderContent();
        for(int i = 0; i < folderContent.size(); i++) {
            std::string element = folderContent[i];
            if(IsPathFile(element.c_str())) {
                const char* name = GetFileNameWithoutExt(element.c_str());
                const char* extension = GetFileExtension(element.c_str());
                if(extension == NULL) {
                    extension = "";
                }
                elements.push_back(TabElement(1, name, extension));
            }else {
                const char* name = GetFileName(element.c_str());
                elements.push_back(TabElement(0, name, ""));
            }
        }
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_SIDE)) {
        currentPath = currentPath.substr(0, currentPath.size() - 1);
        currentPath = currentPath.substr(0, currentPath.find_last_of("/") + 1);
        refresh();
    }

    raylib::Vector2 mousePosition = GetMousePosition();
    int xPosition = nameWidth + nameStringWidth + 14;
    if(mousePosition.x >= xPosition - 4 && mousePosition.x < xPosition + 4 && mousePosition.y >= yOffset + 6 - 4 && mousePosition.y < yOffset + 6 + 30 + 4) {
        SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            changingNameWidth = true;
        }
    }else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        if(changingNameWidth) {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            changingNameWidth = false;
        }
    }

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if(changingNameWidth) {
            raylib::Vector2 mousePosition = GetMousePosition();
            nameWidth = std::max((int) mousePosition.x - nameStringWidth - 14, 0);
        }
    }

    for(int i = 0; i < elements.size(); i++) {
        TabElement* element = &elements[i];
        bool wasSelected = element->update(i, yOffset + headerHeight, nameWidth + nameStringWidth, changingNameWidth);
        if(wasSelected) {
            if(element->isSelected() && element->getSelectAt() + 0.5 > GetTime()) {
                element->trigger();
            }else {
                resetSelected();
                element->select();
            }
        }
    }
}

void Tab::draw() {
    raylib::DrawText(currentPath, 10, 10, 16, WHITE);

    DrawRectangle(6, yOffset, screenWidth - 12, screenHeight - yOffset - 6, raylib::Color(32, 32, 32));
    DrawRectangleLines(6, yOffset, screenWidth - 12, screenHeight - yOffset - 6, raylib::Color(43, 43, 43));

    DrawText("Name", 14, yOffset + 10, 22, WHITE);
    DrawRectangle(nameWidth + nameStringWidth + 14, yOffset + 6, 1, 30, WHITE);

    for(int i = 0; i < elements.size(); i++) {
        elements[i].draw(i, yOffset + headerHeight, nameWidth + nameStringWidth, changingNameWidth);
    }

}

void Tab::resetSelected() {
    for(int i = 0; i < elements.size(); i++) {
        elements[i].deselect();
    }
}

void Tab::refresh() {
    elements.clear();
}

void Tab::navigate(std::string path) {
    currentPath += path;
}

std::vector<std::string> Tab::getCurrentFolderContent() {
    return raylib::LoadDirectoryFiles(currentPath);
}
