#pragma once

#include "raylib-cpp.hpp"
#include <string>
#include <vector>

#include "Path.hpp"
#include "TabElement.hpp"

class Tab {
private:
    std::string currentPath = Path::formatPath(raylib::GetWorkingDirectory());

    std::vector<TabElement> elements;

    int headerHeight = 50;
    int yOffset = 75;

    int nameStringWidth = raylib::MeasureText("Name", 22);
    bool changingNameWidth = false;
    int nameWidth = 400;

    int typeStringWidth = raylib::MeasureText("Type", 22);
    bool changingTypeWidth = false;
    int typeWidth = 150;

    int sizeStringWidth = raylib::MeasureText("Size", 22);
    bool changingSizeWidth = false;
    int sizeWidth = 100;

    int scrolled = 0;
    
public:
    Tab();

    void update();
    void draw();

    void resetSelected();
    void refresh();
    void sortElements();
    void navigate(std::string path);
    
    std::vector<std::string> getCurrentFolderContent();
};