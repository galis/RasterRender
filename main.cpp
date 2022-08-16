#include <iostream>
#include "Model.h"
#include "Rasterizer.h"

#define WIDTH 720
#define HEIGHT 720
#define CAMERA_SCALE 1

int main() {
    Model model("/Volumes/mac-code/RasterizationRender/assets/cyborg/cyborg.obj");
//    Model model("/Volumes/mac-code/RasterizationRender/assets/rock/rock.obj");
//    Model model("/Volumes/mac-code/RasterizationRender/assets/triangles.obj");
//    Model model("/Volumes/mac-code/RasterizationRender/assets/bunny.obj");
//    Model model("/Volumes/mac-code/RasterizationRender/assets/cube.obj");
    model.load();
    Rasterizer rasterizer;
    glm::vec4 viewport(0, 0, WIDTH, HEIGHT);
    float scale = HEIGHT * 1.0f / WIDTH;
    float orthoCameraScale = 15.0f;
    glm::mat4x4 modelMatrix = glm::translate(glm::identity<glm::mat4x4>(), {0.0, 0, 0});
    glm::mat4x4 viewMatrix = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
//    glm::mat4x4 projMatrix = glm::ortho(-1.f * orthoCameraScale, 1.f * orthoCameraScale, -1.f * scale * orthoCameraScale,
//                                        1.f * scale * orthoCameraScale, 0.01f, 100.f);
    glm::mat4x4 projMatrix = glm::perspective(45.f, 1.f, 0.1f, 100.f);
    rasterizer.setModelMatrix(modelMatrix);
    rasterizer.setViewMatrix(viewMatrix);
    rasterizer.setProjectionMatrix(projMatrix);
    rasterizer.setViewPort(viewport);
    double t = (double) getTickCount();
    // do something ...
    Mat mat = rasterizer.render(model);
    t = ((double) getTickCount() - t) / getTickFrequency();
    cv::putText(mat, "UseTime:" + to_string(t), Point(100, 100), 0, 1, Scalar(255, 0, 0));
    cv::imshow("window", mat);
    cv::waitKey(-1);
    return 0;
}
