#pragma once

#include <string>

#define FOLDER 0
#define FILE 1

class TabElement {
private:
    int type;
    std::string name;
    std::string ext;

    bool hovered = false;
    bool selected = false;
    double selectedAt = -1;
    
public:
    TabElement(int type, std::string name, std::string ext);

    bool update(int idx, int yOffset, int width, bool disable);
    void draw(int idx, int yOffset, int width);
    void trigger();

    int getType();
    std::string getName();
    std::string getExt();

    bool isSelected();
    void deselect();
    void select();

    double getSelectAt();
};