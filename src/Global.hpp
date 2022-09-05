#pragma once

#include "raylib-cpp.hpp"

#include <string>
#include <vector>
#include <map>

#include "Constants.hpp"
#include "Tab.hpp"

struct Global {

    Global() { }
    Global(raylib::Window* window) : window(window), mainFont(raylib::Font((Constants::ressourcesBasePath + "/Roboto-Regular.ttf"), 22)) {
        std::vector<std::string> extensionsFiles = raylib::LoadDirectoryFiles(Constants::ressourcesBasePath + "/extensions");
        for(int i = 0; i < extensionsFiles.size(); i++) {
            extensionsTextures[raylib::GetFileNameWithoutExt(extensionsFiles[i])] = raylib::Texture2D(extensionsFiles[i]);
        }
    }

    raylib::Window* window;

    Tab tab;

    std::map<std::string, raylib::Texture2D> extensionsTextures {};
    raylib::Font mainFont;

};

extern Global global;