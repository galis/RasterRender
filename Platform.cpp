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

void Platform::Debug(cv::Mat mat) {
    cv::Mat resultMat;
    cv::cvtColor(mat, resultMat, CV_RGBA2BGRA);
    cv::imshow("debug", resultMat);
    cv::waitKey(-1);
}
