//
// Created by galismac on 10/8/2022.
//

#ifndef RASTERIZATIONRENDER_RESOURCE_H
#define RASTERIZATIONRENDER_RESOURCE_H

#include <string>

class Resource {
public:
    static bool CheckPath(const std::string &path);

    static bool CheckPath(const std::string &&path);
};


#endif //RASTERIZATIONRENDER_RESOURCE_H
