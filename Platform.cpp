//
// Created by galismac on 10/8/2022.
//

#include "Platform.h"
#include <iostream>

void Platform::Debug(char *info) {
    std::cout << info << std::endl;
}

void Platform::Debug(std::string &info) {
    std::cout << info << std::endl;
}

void Platform::Debug(std::string &&info) {
    std::cout << info << std::endl;
}
