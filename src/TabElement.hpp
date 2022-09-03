#pragma once

#include <string>

class TabElement {
private:
    int type;
    std::string name;
    std::string ext;

    bool selected = false;
    double selectedAt = -1;
    
public:
    TabElement(int type, std::string name, std::string ext);

    bool update(int idx, int yOffset, int width, bool disable);
    void draw(int idx, int yOffset, int width, bool disableHover);
    void trigger();

    int getType();
    std::string getName();
    std::string getExt();

    bool isSelected();
    void deselect();
    void select();

    double getSelectAt();
};