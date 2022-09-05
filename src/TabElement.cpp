
#include "TabElement.hpp"

#include "raylib-cpp.hpp"

#include "Global.hpp"

TabElement::TabElement(int type, std::string fullPath) : type(type), fullPath(fullPath) {

    switch (type) {
        case FOLDER:
            name = GetFileName(fullPath.c_str());
            fileSize = -1;
            ext = "";

            drawName = name;
            drawTypeName = "Folder";
            drawTypeColor = raylib::Color(255, 231, 146);
            break;
        case FILE:
            name = GetFileNameWithoutExt(fullPath.c_str());
            fileSize = GetFileLength(fullPath.c_str());
            const char* extension = GetFileExtension(fullPath.c_str());
            if(extension == NULL) {
                extension = "";
            }
            ext = extension;
            extInfo = Extension::getInfoForExt(ext);
            if(extInfo.icon != "") {
                iconName = extInfo.icon;
                hasIcon = true;
            }

            drawName = name + ext;
            drawTypeName = extInfo.type;
            drawTypeColor = extInfo.color;
            break;
    }
}

bool TabElement::update(int idx, int yOffset, int width, bool disable) {
    int height = 26;
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

void TabElement::draw(int idx, int yOffset, int width, int typeOffset, int sizeOffset) {
    int height = 26;
    int minX = 16;
    int minY = yOffset + idx * height;

    raylib::Color background(0, 0, 0, 0);
    if(selected) {
        background = raylib::Color(119, 119, 119);
    }else if(hovered) {
        background = raylib::Color(77, 77, 77);
    }
    DrawRectangle(minX, minY, width, height, background);

    if(!hasIcon) {
        DrawRectangle(minX + 6, minY + 4, 18, 18, drawTypeColor);
    }else {
        global.extensionsTextures[iconName].Draw(minX + 6, minY + 4, WHITE);
    }
    raylib::DrawText(drawName, minX + 36, minY + 4, 18, WHITE);
    raylib::DrawText(drawTypeName, typeOffset, minY + 4, 18, WHITE);
    if(fileSize != -1) {
        raylib::DrawText(std::to_string(fileSize), sizeOffset, minY + 4, 18, WHITE);
    }
}

void TabElement::trigger() {
    switch (type) {
        case FOLDER:
            global.tab.navigate(name + "/");
            break;
        case FILE:
            ExtensionInfo extensionInfo = Extension::getInfoForExt(ext);
            if(extensionInfo.executable != "") {
                system((extensionInfo.executable + " " + fullPath).c_str());
            }
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