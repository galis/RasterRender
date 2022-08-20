//
// Created by galismac on 11/8/2022.
//

#ifndef RASTERIZATIONRENDER_TEXTURE_H
#define RASTERIZATIONRENDER_TEXTURE_H

#include <string>
#include <opencv2/opencv.hpp>
#include <glm/glm.hpp>

using namespace std;
using namespace cv;

class Texture {
private:
    string path;
    Mat mat;
    bool isLoad;
public:
    explicit Texture(string &path);

    explicit Texture(string &&path);

    void load();

    Mat& asMat();

    glm::vec4 getColor(glm::vec2& uv);
};


#endif //RASTERIZATIONRENDER_TEXTURE_H
