#pragma once

#include <string>
#include <vector>

#include "Folder.hpp"

class Tab {
private:
    std::string currentPath = "C:/Users/matbo/Documents/Dev/C-C++/c-xplorer/test/";
    std::vector<Folder> cachedFolders;
    
public:
    Tab();

    std::vector<std::string> getCurrentFolderContent();

    void update();
    void draw();
};