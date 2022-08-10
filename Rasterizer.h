//
// Created by galismac on 10/8/2022.
//

#ifndef RASTERIZATIONRENDER_RASTERIZER_H
#define RASTERIZATIONRENDER_RASTERIZER_H


#include <glm/glm.hpp>
#include "Model.h"

/**
 * 光栅化模块
 */
class Rasterizer {
private:
    glm::mat4x4 modelMatrix, viewMatrix, projMatrix;
    glm::vec4 viewport;
    vector<int> zbuffer;

    bool isInTriangle(glm::vec2 &pos, vector<glm::vec2> &verticals);

public:

    Rasterizer();

    void setModelMatrix(glm::mat4x4 &matrix);

    void setCameraMatrix(glm::mat4x4 &matrix);

    void setProjectionMatrix(glm::mat4x4 &matrix);

    void setViewPort(glm::vec4 &viewport);

    void render(Model &model);
};


#endif //RASTERIZATIONRENDER_RASTERIZER_H
