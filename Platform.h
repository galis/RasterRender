//
// Created by galismac on 10/8/2022.
//

#ifndef RASTERIZATIONRENDER_PLATFORM_H
#define RASTERIZATIONRENDER_PLATFORM_H


#include <string>

class Platform {
public:
    static void Debug(char *info);

    static void Debug(std::string &info);

    static void Debug(std::string &&info);
};


#endif //RASTERIZATIONRENDER_PLATFORM_H
