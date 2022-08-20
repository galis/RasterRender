//
// Created by galismac on 11/8/2022.
//

#include "Texture.h"

void Texture::load() {
    mat = cv::imread(path);
    cv::cvtColor(mat, mat, CV_BGR2RGBA);
    isLoad = true;
}

Texture::Texture(string &path) : path(path) {

}

Texture::Texture(string &&path) : path(path) {

}

glm::vec4 Texture::getColor(glm::vec2 &uv) {//0~1
    if (uv[0] < 0) uv[0] = 0;
    if (uv[1] < 0) uv[1] = 0;
    if (uv[0] > 1) uv[0] = 1;
    if (uv[1] > 1) uv[1] = 1;
    auto color = mat.at<Vec4b>(uv.y * mat.rows, uv.x * mat.cols);
    return glm::vec4(color[0], color[1], color[2], color[3]) / 255.f;
}

Mat &Texture::asMat() {
    return mat;
}
