#pragma once

#include "raylib-cpp.hpp"

#include <string>
#include <vector>
#include <map>

#include "Constants.hpp"
#include "Tab.hpp"

struct Global {

    Global() { }
    Global(raylib::Window* window) : window(window), mainFont(raylib::Font((Constants::ressourcesBasePath + "/Roboto-Regular.ttf"), 22)) { }

    raylib::Window* window;

    Tab tab;

    std::map<std::string, raylib::Texture2D> extensionsTextures {};
    raylib::Font mainFont;

    raylib::Texture2D* GetOrLoadExtensionTexture(std::string extension) {
        if(!extensionsTextures.count(extension)) {
            if(!raylib::FileExists(Constants::ressourcesBasePath + "/extensions/" + extension + ".png")) return nullptr;
            extensionsTextures[extension] = raylib::Texture2D(Constants::ressourcesBasePath + "/extensions/" + extension + ".png");
        }
        return &extensionsTextures[extension];
    }

};

extern Global global;