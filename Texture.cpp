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

int Texture::getColor(glm::vec2 &uv) {
    return mat.at<int>(uv.y * mat.rows, uv.x * mat.cols);
}
