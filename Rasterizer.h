//
// Created by galismac on 10/8/2022.
//

#ifndef RASTERIZATIONRENDER_RASTERIZER_H
#define RASTERIZATIONRENDER_RASTERIZER_H


#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <opencv2/opencv.hpp>
#include "Model.h"

/**
 * 光栅化模块
 */
class Rasterizer {
private:
    glm::mat4x4 modelMatrix, viewMatrix, projMatrix,mvpMatrix;
    glm::vec4 viewport;
    bool isMsaa;
    vector<int> zbuffer;

    bool isInTriangle(glm::vec2 &pos, vector<glm::vec2> &verticals);

    void renderFace(const Mesh &mesh, int faceIdx, cv::Mat &resultMat);

public:

    Rasterizer();

    void setModelMatrix(glm::mat4x4 &matrix);

    void setViewMatrix(glm::mat4x4 &matrix);

    void setProjectionMatrix(glm::mat4x4 &matrix);

    void setViewPort(glm::vec4 &viewport);

    void enableMSAA(bool enable);

    void render(Model &model);
};


#endif //RASTERIZATIONRENDER_RASTERIZER_H
