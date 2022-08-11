//
// Created by galismac on 10/8/2022.
//

#include "Rasterizer.h"
#include "Platform.h"
#include <opencv2/opencv.hpp>

void Rasterizer::setModelMatrix(glm::mat4x4 &matrix) {
    modelMatrix = matrix;
}

void Rasterizer::setViewMatrix(glm::mat4x4 &matrix) {
    viewMatrix = matrix;
}

void Rasterizer::setProjectionMatrix(glm::mat4x4 &matrix) {
    projMatrix = matrix;
}

void Rasterizer::render(Model &model) {

    //cal mvp
    mvpMatrix = projMatrix * viewMatrix * modelMatrix;

    cv::Mat resultMat(cv::Size(viewport[2], viewport[3]), CV_8UC4, cv::Scalar(0, 0, 0, 0));
    for (const Mesh &mesh:model.getMeshs()) {
        vector<glm::vec2> vertexs(mesh.vertices.size());
        for (int i = 0; i < mesh.facesNum; i++) {
            renderFace(mesh, i, resultMat);
            Platform::Debug("renderFace#" + to_string(i));
        }
    }

    cv::imshow("render", resultMat);
    cv::waitKey(-1);
}

void Rasterizer::setViewPort(glm::vec4 &viewport) {
    this->viewport = viewport;
}

Rasterizer::Rasterizer() : viewport(0, 0, 640, 480), viewMatrix(1.0f), modelMatrix(1.0f), projMatrix(1.0f) {
}

bool Rasterizer::isInTriangle(glm::vec2 &pos, vector<glm::vec2> &verticals) {

    auto getDir = [](glm::vec2 &p, glm::vec2 &v1, glm::vec2 &v2) {
        glm::vec3 line(v2 - v1, 0);
        glm::vec3 line2(p - v1, 0);
        return glm::cross(line, line2).z < 0;
    };

    return getDir(pos, verticals[0], verticals[1]) &&
           getDir(pos, verticals[1], verticals[2]) &&
           getDir(pos, verticals[2], verticals[0]);
}

void Rasterizer::renderFace(const Mesh &mesh, int faceIdx, cv::Mat &resultMat) {

    //初始化三角形顶点
    vector<Vertex> faceVerts(3);
    faceVerts[0] = mesh.vertices[3 * faceIdx];
    faceVerts[1] = mesh.vertices[3 * faceIdx + 1];
    faceVerts[2] = mesh.vertices[3 * faceIdx + 2];

    //计算屏幕坐标
    vector<glm::vec2> windowPos(3);
    for (int i = 0; i < faceVerts.size(); i++) {
        //裁剪坐标系
        glm::vec4 clipPosition = mvpMatrix * glm::vec4(faceVerts[i].Position, 1.0);
        //规范化坐标系
        clipPosition.x /= clipPosition.w;
        clipPosition.y /= clipPosition.w;
        clipPosition.z /= clipPosition.w;
        //屏幕坐标系
        glm::vec2 screenPosition;
        screenPosition.x = (clipPosition.x + 1) * 0.5 * viewport[2];
        screenPosition.y = (1.0 - (clipPosition.y + 1) * 0.5) * viewport[3];
        windowPos[i] = screenPosition;
        Platform::Debug("modelPos#" + glm::to_string(faceVerts[i].Position));
        Platform::Debug("clipPos#" + glm::to_string(clipPosition));
        Platform::Debug("winPos#" + glm::to_string(windowPos[i]));
    }

    //计算roi
    float xMin = viewport[2], yMin = viewport[3], xMax = -1, yMax = -1;
    for (glm::vec2 &ver:windowPos) {
        xMin = floor(min(xMin, ver.x));
        yMin = floor(min(yMin, ver.y));
        xMax = ceil(max(xMax, ver.x));
        yMax = ceil(max(yMax, ver.y));
    }
    glm::vec2 cur;
    for (int y = yMin; y <= yMax; y++) {
        for (int x = xMin; x <= xMax; x++) {
            cur.x = x;
            cur.y = y;
            //上色。。。
            if (isInTriangle(cur, windowPos)) {
                resultMat.at<int>(y, x) = 0xffff0000 | (30 * faceIdx);
            }
        }
    }
}

void Rasterizer::enableMSAA(bool enable) {
    isMsaa = enable;
}

