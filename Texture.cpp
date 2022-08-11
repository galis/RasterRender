//
// Created by galismac on 11/8/2022.
//

#include "Texture.h"

void Texture::load() {
    mat = cv::imread(path);
    cv::cvtColor(mat, mat, CV_BGR2BGRA);
    isLoad = true;
}

Texture::Texture(string &path) : path(path) {

}

Texture::Texture(string &&path) : path(path) {

}

glm::vec4 Texture::getColor(glm::vec2 &uv) {
    auto color = mat.at<Vec4b>(mat.rows - uv.y * mat.rows, uv.x * mat.cols);
    return {color[0],color[1],color[2],color[3]};
}
