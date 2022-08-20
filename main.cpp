#include <iostream>
#include "Model.h"
#include "Rasterizer.h"
#include "Platform.h"

#define WIDTH 2048
#define HEIGHT 2048
#define CAMERA_SCALE 1

int main() {
    Model model("/Volumes/mac-code/RasterizationRender/assets/cyborg/cyborg.obj");
    model.load();
    Rasterizer rasterizer;
    glm::vec4 viewport(0, 0, WIDTH, HEIGHT);
    glm::vec3 cameraPos = glm::vec3(0, 0, 10);
    glm::mat4x4 modelMatrix = glm::translate(glm::identity<glm::mat4x4>(), {0.0, 0, 0});
    glm::mat4x4 viewMatrix = glm::lookAt(cameraPos, glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    glm::mat4x4 projMatrix = glm::perspective(45.f, 1.f, 0.1f, 100.f);
    rasterizer.setCameraPos(cameraPos);
    rasterizer.setModelMatrix(modelMatrix);
    rasterizer.setViewMatrix(viewMatrix);
    rasterizer.setProjectionMatrix(projMatrix);
    rasterizer.setViewPort(viewport);
    double t = (double) getTickCount();
    Mat mat = rasterizer.render(model);
    t = ((double) getTickCount() - t) / getTickFrequency();
    cv::putText(mat, "UseTime:" + to_string(t), Point(100, 100), 0, 1, Scalar(255, 0, 0));
    FastDebug(mat)
    return 0;
}
