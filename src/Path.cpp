#include "Path.hpp"

#include <algorithm>

std::string Path::formatPath(std::string path) {
    std::replace(path.begin(), path.end(), '\\', '/');
    return path;
}