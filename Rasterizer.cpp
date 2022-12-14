//
// Created by galismac on 10/8/2022.
//

#include "Rasterizer.h"
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

Mat Rasterizer::render(Model &model) {

    //处理zbuffer
    if (zbuffer.empty()) {
        zbuffer.resize(viewport[2] * viewport[3], 10000.0);
    }

    //cal mvp
    mvpMatrix = projMatrix * viewMatrix * modelMatrix;

    cv::Mat resultMat(cv::Size(viewport[2], viewport[3]), CV_8UC4, cv::Scalar(0, 0, 0, 255));
//    renderFace(model.getMeshs()[0], 2898, resultMat);
//    renderFace(model.getMeshs()[0], 4825, resultMat);
    for (Mesh &mesh:model.getMeshs()) {
        for (int i = 0; i < mesh.facesNum; i++) {
            renderFace(mesh, i, resultMat);
        }
    }

    return resultMat;
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
        return glm::cross(line, line2).z >= 0;
    };

    return getDir(pos, verticals[0], verticals[1]) &&
           getDir(pos, verticals[1], verticals[2]) &&
           getDir(pos, verticals[2], verticals[0]);
}

void Rasterizer::renderFace(Mesh &mesh, int faceIdx, cv::Mat &resultMat) {

    int width = viewport[2];
    int height = viewport[3];

    //初始化三角形顶点
    vector<Vertex> faceVerts(3);
    faceVerts[0] = mesh.vertices[3 * faceIdx];
    faceVerts[1] = mesh.vertices[3 * faceIdx + 1];
    faceVerts[2] = mesh.vertices[3 * faceIdx + 2];

    auto calTBN = [&](int i, int j, int k) {
        auto v1 = faceVerts[j].Position - faceVerts[i].Position;
        auto v2 = faceVerts[k].Position - faceVerts[i].Position;
        auto uv1 = faceVerts[j].TexCoords - faceVerts[i].TexCoords;
        auto uv2 = faceVerts[k].TexCoords - faceVerts[i].TexCoords;
        auto f = 1.0f / (uv1.x * uv2.y - uv1.y * uv2.x);
        auto tb = f * glm::mat2x2(uv2.y, -uv2.x, -uv1.y, uv1.x) * glm::mat3x2(v1.x, v2.x, v1.y, v2.y, v1.z, v2.z);
        auto t = glm::normalize(glm::row(tb, 0));
        auto n = faceVerts[i].Normal;
        t = glm::normalize(t - glm::dot(t, n) * n);
        auto b = glm::normalize(glm::cross(n, t));
        return glm::mat3x3(t, b, n);
    };

    auto tbn0 = calTBN(0, 1, 2);
    auto tbn1 = calTBN(1, 2, 0);
    auto tbn2 = calTBN(2, 0, 1);

    //计算屏幕坐标
    vector<glm::vec2> windowPos(3);
    for (int i = 0; i < faceVerts.size(); i++) {
        //裁剪坐标系
        faceVerts[i].ClipPos = mvpMatrix * glm::vec4(faceVerts[i].Position, 1.0);
        //齐次整除
        faceVerts[i].NormalPos = faceVerts[i].ClipPos / faceVerts[i].ClipPos[3];
        faceVerts[i].ModelNormal = modelMatrix * glm::vec4(faceVerts[i].Normal, 1.0f);
        //屏幕坐标系
        glm::vec2 screenPosition;
        screenPosition.x = (faceVerts[i].NormalPos.x + 1) * 0.5 * width;
        screenPosition.y = (faceVerts[i].NormalPos.y + 1) * 0.5 * height;
        windowPos[i] = screenPosition;
//        Platform::Debug("modelPos#" + glm::to_string(faceVerts[i].Position));
//        Platform::Debug("ClipPos#" + glm::to_string(faceVerts[i].ClipPos));
//        Platform::Debug("NormalPos#" + glm::to_string(faceVerts[i].NormalPos));
//        Platform::Debug("winPos#" + glm::to_string(windowPos[i]));
//        Platform::Debug("\n");
    }

    //计算roi
    float xMin = width, yMin = height, xMax = -1, yMax = -1;
    for (glm::vec2 &ver:windowPos) {
        xMin = min(xMin, ver.x);
        yMin = min(yMin, ver.y);
        xMax = max(xMax, ver.x);
        yMax = max(yMax, ver.y);
        std::cout << glm::to_string(ver) << std::endl;
    }
    xMin = floor(xMin);
    yMin = floor(yMin);
    xMax = ceil(xMax);
    yMax = ceil(yMax);
    glm::vec2 cur;
    for (int y = yMin; y <= yMax; y++) {
        for (int x = xMin; x <= xMax; x++) {
            cur.x = x;
            cur.y = y;
            //上色。。。
            if (isInTriangle(cur, windowPos)) {
                if (!mesh.textures.empty()) {
                    glm::vec3 bc = calZhongXinCoord(cur, windowPos);
                    float zn = 1.0f / (bc[0] / faceVerts[0].ClipPos[3] + bc[1] / faceVerts[1].ClipPos[3] + bc[2] / faceVerts[2].ClipPos[3]);
                    auto zp = zn * glm::vec3(bc[0] / faceVerts[0].ClipPos[3], bc[1] / faceVerts[1].ClipPos[3], bc[2] / faceVerts[2].ClipPos[3]);
                    int zbufferIdx = x + width * y;
                    if (zn < zbuffer[zbufferIdx]) {
                        glm::vec2 uv = zp[0] * faceVerts[0].TexCoords + zp[1] * faceVerts[1].TexCoords + zp[2] * faceVerts[2].TexCoords;
                        glm::vec3 faceNormal = glm::normalize(
                                zp[0] * faceVerts[0].ModelNormal + zp[1] * faceVerts[1].ModelNormal + zp[2] * faceVerts[2].ModelNormal);
                        glm::vec3 position = glm::normalize(
                                zp[0] * faceVerts[0].Position + zp[1] * faceVerts[1].Position + zp[2] * faceVerts[2].Position);
                        glm::vec3 srcNormal = mesh.textures[2].getColor(uv);
                        glm::vec3 specularColor = mesh.textures[1].getColor(uv);
                        auto tbn = zp[0] * tbn0 + zp[1] * tbn1 + zp[2] * tbn2;
                        glm::vec3 normal = glm::normalize(tbn * (glm::normalize(srcNormal * 2.0f - 1.0f)));

                        //cal normal
                        glm::vec3 lightPos(0, 0, 10);
                        glm::vec3 lightDir = glm::normalize(lightPos - position);
                        glm::vec3 viewDir = glm::normalize(cameraPos - position);
                        glm::vec3 reflectDir = glm::normalize(2 * glm::dot(lightDir, normal) * normal - lightDir);

                        float ambient = 0.1f;
                        float s = max(0.0f, glm::dot(glm::normalize(lightPos), normal));
                        float diffuse = 0.6f * s;
                        float specular = pow(max(glm::dot(reflectDir, viewDir), 0.0f), 32) * specularColor.x * 0.3f;
//                        float specular = 0;

                        glm::vec3 color = {255, 0, 0};//RGB
//                        color = (normal + 1.0f) * 0.5f;
                        color = mesh.textures[0].getColor(uv);
                        color *= min(1.0f, ambient + diffuse + specular);
                        color *= 255.f;
                        resultMat.at<Vec4b>(height - y, x) = Vec4b(color[0], color[1], color[2], 255.f);
                        zbuffer[zbufferIdx] = zn;
                    }
                }
            }
        }
    }
}

void Rasterizer::enableMSAA(bool enable) {
    isMsaa = enable;
}

glm::vec3 Rasterizer::calZhongXinCoord(glm::vec2 &pos, vector<glm::vec2> &verticals) {
    float i = (-(pos.x - verticals[1].x) * (verticals[2].y - verticals[1].y) + (pos.y - verticals[1].y) * (verticals[2].x - verticals[1].x))
              / (-(verticals[0].x - verticals[1].x) * (verticals[2].y - verticals[1].y) +
                 (verticals[0].y - verticals[1].y) * (verticals[2].x - verticals[1].x));
    float j = (-(pos.x - verticals[2].x) * (verticals[0].y - verticals[2].y) + (pos.y - verticals[2].y) * (verticals[0].x - verticals[2].x))
              / (-(verticals[1].x - verticals[2].x) * (verticals[0].y - verticals[2].y) +
                 (verticals[1].y - verticals[2].y) * (verticals[0].x - verticals[2].x));
    return {i, j, 1.0 - i - j};
}

void Rasterizer::setCameraPos(glm::vec3 &pos) {
    cameraPos = pos;
}

