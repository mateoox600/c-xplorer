#include "Extension.hpp"

#include <algorithm>

std::map<std::string, ExtensionInfo> extensionsColorMap {
    { ".py", { raylib::Color(0, 0, 255), "", "Python script", "code" } },
    { ".txt", { raylib::Color(0, 0, 0, 0), "txt", "Raw text file", "code" } }
};

std::string extensionToFormatedFileTypeName(std::string extension) {
    if(extension == "") {
        return "File";
    }
    std::transform(extension.begin(), extension.end(), extension.begin(), [](unsigned char c) { return toupper(c); });
    extension = extension.substr(1);
    return extension + " File";
}

ExtensionInfo Extension::getInfoForExt(std::string extension) {
    if(extensionsColorMap.find(extension) == extensionsColorMap.end()) {
        return ExtensionInfo{ raylib::Color(255, 0, 0), "", extensionToFormatedFileTypeName(extension), "" };
    }
    return extensionsColorMap[extension];
}