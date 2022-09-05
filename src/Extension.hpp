#pragma once

#include "raylib-cpp.hpp"

#include <string>
#include <map>

struct ExtensionInfo {
    raylib::Color color;
    std::string icon;
    std::string type;
    std::string executable;
};

extern std::map<std::string, ExtensionInfo> extensionsColorMap;

namespace Extension {
    
    ExtensionInfo getInfoForExt(std::string ext);

}
