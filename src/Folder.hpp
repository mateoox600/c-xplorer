#pragma once

#include <string>

class Folder {
private:
    std::string name;
public:
    Folder(std::string name);

    void update();
    void draw(int idx, int yOffset);
};