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

    int changingNameWidth = false;
    int nameWidth = 400;

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