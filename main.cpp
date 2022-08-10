#include <iostream>
#include "Model.h"
#include "Rasterizer.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Model model("/Volumes/mac-code/RasterizationRender/assets/triangles.obj");
//    Model model("/Volumes/mac-code/RasterizationRender/assets/cube.obj");
    model.load();
    Rasterizer rasterizer;
    glm::vec4 viewport(0, 0, 480, 640);
    rasterizer.setViewPort(viewport);
    rasterizer.render(model);
    return 0;
}
