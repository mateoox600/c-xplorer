#pragma once

#include "raylib-cpp.hpp"
#include <string>
#include <vector>

#include "Folder.hpp"

class Tab {
private:
    std::string currentPath = "C:/Users/matbo/Documents/Dev/C-C++/c-xplorer/test/";
    std::vector<Folder> cachedFolders;
    int headerHeight = 50;
    int yOffset = 75;
    int nameStringWidth = raylib::MeasureText("Name", 22);

    int changingNameWidth = false;
    int nameWidth = 400;
    
public:
    Tab();

    std::vector<std::string> getCurrentFolderContent();

    void update();
    void draw();
};