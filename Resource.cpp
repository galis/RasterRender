//
// Created by galismac on 10/8/2022.
//

#include "Resource.h"

bool Resource::CheckPath(const std::string &path) {
    auto fd = fopen(path.c_str(), "r");
    if (fd) {
        fclose(fd);
        return true;
    }
    return false;
}

bool Resource::CheckPath(const std::string &&path) {
    auto fd = fopen(path.c_str(), "r");
    if (fd) {
        fclose(fd);
        return true;
    }
    return false;
}
