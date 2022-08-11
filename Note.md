# Problem

## glm/opengl是列存储模式
```c++
glm::mat4x4 modelMatrix = glm::translate(glm::identity<glm::mat4x4>(), { 0.5, 0, 0 });
std::cout << glm::to_string(modelMatrix) << std::endl;
//存储如下：
//mat4x4((1.000000, 0.000000, 0.000000, 0.000000),
//(0.000000, 1.000000, 0.000000, 0.000000),
//(0.000000, 0.000000, 1.000000, 0.000000),
//(0.500000, 0.000000, 0.000000, 1.000000))
```

## 判断点在三角形中

## 计算重心坐标

## zbuffer