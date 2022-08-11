#include <iostream>
#include "Model.h"
#include "Rasterizer.h"

#define WIDTH 480
#define HEIGHT 640

int main() {
    Model model("/Volumes/mac-code/RasterizationRender/assets/rock/rock.obj");
//    Model model("/Volumes/mac-code/RasterizationRender/assets/triangles.obj");
//    Model model("/Volumes/mac-code/RasterizationRender/assets/bunny.obj");
//    Model model("/Volumes/mac-code/RasterizationRender/assets/cube.obj");
    model.load();
    Rasterizer rasterizer;
    glm::vec4 viewport(0, 0, WIDTH, HEIGHT);
    float scale = HEIGHT * 1.0f / WIDTH;
    glm::mat4x4 modelMatrix = glm::translate(glm::identity<glm::mat4x4>(), {0.0, 0, 0});
    glm::mat4x4 viewMatrix = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
//    viewMatrix = glm::rotate(viewMatrix, 70.f, glm::vec3(1, 0, 0));
    glm::mat4x4 projMatrix = glm::ortho(-2.f, 2.f, -2.f * scale, 2.f * scale, -2.f, 2.f);

    rasterizer.setModelMatrix(modelMatrix);
    rasterizer.setViewMatrix(viewMatrix);
    rasterizer.setProjectionMatrix(projMatrix);
    rasterizer.setViewPort(viewport);
    rasterizer.render(model);
    return 0;
}
