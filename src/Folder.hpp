#pragma once

#include <string>

class Folder {
private:
    std::string name;
    bool selected = false;
    double selectedAt = -1;
public:
    Folder(std::string name);

    bool update(int idx, int yOffset, int width, bool disable);
    void draw(int idx, int yOffset, int width, bool disableHover);

    std::string getName();

    bool isSelected();
    void deselect();
    void select();

    double getSelectAt();
};