#include "Tab.hpp"

#include "raylib-cpp.hpp"

#include "Constants.hpp"

using namespace Constants;

Tab::Tab() {

}

std::vector<std::string> Tab::getCurrentFolderContent() {
    return raylib::LoadDirectoryFiles(currentPath);
}

void Tab::update() {
    if(cachedFolders.size() <= 0) {
        std::vector<std::string> folderContent = getCurrentFolderContent();
        for(int i = 0; i < folderContent.size(); i++) {
            std::string element = folderContent[i];
            const char* name = GetFileNameWithoutExt(element.c_str());
            const char* extension = GetFileExtension(element.c_str());
            if(extension == NULL) {
                cachedFolders.push_back(Folder(name));
            }else {
                printf("File: %s;%s\n", name, extension);
            }
        }
    }
}

void Tab::draw() {
    raylib::DrawText(currentPath, 10, 10, 16, WHITE);

    int headerHeight = 50;

    int yOffset = 75;

    DrawRectangle(6, yOffset, screenWidth - 12, screenHeight - yOffset - 6, raylib::Color(32, 32, 32));
    DrawRectangleLines(6, yOffset, screenWidth - 12, screenHeight - yOffset - 6, raylib::Color(43, 43, 43));

    DrawText("Name", 14, yOffset + 10, 22, WHITE);

    for(int i = 0; i < cachedFolders.size(); i++) {
        cachedFolders[i].draw(i, yOffset + headerHeight);
    }
}