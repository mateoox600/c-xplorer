
#include "TabElement.hpp"

#include "raylib-cpp.hpp"

#include "Global.hpp"

std::vector<std::string> units = { "o", "Kio", "Mio", "Gio", "Tio", "Pio", "Eio", "Zio", "Yoi" };

std::string formatSize(int size, int unit = 0) {
    if(size >  10000) {
        return formatSize(size / 1000, unit + 1);
    }
    std::string digits = std::to_string(size);
    for(int i = digits.size() - 3; i > 0; i -= 3) {
        digits.insert(i, " ");
    }
    return digits + " " + units[unit];
}

TabElement::TabElement(int type, std::string fullPath) : type(type), fullPath(fullPath) {

    switch (type) {
        case FOLDER:
            name = GetFileName(fullPath.c_str());
            fileSize = "";
            ext = "";
            drawTypeColor = raylib::Color(255, 231, 146);
            typeName = "Folder";
            break;
        case FILE:
            name = GetFileNameWithoutExt(fullPath.c_str());
            fileSize = formatSize(GetFileLength(fullPath.c_str()));
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
            drawTypeColor = extInfo.color;
            typeName = extInfo.type;
            break;
    }
    updateStringsWidth();
}

std::string reduceStringToWidth(std::string str, int width) {
    str = str.substr(0, str.size() - 1);
    if(MeasureTextEx(global.mainFont, (str + "...").c_str(), 22, 0).x > width) {
        return reduceStringToWidth(str, width);
    }
    return str + "...";
}

bool TabElement::update(int idx, int yOffset, int width, bool disable, bool widthChanged, int typeOffset) {
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

    if(widthChanged) {
        updateStringsWidth();
    }
    
    if((name + ext) != drawName && mousePosition.x >= minX + 30 && mousePosition.x < minX + global.tab.getFullNameWidth() && mousePosition.y >= minY && mousePosition.y < minY + height) {
        namePopup = true;
    }else if(namePopup) {
        namePopup = false;
    }

    if(typeName != drawTypeName && mousePosition.x >= typeOffset && mousePosition.x <= typeOffset + global.tab.getFullTypeWidth() && mousePosition.y >= minY && mousePosition.y <= minY + height) {
        typePopup = true;
    }else if(typePopup) {
        typePopup = false;
    }

    return wasSelected;
}

void TabElement::updateStringsWidth() {
    int nameStringWidth = MeasureTextEx(global.mainFont, (name + ext).c_str(), 22, 0).x;
    if(nameStringWidth >= global.tab.getFullNameWidth() - 14 - 32) {
        drawName = reduceStringToWidth(name + ext, global.tab.getFullNameWidth() - 14 - 32);
    }else {
        drawName = name + ext;
    }
    int typeStringWidth = MeasureTextEx(global.mainFont, typeName.c_str(), 22, 0).x;
    if(typeStringWidth >= global.tab.getFullTypeWidth() - 14) {
        drawTypeName = reduceStringToWidth(typeName, global.tab.getFullTypeWidth() - 14);
    }else {
        drawTypeName = typeName;
    }
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
        global.GetOrLoadExtensionTexture(iconName)->Draw(minX + 6, minY + 4, WHITE);
    }
    raylib::DrawTextEx(global.mainFont, drawName, raylib::Vector2(minX + 32, minY + 2), 22, 0, WHITE);
    raylib::DrawTextEx(global.mainFont, drawTypeName, raylib::Vector2(typeOffset, minY + 2), 22, 0, WHITE);
    if(fileSize != "") {
        raylib::DrawTextEx(global.mainFont, fileSize, raylib::Vector2(sizeOffset, minY + 2), 22, 0, WHITE);
    }

    raylib::Vector2 mousePosition = GetMousePosition();
    if(namePopup) {
        int fullNameWidth = MeasureTextEx(global.mainFont, (name + ext).c_str(), 22, 0).x;
        mousePosition.DrawRectangle(raylib::Vector2(fullNameWidth + 6, 26), GRAY);
        raylib::DrawTextEx(global.mainFont, name + ext, raylib::Vector2(mousePosition.x + 3, mousePosition.y + 2), 22, 0, WHITE);
    }
    if(typePopup) {
        int fullTypeWidth = MeasureTextEx(global.mainFont, typeName.c_str(), 22, 0).x;
        mousePosition.DrawRectangle(raylib::Vector2(fullTypeWidth + 6, 26), GRAY);
        raylib::DrawTextEx(global.mainFont, typeName, raylib::Vector2(mousePosition.x + 3, mousePosition.y + 2), 22, 0, WHITE);
    }
}

void TabElement::trigger() {
    switch (type) {
        case FOLDER:
            global.tab.navigate(name + "/");
            break;
        case FILE:
            if(extInfo.executable != "") {
                system((extInfo.executable + " " + fullPath).c_str());
            }else {
                system(fullPath.c_str());
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