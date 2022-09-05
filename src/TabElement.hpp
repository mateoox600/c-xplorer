#pragma once

#include "raylib-cpp.hpp"

#include <string>

#include "Extension.hpp"

#define FOLDER 0
#define FILE 1

class TabElement {
private:
    int type;
    std::string name;
    std::string ext;
    std::string fullPath;
    std::string fileSize;

    ExtensionInfo extInfo;

    bool hasIcon = false;
    std::string iconName;

    std::string drawName;
    std::string drawTypeName;
    raylib::Color drawTypeColor;

    bool hovered = false;
    bool selected = false;
    double selectedAt = -1;
    
public:
    TabElement(int type, std::string fullPath);

    bool update(int idx, int yOffset, int width, bool disable);
    void draw(int idx, int yOffset, int width, int typeOffset, int sizeOffset);
    void trigger();

    int getType();
    std::string getName();
    std::string getExt();

    bool isSelected();
    void deselect();
    void select();

    double getSelectAt();
};