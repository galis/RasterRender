cmake_minimum_required(VERSION 3.17)
project(RasterizationRender)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules")

include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_executable(Rasterizer main.cpp Model.cpp Rasterizer.cpp Resource.cpp Platform.cpp Mesh.cpp)
target_link_libraries(Rasterizer assimp opencv_core opencv_highgui opencv_imgcodecs)